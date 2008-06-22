SHELL = /bin/sh

QTDIR=/usr/share/qt4

ROOT  = /
DEST  = $(ROOT)/usr
qmake = $(QTDIR)/bin/qmake
lrelease = $(QTDIR)/bin/lrelease
#DEST  = /usr/local
BINPATH = $(DEST)/bin

DATAPATH = $(DEST)/share
STYLESDIR= $(ROOT)/$(QTDIR)/plugins/styles
DESIGDIR= $(ROOT)/$(QTDIR)/plugins/designer

DVERSION = 0.9.0

all: config
	cd hcolorcop ; $(qmake) hcolorcop.pro; $(MAKE)
#	cd hcolorcop ; $(qmake); $(lrelease) hcolorcop.pro \


config: Makefile
	
	cd hcolorcop ; \
	(echo "#define CONFDIR \"$(SHAREPATH)\"" ; \
	echo "#define DVERSION \"$(DVERSION)\"") > conf.h ;
	
	(echo "export DVERSION=$(DVERSION)") > config;
	
distclean:
	cd hcolorcop ; $(qmake); 	$(MAKE) distclean
#	cd debian; rm -f hde_* libhde_*
	rm -f config
	rm -f *~ core config

clean:
	cd hcolorcop ; $(qmake); 	$(MAKE) clean
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
#	cp ./README $(SHAREPATH)/README
	
#	find $(SHAREPATH) -type d -name CVS | xargs rm -rf

