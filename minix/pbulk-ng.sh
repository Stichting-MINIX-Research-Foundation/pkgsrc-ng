#!/bin/sh

# This script tries to optimise time building for jailed pbulk builds
# at the expense of disk space.
#
# A full (all packages) build requires currently about:
#  -   1.0GB	pkgsrc itself
#  -   0.3GB	chroot-minix
#  -   1.3GB	chroot-bootstrap
#  -   1.3GB	chroot-pbulk (w/o distfiles)
#  -  24.0GB	distfiles (sources of the packages)
#  -  20.0GB    during build, to store temporary files and produced packages
# ==========
#    ~48.0GB	total
#
# I (LSC) recommend a partition of at least 100GB for a full build.
#
# this will create the following hierarchy (assuming defaults) :
# /usr/bbuild
# /usr/bbuild/chroot-minix	Pristine minix rootfs
# /usr/bbuild/chroot-bootstrap	Pristine minix + bootstrapped pbulk tools
# /usr/bbuild/chroot-pbulk	Root system with build pkgsrc.
#
# Upon successful completion the following will be copied into:
# /usr/bbuild/save/YYYYMMDD-HHmmss.logs     pbulk-log files
# /usr/bbuild/save/YYYYMMDD-HHmmss.packages generated packages
# /usr/bbuild/save/YYYYMMDD-HHmmss.disfiles fetched distfiles
#

# Exit at the first error
set -e

# Some useful constant
YES="yes"
NO="no"

# Defaults
: ${TOPDIR=/usr/bbuild}
: ${SAVEDIR=/usr/bbuild/save}
: ${TOOLDIR=/usr/bbuild/tooldir.$(uname -p)}
: ${OBJDIR=/usr/bbuild/obj.$(uname -p)}
: ${MINIXSRCDIR=/usr/src}
: ${PKGSRCDIR=/usr/pkgsrc}
: ${DISTFILESDIR=/usr/pkgsrc/distfiles}
: ${USETOOLS=yes}

: ${ROOT_MINIX=${TOPDIR}/chroot-minix}
: ${ROOT_BOOTSTRAP=${TOPDIR}/chroot-bootstrap}
: ${ROOT_PBULK=${TOPDIR}/chroot-pbulk}

