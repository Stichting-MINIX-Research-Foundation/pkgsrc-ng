# $NetBSD: Makefile,v 1.11 2014/01/09 12:07:42 jperkin Exp $
#

DISTNAME=		mapm-4.9.5a
CATEGORIES=		math
MASTER_SITES=		http://www.tc.umn.edu/~ringx004/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://www.tc.umn.edu/~ringx004/mapm-main.html
COMMENT=		Arbitrary Precision Math library

WRKSRC=		${WRKDIR}/${DISTNAME:S/-/_/}

DOCS=	README algorithms.used function.ref article.pdf

USE_LANGUAGES=	c c++

INSTALLATION_DIRS=	bin include lib share/doc/mapm

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "SunOS"
BUILDLINK_TRANSFORM+=	rm:-static
.endif

do-install:
	${INSTALL_DATA} ${WRKSRC}/m_apm.h ${DESTDIR}${PREFIX}/include
	${INSTALL_DATA} ${WRKSRC}/libmapm.a ${DESTDIR}${PREFIX}/lib
	${INSTALL_PROGRAM} ${WRKSRC}/calc ${DESTDIR}${PREFIX}/bin/mapm-calc
	cd ${WRKSRC}/DOCS; for f in ${DOCS}; do \
		${INSTALL_DATA} $$f ${DESTDIR}${PREFIX}/share/doc/mapm; \
	done

do-test:
	cd ${WRKSRC} && ./validate

.include "../../mk/bsd.pkg.mk"
