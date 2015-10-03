# $NetBSD: options.mk,v 1.41 2015/09/18 16:18:47 tnn Exp $

PKG_OPTIONS_VAR=		PKG_OPTIONS.MesaLib
PKG_SUPPORTED_OPTIONS=		llvm dri
PKG_SUGGESTED_OPTIONS=

# The LLVM option enables JIT accelerated software rendering and
# is also required to support the latest RADEON GPUs, so enable it
# by default on platforms where such GPUs might be encountered.
.if \
	!empty(MACHINE_PLATFORM:MNetBSD-[789].*-i386) ||	\
	!empty(MACHINE_PLATFORM:MNetBSD-[789].*-x86_64) ||	\
	!empty(MACHINE_PLATFORM:MNetBSD-[789].*-sparc64)
PKG_SUGGESTED_OPTIONS+=		llvm
.endif

.if	(!empty(MACHINE_PLATFORM:MLinux-*-i386) ||	\
	 !empty(MACHINE_PLATFORM:MLinux-*-x86_64)) &&	\
	(!empty(CC_VERSION:Mgcc-4.[89].*) ||		\
	 !empty(CC_VERSION:Mgcc-[56].*))
PKG_SUGGESTED_OPTIONS+=		llvm
.endif

.if (${OPSYS} == "FreeBSD" || ${OPSYS} == "OpenBSD" ||		\
	${OPSYS} == "DragonFly" || ${OPSYS} == "Linux" ||	\
	${OPSYS} == "SunOS") || ${OPSYS} == "NetBSD"
PKG_SUGGESTED_OPTIONS+=		dri
.endif

.include "../../mk/bsd.options.mk"

# gallium
PLIST_VARS+=		swrast svga ilo i915 i965 nouveau r300 r600 radeonsi
# classic DRI
PLIST_VARS+=		dri swrast_dri i915_dri nouveau_dri i965_dri radeon_dri r200_dri

.if !empty(PKG_OPTIONS:Mdri)

CONFIGURE_ARGS+=	--enable-dri
CONFIGURE_ARGS+=	--enable-egl

# Use Thread Local Storage in GLX where it is supported by Mesa and works.
.if \
	!empty(MACHINE_PLATFORM:MLinux-*-i386) ||		\
	!empty(MACHINE_PLATFORM:MLinux-*-x86_64) ||		\
	!empty(MACHINE_PLATFORM:MFreeBSD-1[0-9].*-x86_64) ||	\
	!empty(MACHINE_PLATFORM:MDragonFly-*-x86_64)
CONFIGURE_ARGS+=	--enable-glx-tls
.else
CONFIGURE_ARGS+=	--disable-glx-tls
.endif

PLIST.dri=	yes

BUILDLINK_DEPMETHOD.libpciaccess=	full
.include "../../sysutils/libpciaccess/buildlink3.mk"
.include "../../graphics/MesaLib/dri.mk"

# Linux supports dri3
.if ${OPSYS} == "Linux"
CONFIGURE_ARGS+=	--enable-dri3
# DRI on Linux needs either sysfs or udev
CONFIGURE_ARGS+=	--enable-sysfs
.else
CONFIGURE_ARGS+=	--disable-dri3
.endif

DRI_DRIVERS=		#
PLIST.swrast_dri=	yes
DRI_DRIVERS+=		swrast

# Software rasterizer
GALLIUM_DRIVERS=	#
PLIST.swrast=		yes
GALLIUM_DRIVERS+=	swrast

.if ${MACHINE_ARCH} == "i386" || ${MACHINE_ARCH} == "x86_64"
# svga / VMWare driver
PLIST.svga=		yes
GALLIUM_DRIVERS+=	svga

# Intel chipsets, x86 only
PLIST.i915=		yes
GALLIUM_DRIVERS+=	i915
PLIST.i915_dri=		yes
DRI_DRIVERS+=		i915

# Experimental Intel driver
PLIST.ilo=		yes
GALLIUM_DRIVERS+=	ilo

PLIST.i965_dri=		yes
DRI_DRIVERS+=		i965
.endif

.if !empty(MACHINE_PLATFORM:MNetBSD-*-*arm*)
# Qualcomm SnapDragon, libdrm_freedreno.pc
# GALLIUM_DRIVERS+=	freedreno

# Broadcom VideoCore 4
# GALLIUM_DRIVERS+=	vc4

.else

# AMD Radeon r600
PLIST.r600=		yes
GALLIUM_DRIVERS+=	r600

# nVidia
PLIST.nouveau=		yes
GALLIUM_DRIVERS+=	nouveau

# classic DRI radeon
PLIST.radeon_dri=	yes
DRI_DRIVERS+=		radeon

# classic DRI r200
PLIST.r200_dri=		yes
DRI_DRIVERS+=		r200

# classic DRI nouveau
PLIST.nouveau_dri=	yes
DRI_DRIVERS+=		nouveau
.endif

CONFIGURE_ARGS+=	--with-egl-platforms=x11,drm
CONFIGURE_ARGS+=	--with-gallium-drivers=${GALLIUM_DRIVERS:ts,}
CONFIGURE_ARGS+=	--with-dri-drivers=${DRI_DRIVERS:ts,}

.if !empty(PKG_OPTIONS:Mllvm)
# AMD Radeon r300
PLIST.r300=		yes
GALLIUM_DRIVERS+=	r300
# AMD Canary Islands GPUs
PLIST.radeonsi=		yes
GALLIUM_DRIVERS+=	radeonsi
CONFIGURE_ARGS+=	--enable-gallium-llvm
CONFIGURE_ARGS+=	--enable-r600-llvm-compiler
.include "../../devel/libelf/buildlink3.mk"
CPPFLAGS+=		-I${BUILDLINK_PREFIX.libelf}/include/libelf
.include "../../lang/libLLVM/buildlink3.mk"
CONFIGURE_ENV+=		ac_cv_path_ac_pt_LLVM_CONFIG=${LLVM_CONFIG_PATH}
.else # !llvm
CONFIGURE_ARGS+=	--disable-gallium-llvm
CONFIGURE_ARGS+=	--disable-r600-llvm-compiler
.endif # llvm
.else # !dri
CONFIGURE_ARGS+=	--with-gallium-drivers=
CONFIGURE_ARGS+=	--with-dri-drivers=
CONFIGURE_ARGS+=	--disable-dri
CONFIGURE_ARGS+=	--disable-dri3
CONFIGURE_ARGS+=	--disable-egl
CONFIGURE_ARGS+=	--enable-xlib-glx
.if !empty(PKG_OPTIONS:Mllvm)
PKG_FAIL_REASON+=	"The llvm PKG_OPTION must also be disabled when dri is disabled"
.endif
.endif
