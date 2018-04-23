TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = hcolorcop
DEPENDPATH += . release
CONFIG += release
INCLUDEPATH += .

RC_FILE = hcolorcop.rc
RESOURCES = hcolorcop.qrc

# Input
HEADERS += hcolorcop.h hscreenwidget.h hscreencolors.h
FORMS += hcolorcop.ui
SOURCES += hcolorcop.cpp hscreenwidget.cpp main.cpp hscreencolors.cpp

TRANSLATIONS    = ../lng/hcolorcop_ar.ts \
                  ../lng/hcolorcop_nl.ts \
                  ../lng/hcolorcop_es.ts \
                  ../lng/hcolorcop_fr.ts \
                  ../lng/hcolorcop_tr.ts
