# $NetBSD: Makefile,v 1.6 2014/02/16 21:39:14 rodent Exp $

DISTNAME=	v1.4.3
PKGNAME=	${DISTNAME:S/v/${PYPKGPREFIX}-amqp-/1}
CATEGORIES=	net
MASTER_SITES=	https://github.com/celery/py-amqp/archive/
DIST_SUBDIR=	${PKGBASE:S/${PYPKGPREFIX}/py/1}

MAINTAINER=	rodent@NetBSD.org
HOMEPAGE=	http://amqp.readthedocs.org/
COMMENT=	Python AMQP 0.9.1 client library
LICENSE=	gnu-lgpl-v2.1

WRKSRC=		${WRKDIR}/${PKGNAME_NOREV:S/${PYPKGPREFIX}/py/1}
USE_LANGUAGES=	# none
EGG_NAME=	${DISTNAME:S/v/amqp-/1}

.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
