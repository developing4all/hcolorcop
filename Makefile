SHELL = /bin/sh

QTDIR=/usr/lib/qt5

DESTDIR  = /
DEST  = $(DESTDIR)/usr
qmake = $(QTDIR)/bin/qmake
lrelease = $(QTDIR)/bin/lrelease
#DEST  = /usr/local
BINPATH = $(DEST)/bin

DATAPATH = $(DEST)/share
STYLESDIR= $(DESTDIR)/$(QTDIR)/plugins/styles
DESIGDIR= $(DESTDIR)/$(QTDIR)/plugins/designer

DVERSION = 1.1.0

all: config
	cd hcolorcop ; $(qmake) hcolorcop.pro; $(MAKE)
	cd hcolorcop ; $(lrelease) hcolorcop.pro

config: Makefile
	cd hcolorcop ; \
	(echo "#define CONFDIR \"$(SHAREPATH)\"" ; \
	echo "#define DVERSION \"$(DVERSION)\"") > conf.h ;
	(echo "export DVERSION=$(DVERSION)") > config;

distclean:
	cd hcolorcop ; $(qmake); 	$(MAKE) distclean
	cd debian; rm -f hcolorcop_*
	cd lng; rm -f *.qm
	rm -f config
	rm -f *~ core config

clean:
	cd hcolorcop ; $(qmake); 	$(MAKE) clean
	cd lng; rm -f *.qm
	rm -f config
	rm -f *~ core config

dist:	distclean
	find -exec touch {} \; ; \
	d=hcolorcop-$(DVERSION) ; \
	cd .. ; \
	rm -f $${d}.tar.gz ; \
	ln -s hcolorcop $${d} ; \
	tar cvjhf $${d}.tar.bz2 $${d} ; \
	rm $${d}

install: all
	mkdir -p $(BINPATH)
	cd hcolorcop    ; install -s ./hcolorcop $(BINPATH)/hcolorcop
	mkdir -p $(DEST)/share/applications
	#mkdir -p $(DEST)/share/icons
	mkdir -p $(DEST)/share/icons/hicolor/128x128/apps
	mkdir -p $(DEST)/share/icons/gnome/128x128/apps
	install hcolorcop/images/hcolorcop-128x128.png $(DEST)/share/icons/hicolor/128x128/apps/
	#install hcolorcop/images/hcolorcop-128x128.png $(DEST)/share/icons/hcolorcop.png
	for s in 96x96 64x64 48x48 32x32 22x22 16x16; do \
		mkdir -p $(DEST)/share/icons/hicolor/$${s}/apps ;\
		mkdir -p $(DEST)/share/icons/gnome/$${s}/apps ;\
		install hcolorcop/images/hcolorcop-$${s}.png $(DEST)/share/icons/hicolor/$${s}/apps/hcolorcop.png ;\
		install hcolorcop/images/hcolorcop-$${s}.png $(DEST)/share/icons/gnome/$${s}/apps/hcolorcop.png ;\
	done
	mkdir -p $(DEST)/share/applications
	install hcolorcop.desktop $(DEST)/share/applications
#	cp ./README $(SHAREPATH)/README
#	find $(SHAREPATH) -type d -name CVS | xargs rm -rf

