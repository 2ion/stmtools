# qt project: sherlog
# shared library, part of stmtool

TEMPLATE = lib
TARGET = sherlog
QT += core
HEADERS += src/Sherlog.h \
    src/global_header.h
SOURCES += src/Sherlog.cpp
DEFINES += SHERLOG_LIBRARY
# uncomment to enable debug messages
#DEFINES *= SHERLOG_DEBUG
DESTDIR = ./bin
MOC_DIR = ./moc
OBJECTS_DIR = ./built
RCC_DIR = ./built
UI_DIR = ./built
library.path = /usr/local/lib
library.files += bin/*
INSTALLS += library
VERSION = 2.0.0
