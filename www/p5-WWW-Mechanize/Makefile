# $NetBSD: Makefile,v 1.34 2013/05/31 12:42:53 wiz Exp $

DISTNAME=	WWW-Mechanize-1.72
PKGNAME=	p5-${DISTNAME}
PKGREVISION=	3
CATEGORIES=	www perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=WWW/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://search.cpan.org/dist/WWW-Mechanize/
COMMENT=	Automates web page form & link interaction
LICENSE=	${PERL5_LICENSE}

DEPENDS+=	p5-HTML-Form>=6.00:../../www/p5-HTML-Form
DEPENDS+=	p5-HTML-Parser>=3.33:../../www/p5-HTML-Parser
DEPENDS+=	p5-HTML-Tree-[0-9]*:../../www/p5-HTML-Tree
DEPENDS+=	p5-HTTP-Daemon-[0-9]*:../../www/p5-HTTP-Daemon
DEPENDS+=	p5-HTTP-Message>=1.3:../../www/p5-HTTP-Message
DEPENDS+=	p5-HTTP-Server-Simple>=0.35:../../www/p5-HTTP-Server-Simple
DEPENDS+=	p5-URI>=1.36:../../www/p5-URI
DEPENDS+=	p5-libwww>=5.829:../../www/p5-libwww
# recommended for HTML::Tree ...
DEPENDS+=	p5-HTML-Format-[0-9]*:../../www/p5-HTML-Format

BUILD_DEPENDS+=	p5-Test-Memory-Cycle-[0-9]*:../../devel/p5-Test-Memory-Cycle
BUILD_DEPENDS+=	p5-Test-Pod-[0-9]*:../../devel/p5-Test-Pod
BUILD_DEPENDS+=	p5-Test-Taint-[0-9]*:../../devel/p5-Test-Taint
BUILD_DEPENDS+=	p5-Test-Warn>=0.11:../../devel/p5-Test-Warn

# use defaults from Makefile.PL, to avoid user interaction
# if not set explicitly
MAKE_PARAMS+=	--mech-dump --nolive

PKG_INSTALLATION_TYPES=	overwrite pkgviews

USE_LANGUAGES=	# empty
PERL5_PACKLIST=	auto/WWW/Mechanize/.packlist

.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"
