# $NetBSD: Makefile,v 1.13 2013/07/15 02:02:18 ryoon Exp $

DISTNAME=	ysmv7_2_9_9_1
PKGNAME=	ysm-2.9.9.1
CATEGORIES=	chat
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=ysmv7/}

MAINTAINER=	dawszy@arhea.net
HOMEPAGE=	http://ysmv7.sourceforge.net/
COMMENT=	The 'You Sick Me' terminal based ICQ client
LICENSE=	gnu-gpl-v2

GNU_CONFIGURE=		YES

# rl_delete_text
.include "../../devel/readline/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
