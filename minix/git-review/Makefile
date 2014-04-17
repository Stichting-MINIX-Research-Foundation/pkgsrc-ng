# $NetBSD$
#
DISTNAME=	git-review-1.21
CATEGORIES=	devel
MASTER_SITES=	http://www.minix3.org/distfiles-minix/

MAINTAINER=	Kees Jongenburger <keesj@minix3.org>
HOMEPAGE=	http://www.minix3.org/distfiles-minix/
COMMENT=	A git command for submitting branches to Gerrit
LICENSE=	apache-2.0

DEPENDS+=       ${PYPKGPREFIX}-setuptools>=0.6c9:../../devel/py-setuptools
PYTHON_VERSIONS_ACCEPTED= 27
PYDISTUTILSPKG=yes
REPLACE_PYTHON=   *.py
PKG_DESTDIR_SUPPORT=	user-destdir
USE_LANGUAGES=	# none

.include "../../lang/python/extension.mk"
.include "../../mk/bsd.pkg.mk"