# By default copy the local pkgsrc repository
: ${PKGSRC_COPY=${YES}}
: ${PKGSRC_REMOTE=pkgsrc}
: ${PKGSRC_URL=git://git.minix3.org/pkgsrc.git}
: ${PKGSRC_BRANCH=minix-master}
# Destination pkgsrc git, absolute path, has to contain ROOT_BOOTSTRAP!
: ${PKGSRC_GIT=${ROOT_BOOTSTRAP}/usr/pkgsrc/.git}

# By default re-use root FS if available
: ${BUILD_ROOT_BOOTSTRAP=${NO}}
: ${BUILD_ROOT_MINIX=${NO}}
: ${BUILD_ROOT_PBULK=${NO}}

# By default copy to a safe place the generated packages, distfiles and logs
: ${SAVE_PACKAGES=${YES}}
: ${SAVE_DISTFILES=${YES}}
: ${SAVE_LOGS=${YES}}

# Use tools through variables, ease the debug process
: ${DRY_RUN=${NO}}

# Some private variables which may used from within the chroots
: ${CMD_BOOTSTRAP=./bootstrap/bootstrap}
: ${CMD_BOOTSTRAP_CLEANUP=./bootstrap/cleanup}
#   This cannot be changed without updating pbulk.conf
: ${BOOTSTRAP_PREFIX=/usr/pbulk}
: ${PKGSRC_PREFIX=/usr/pkgsrc}

# Generate a clean PATH for the jails.
CHROOT_PATH=""
for d in ${BOOTSTRAP_PREFIX} /usr/pkg /usr/X11R7 /usr ''
do
	CHROOT_PATH=${CHROOT_PATH}:${d}/bin:${d}/sbin
done
CHROOT_PATH=${CHROOT_PATH}:/usr/games
LD_CHROOT_PATH=/usr/pkg/lib:/usr/X11R7/lib:/usr/lib:/lib

if [ ! -d $MINIXSRCDIR ]
then
	echo Please install the minix sources in $MINIXSRCDIR.
	exit 1
fi

#============================================================================
if [ ${DRY_RUN} = ${YES} ]
then
	RM='echo ##: rm '
	MV='echo ##: mv '
	CP='echo ##: cp '
	CD='echo ##: cd '
	LN='echo ##: ln '
	SED='echo ##: sed '
	CHROOT='echo ##: chroot '
	MKDIR='echo ##: mkdir '
	TAR='echo ##: tar '
	EXPORT='echo ##: export '
	PKG_ADD='echo ##: pkg_add '
	SYNCTREE='echo ##: synctree '
	GIT='echo ##: git '
	BMAKE='echo ##: bmake '
	CMD_RELEASE="echo ##: ${CMD_RELEASE} "
	CMD_BOOTSTRAP="echo ##: ${CMD_BOOTSTRAP} "
	CMD_BOOTSTRAP_CLEANUP="echo ##: ${CMD_BOOTSTRAP_CLEANUP} "
	CMD_RESET_ERRORS="echo ##: test ! -f /usr/pbulk-logs/meta/error || rm /usr/pbulk-logs/meta/error "
	CMD_BULKBUILD="echo ##: bulkbuild "
	CMD_BULKBUILD_RESTART="echo ##: bulkbuild-restart "

	DIRNAME='echo _dirname_ '
	# Kind of an exception, but as it used to collect
	# all the output of a phase, we want it to be echoed,
	# instead of saved in a log file
	TEE="cat - "
else
	RM='rm '
	MV='mv '
	CP='cp '
	CD='cd '
	LN='ln '
	SED='sed '
	DIRNAME='dirname '
	CHROOT='chroot '
	MKDIR='mkdir '
	TAR='tar '
	EXPORT='export '
	PKG_ADD='pkg_add '
	SYNCTREE='synctree '
	GIT='git '
	BMAKE='bmake '
	TEE='tee '
	CMD_RESET_ERRORS="test ! -f /usr/pbulk-logs/meta/error || rm /usr/pbulk-logs/meta/error "
	CMD_BULKBUILD="bulkbuild "
	CMD_BULKBUILD_RESTART="bulkbuild-restart "
fi

# Check at which step which should start :
[ ! -d "${ROOT_MINIX}" ] && BUILD_ROOT_MINIX=${YES}
[ ! -d "${ROOT_BOOTSTRAP}" ] && BUILD_ROOT_BOOTSTRAP=${YES}
[ ! -d "${ROOT_PBULK}" ] && BUILD_ROOT_PBULK=${YES}

# Ensure that all the steps following the first to be generated
# are also re-generated.
[ ${BUILD_ROOT_MINIX} = ${YES} ] && BUILD_ROOT_BOOTSTRAP=${YES}
[ ${BUILD_ROOT_BOOTSTRAP} = ${YES} ] && BUILD_ROOT_PBULK=${YES}

#============================================================================
build_minix() {
	echo ":-> Building minix chroot in ${ROOT_MINIX}"
	(
		exec 2>&1
		set -e

		echo ":--> Building minix sources [${BUILD_START}]"

		${CD} ${MINIXSRCDIR}

		HOST_CC=clang HOST_CXX=clang++ ./build.sh \
			-m i386 \
			-O ${OBJDIR} \
			-T ${TOOLDIR} \
			-D ${ROOT_MINIX} \
			-V SLOPPY_FLIST=yes \
			-V MKX11=yes \
			-V MKUPDATE=yes \
			-V MKLLVM=yes \
			-V MKLIBCXX=yes \
			-V MKGCCCMDS=no \
			-V MKLIBSTDCXX=no \
			-V MKKYUA=no \
			-V MKATF=no \
			distribution

		echo ":--> Copying config files"
		for f in hosts resolv.conf
		do
			[ -f /etc/${f} ] && ${CP} /etc/${f} ${ROOT_MINIX}/etc/${f}
		done
	) | ${TEE} ${TOPDIR}/1-build_minix.log
	echo ":-> Building minix chroot done"

	return 0
}

build_bootstrap() {
	echo ":-> Building bootstrapped chroot"
	(
		exec 2>&1
		set -e
		echo ":--> Initializing chroot in ${ROOT_BOOTSTRAP} [${BUILD_START}]"

		if [ ${PKGSRC_COPY} = ${YES} ]
		then
			echo ":--> Copying from ${PKGSRCDIR}"
			# Copy and use our local pkgsrc repository as it is
			${MKDIR} -p ${ROOT_BOOTSTRAP}${PKGSRC_PREFIX}
			${SYNCTREE} -f ${PKGSRCDIR} ${ROOT_BOOTSTRAP}${PKGSRC_PREFIX} >/dev/null
		else
			echo ":--> Cloning from ${PKGSRC_URL}/${PKGSRC_BRANCH}"
			# Copy our own pkgsrc repository there so the new
			# repository does not have to retrieve objects we
			# already have locally.
			${MKDIR} -p ${PKGSRC_GIT}
			${SYNCTREE} -f ${PKGSRCDIR}/.git ${PKGSRC_GIT} >/dev/null
			${GIT} --git-dir ${PKGSRC_GIT} remote rm ${PKGSRC_REMOTE}
			${GIT} --git-dir ${PKGSRC_GIT} remote add ${PKGSRC_REMOTE} ${PKGSRC_URL} 
			${GIT} --git-dir ${PKGSRC_GIT} fetch ${PKGSRC_REMOTE}
			${GIT} --git-dir ${PKGSRC_GIT} checkout -f ${PKGSRC_REMOTE}/${PKGSRC_BRANCH}
		fi

		# Bonus distfiles	
		echo ":--> Copying prefetched distfiles from ${DISTFILESDIR}"
		${MKDIR} -p ${ROOT_BOOTSTRAP}${PKGSRC_PREFIX}/distfiles
		${SYNCTREE} -f ${DISTFILESDIR} ${ROOT_BOOTSTRAP}${PKGSRC_PREFIX}/distfiles >/dev/null

		# Ensure that the package directoy is clean and exists
		${RM} -rf ${ROOT_BOOTSTRAP}${PKGSRC_PREFIX}/packages/$(uname -r)/
		${MKDIR} -p ${ROOT_BOOTSTRAP}${PKGSRC_PREFIX}/packages/$(uname -r)/$(uname -p)/All

		echo ":--> Bootstrapping pbulk"
		${CHROOT} ${ROOT_BOOTSTRAP} sh -c \
		"(
			set -e
			${EXPORT} PATH=${CHROOT_PATH}
			${EXPORT} LD_LIBRARY_PATH=${LD_CHROOT_PATH}

			${CD} ${PKGSRC_PREFIX}

			# First stage, PBULK bootstrap & installation
			
			# Trim the .ifdef BSD_PKG_MK and .endif lines to make a 'fragment'
			# and adapt a few path to the ones expected for pbulk
			${SED} \
				-e '/.*BSD_PKG_MK/d' \
				-e 's@VARBASE?=.*@VARBASE=	'${BOOTSTRAP_PREFIX}'/var@' \
				-e 's@PKG_DBDIR?=.*@PKG_DBDIR=	'${BOOTSTRAP_PREFIX}'/pkgdb@' \
				-e 's@WRKOBJDIR?=.*@WRKOBJDIR=	'${BOOTSTRAP_PREFIX}'/work@' \
				./minix/mk.conf.minix \
				> ./minix/mk.conf.minix.pbulk.frag

			echo ':--> Building pbulk kit'
			${CMD_BOOTSTRAP} \
				--prefix=${BOOTSTRAP_PREFIX} \
				--varbase=${BOOTSTRAP_PREFIX}/var \
				--pkgdbdir=${BOOTSTRAP_PREFIX}/pkgdb \
				--workdir=${BOOTSTRAP_PREFIX}/work \
				--mk-fragment=./minix/mk.conf.minix.pbulk.frag

			# Install pbulk into /usr/pbulk
			echo ':--> Building and installing pbulk'
			${BMAKE} -C ./devel/pth package-install
			${BMAKE} -C ./pkgtools/pbulk package-install
			${SED} -e 's/OP_SYS_VER/'$(uname -r)'/g' ./minix/pbulk.conf > ${BOOTSTRAP_PREFIX}/etc/pbulk.conf

			# First stage: done

			echo ':--> Bootstrap cleanup'
			${CMD_BOOTSTRAP_CLEANUP}

			# Second stage, pkgsrc bootstrap & installation

			# Trim the .ifdef BSD_PKG_MK and .endif lines to make a 'fragment'
			${SED} -e '/.*BSD_PKG_MK/d' \
				./minix/mk.conf.minix \
				> ./minix/mk.conf.minix.frag

			echo ':--> Building binary pkgsrc kit'
                 	${CMD_BOOTSTRAP} \
				--varbase=/usr/pkg/var \
				--pkgdbdir=/usr/pkg/var/db/pkg \
				--mk-fragment=./minix/mk.conf.minix.frag \
				--workdir=${PKGSRC_PREFIX}/work \
				--gzip-binary-kit=${BOOTSTRAP_PREFIX}/bootstrap.tar.gz

			${RM} -rf ./packages/$(uname -r)/
			${MKDIR} -p ./packages/$(uname -r)/$(uname -p)/All

			# Use the same mk.conf that our users instead of the hybrid 
			# auto-generated mk.conf from bootstrap.
			${TAR} -C /tmp -xzf ${BOOTSTRAP_PREFIX}/bootstrap.tar.gz
			${CP} ./minix/mk.conf.minix /tmp/usr/pkg/etc/mk.conf
			${TAR} -C /tmp -hzcf ${BOOTSTRAP_PREFIX}/bootstrap.tar.gz usr
			${RM} -rf /tmp/usr

			# Second stage: done
		)"

		echo ":--> Bootstrapping pbulk done"
		
	) | ${TEE} ${TOPDIR}/2-build_bootstrap.log
	echo ":-> Building bootstrapped chroot done"

	return 0
}

