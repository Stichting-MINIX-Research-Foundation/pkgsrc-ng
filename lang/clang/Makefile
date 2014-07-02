# $NetBSD: Makefile,v 1.26 2014/02/27 17:35:35 adam Exp $

DISTNAME=	clang-3.4
PKGREVISION=	1
CATEGORIES=	lang
MASTER_SITES=	${MASTER_SITE_MINIX}
DISTFILES=	llvm-${PKGVERSION_NOREV}.minix.src.tar.gz \
		libcxx-${PKGVERSION_NOREV}.minix.src.tar.gz \
		clang-${PKGVERSION_NOREV}.minix.src.tar.gz

MAINTAINER=	ben@minix3.org
HOMEPAGE=	http://llvm.org/
COMMENT=	Low Level Virtual Machine compiler infrastructure
LICENSE=	modified-bsd

WRKSRC=			${WRKDIR}/llvm-${PKGVERSION_NOREV}

USE_LANGUAGES=		c c++
USE_TOOLS+=		chown gmake groff pod2html pod2man
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--disable-assertions
CONFIGURE_ARGS+=	--disable-bindings	# disable OCaml
CONFIGURE_ARGS+=	--disable-timestamps
CONFIGURE_ARGS+=	--enable-optimized
#CONFIGURE_ARGS+=	--enable-shared

MAKE_DIRS+=		etc/llvm

INSTALLATION_DIRS=	bin lib libexec

CHECK_PORTABILITY_SKIP=	utils/buildit/build_llvm

TEST_TARGET=	check unittests

.include "../../mk/bsd.prefs.mk"

.if ${_OPSYS_SHLIB_TYPE} == "dylib"
PLIST_SUBST+=		SOEXT="dylib"
.else
PLIST_SUBST+=		SOEXT="so"
.endif

.include "../../mk/compiler.mk"

.if ${OPSYS} == "SunOS" && !empty(PKGSRC_COMPILER:Mgcc)
# This should probably be in hacks, but since clang hardcodes gcc paths
# put this here so it can be removed when clang matures.
# cxa_finalize.o is no longer necessary with libc.so >= ILLUMOS_0.5
TEST_ILLUMOS_3849!=\
	if /usr/bin/elfdump -v /lib/libc.so |\
	  ${GREP} -q 'ILLUMOS_0.5' ; then	\
		${ECHO} 1;	\
	else ${ECHO} 0;	\
	fi

#doesn't seem to be needed anymore, but may be dependent on
#a recent version of solaris (illumos) ld.
#
#CFLAGS.SunOS+=		-mimpure-text

SUBST_CLASSES+=			fix-paths
SUBST_STAGE.fix-paths=		pre-configure
SUBST_MESSAGE.fix-paths=	Fixing absolute gcc paths for SunOS.
SUBST_FILES.fix-paths=		tools/clang/lib/Driver/Tools.cpp
.  if defined(_GCC_ARCHDIR)
SUBST_SED.fix-paths=		-e 's,/usr/gcc/4.5/lib/gcc/,${_GCC_ARCHDIR}/,g'
.  else
LIBGCCDIR!=	${CC} -print-libgcc-file-name
ARCHDIR:=	${LIBGCCDIR:H}
SUBST_SED.fix-paths=		-e 's,/usr/gcc/4.5/lib/gcc/,${ARCHDIR}/,g'
.  endif
SUBST_SED.fix-paths+=		-e '/^.*i386.*getVendorName.*$$/{d;}'
SUBST_SED.fix-paths+=		-e '/^.*GCCLibPath +=$$/d'
SUBST_SED.fix-paths+=		-e 's,/4.5.2/amd64/,amd64/,g'
SUBST_SED.fix-paths+=		-e 's,"as","gas",g'
.  if exists(/usr/bin/ld)
SUBST_SED.fix-paths+=		-e 's,getToolChain().GetProgramPath("ld"),"/usr/bin/ld",g'
.  else
SUBST_SED.fix-paths+=		-e 's,getToolChain().GetProgramPath("ld"),"/usr/ccs/bin/ld",g'
.  endif
.  if ${TEST_ILLUMOS_3849}
SUBST_SED.fix-paths+=		-e 's,^.*cxa_finalize.*$$,		; //cxa_finalize.o,g'
.  endif
.endif

post-extract:
	mv ${WRKDIR}/libcxx-${PKGVERSION_NOREV} ${WRKSRC}/projects/libcxx
	mv ${WRKDIR}/clang-${PKGVERSION_NOREV} ${WRKSRC}/tools/clang
.if ${OPSYS} == "SunOS"
	${ECHO} "int sun_ld_needs_a_symbol=0;" >> ${WRKSRC}/lib/Target/NVPTX/InstPrinter/NVPTXInstPrinter.cpp
.endif

.if ${OPSYS} == "NetBSD" && ${OS_VARIANT} == "Minix"
.  if ${PKGSRC_COMPILER} == "clang"
# Can't build libc++ with GCC45
# Seems it is not installed, so for now just skip it, and go with the defaults.
#CONFIGURE_ARGS+=	--enable-libcpp
.  endif
CONFIGURE_ARGS+=	--disable-threads
CONFIGURE_ARGS+=	--with-binutils-include=${LOCALBASE}/include/
CONFIGURE_ENV+= ac_cv_func_getrusage=no ac_cv_func_setrlimit=no

post-install:
	${INSTALL_SCRIPT} ${WRKSRC}/tools/clang/tools/scan-build/* ${DESTDIR}${PREFIX}/bin/
	${INSTALL_SCRIPT} ${WRKSRC}/tools/clang/tools/scan-build/ccc-analyzer \
		${WRKSRC}/tools/clang/tools/scan-build/c++-analyzer \
		${WRKSRC}/tools/clang/tools/scan-build/scan-build \
		${WRKSRC}/tools/clang/tools/scan-view/scan-view \
		${DESTDIR}${PREFIX}/bin
	${MKDIR} ${DESTDIR}${PYSITELIB}
	${MKDIR} ${DESTDIR}${PYSITELIB}/Resources
	${INSTALL_SCRIPT} ${WRKSRC}/tools/clang/tools/scan-view/*.py \
		${DESTDIR}${PYSITELIB}
	${INSTALL_SCRIPT} ${WRKSRC}/tools/clang/tools/scan-view/Resources/* \
		${DESTDIR}${PYSITELIB}/Resources
	${MKDIR} ${DESTDIR}${PREFIX}/share
	${INSTALL_DATA} ${WRKSRC}/tools/clang/tools/scan-build/scanview.css ${DESTDIR}${PREFIX}/share
	${INSTALL_DATA} ${WRKSRC}/tools/clang/tools/scan-build/sorttable.js ${DESTDIR}${PREFIX}/share

.  if ${PKGSRC_COMPILER} == "gcc"
# When the package is compiled using GCC we depend on libstdc++
# Requires changes in the package to symlink libstdc++.so* in /usr/pkg/lib
#.include "../../lang/gcc45/buildlink3.mk"
.  endif
.include "../../devel/binutils/buildlink3.mk"
.endif # ${OPSYS} == "NetBSD" && ${OS_VARIANT} == "Minix"

.include "../../lang/python/tool.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
