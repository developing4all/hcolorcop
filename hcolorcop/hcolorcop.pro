TEMPLATE = app
TARGET = 
DEPENDPATH += . release
INCLUDEPATH += .

RC_FILE = hcolorcop.rc

# Input
HEADERS += hcolorcop.h hscreenwidget.h hscreencolors.h
FORMS += hcolorcop.ui
SOURCES += hcolorcop.cpp hscreenwidget.cpp main.cpp hscreencolors.cpp
RESOURCES += hcolorcop.qrc

TRANSLATIONS    = ../lng/hcolorcop_ar.ts \
                  ../lng/hcolorcop_nl.ts \
                  ../lng/hcolorcop_es.ts \
                  ../lng/hcolorcop_fr.ts \
                  ../lng/hcolorcop_tr.ts