pbulk_start() {
	echo ":-> Building packages from scratch"
	(
		exec 2>&1
		set -e

		${CHROOT} ${ROOT_PBULK} sh -c \
		"(
			set -e
			${EXPORT} PATH=${CHROOT_PATH}
			${EXPORT} LD_LIBRARY_PATH=${LD_CHROOT_PATH}

			${CD} ${PKGSRC_PREFIX}

			echo ':--> Starting build ['${BUILD_START}']'
			${CMD_BULKBUILD}
		)"
	) | ${TEE} ${TOPDIR}/3-pbulk.log
	echo ":-> Building packages from scratch done"

	return 0
}

pbulk_restart() {
	echo ":-> Building packages from previous build"
	(
		exec 2>&1
		set -e

		${CHROOT} ${ROOT_PBULK} sh -c \
		"(
			set -e
			${EXPORT} PATH=${CHROOT_PATH}
			${EXPORT} LD_LIBRARY_PATH=${LD_CHROOT_PATH}

			${CD} ${PKGSRC_PREFIX}

			echo ':--> Resetting error file'
			${CMD_RESET_ERRORS}

			echo ':--> Restarting build ['${BUILD_START}']'
			${CMD_BULKBUILD_RESTART}
		)"
	) | ${TEE} ${TOPDIR}/3-pbulk.log

	echo ":-> Building packages from previous build done"
}

