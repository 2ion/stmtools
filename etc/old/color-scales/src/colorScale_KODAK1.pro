TEMPLATE = lib
DESTDIR = ../static
CONFIG += plugin \
    static
TARGET = $$qtLibraryTarget(colorScale_KODAK1)
MAKEFILE = Makefile.$${TARGET}
QT += core \
    gui
HEADERS += colorScale_KODAK1.h
SOURCES += colorScale_KODAK1.cpp
FORMS += 
RESOURCES += 
INCLUDEPATH += ../../stmtool/gui/colorScales
