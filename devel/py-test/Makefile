# $NetBSD: Makefile,v 1.3 2014/03/21 23:58:47 wiz Exp $

DISTNAME=	pytest-2.5.2
PKGNAME=	${PYPKGPREFIX}-${DISTNAME:S/py//}
PKGREVISION=	1
CATEGORIES=	devel
MASTER_SITES=	https://pypi.python.org/packages/source/p/pytest/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://pypi.python.org/pypi/pytest
COMMENT=	Python testing tool
LICENSE=	mit

DEPENDS+=	${PYPKGPREFIX}-py>=1.4.20:../../devel/py-py
DEPENDS+=	${PYPKGPREFIX}-expat-[0-9]*:../../textproc/py-expat
# actually, test dependencies
BUILD_DEPENDS+=	${PYPKGPREFIX}-yaml-[0-9]*:../../textproc/py-yaml
USE_TOOLS+=	bash:build

CONFLICTS=	${PYPKGPREFIX}-pytest-[0-9]*

USE_LANGUAGES=	# none

PLIST_SUBST+=	PYVERSSUFFIX=${PYVERSSUFFIX}

REPLACE_PYTHON+=	_pytest/standalonetemplate.py

.include "../../lang/python/application.mk"
.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