#============================================================================
# Initializations are done, start applying the requested actions on the system

BUILD_START=$(date)
echo -e "\n:: pbulk started on ${BUILD_START}"

if [ ${BUILD_ROOT_MINIX} = ${YES} ]
then
	echo -e "\n:> Generating minix root fs."
	${RM} -rf ${ROOT_MINIX}

	# Ensure presence of destination directory
	${MKDIR} -p ${ROOT_MINIX}

	build_minix
fi

if [ ${BUILD_ROOT_BOOTSTRAP} = ${YES} ]
then
	echo -e "\n:> Bootstrapping pkgsrc."
	# Ensure the new chroot is clean.
	${MKDIR} -p ${ROOT_BOOTSTRAP}
	${SYNCTREE} -f ${ROOT_MINIX} ${ROOT_BOOTSTRAP} >/dev/null

	build_bootstrap
fi

if [ ${BUILD_ROOT_PBULK} = ${YES} ]
then
	echo -e "\n:> Initializing pbulk root."
	# Ensure the new chroot is clean.
	${MKDIR} -p ${ROOT_PBULK}
	${SYNCTREE} -f ${ROOT_BOOTSTRAP} ${ROOT_PBULK} >/dev/null

	echo -e "\n:> Building packages from scratch."
	pbulk_start
else
	# We want to re-use a previous pbulk.
	# Just make sure that any modification within the pkgsrc tree is visible
	# find param to make synctree keep files in packages and distfiles
	# Also requires regenerating the bootstrap tarball, as well as updating
	# ROOT_PBULK/usr/pbulk/etc/pbulk.conf
	#${SYNCTREE} -f ${PKGSRCDIR} ${ROOT_PBULK}${PKGSRC_PREFIX} >/dev/null

	echo -e "\n:> Restarting build of packages."
	pbulk_restart
fi

_build_end=$(date '+%Y%m%d%H%M.%S')
BUILD_END=$(date -j ${_build_end})

# We have to do this here, otherwise the date field would be empty
: ${TIMESTAMP=$(date -j '+%Y%m%d-%H%M%S' ${_build_end})}
: ${ROOT_LOGS=${SAVEDIR}/${TIMESTAMP}.logs}
: ${ROOT_DISTFILES=${SAVEDIR}/${TIMESTAMP}.distfiles}
: ${ROOT_PACKAGES=${SAVEDIR}/${TIMESTAMP}.packages}

if [ ${SAVE_LOGS} = ${YES} ]
then
	${MKDIR} -p ${ROOT_LOGS}
	${CP} -pfr ${TOPDIR}/1-build_minix.log ${ROOT_LOGS}/
	${CP} -pfr ${TOPDIR}/2-build_bootstrap.log ${ROOT_LOGS}/
	${CP} -pfr ${TOPDIR}/3-pbulk.log ${ROOT_LOGS}/
	${SYNCTREE} -uf ${ROOT_PBULK}/usr/pbulk-logs ${ROOT_LOGS}/pbulk-logs
fi

if [ ${SAVE_DISTFILES} = ${YES} ]
then
	${SYNCTREE} -uf ${ROOT_PBULK}${PKGSRC_PREFIX}/distfiles ${ROOT_DISTFILES}
fi

if [ ${SAVE_PACKAGES} = ${YES} ]
then
	${SYNCTREE} -uf ${ROOT_PBULK}${PKGSRC_PREFIX}/packages ${ROOT_PACKAGES}
fi

echo -e "\n:: pbulk finished:"
echo ":>   started on  : ${BUILD_START}"
echo ":>   finished on : ${BUILD_END}"
echo ":> Build logs    : ${ROOT_LOGS}"
echo ":> Distfiles     : ${ROOT_DISTFILES}"
echo ":> Packages      : ${ROOT_PACKAGES}"
