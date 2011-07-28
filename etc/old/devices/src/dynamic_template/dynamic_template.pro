TEMPLATE = lib
CONFIG += plugin
TARGET = $$qtLibraryTarget(stmDeviceTemplate)
QT += core \
    gui
HEADERS += src/widgets/PrimaryParametricWidget.h \
    src/widgets/ControllingWidget.h \
    src/stmDevice.h
SOURCES += src/widgets/PrimaryParametricWidget.cpp \
    src/widgets/ControllingWidget.cpp \
    src/stmDevice.cpp
FORMS += src/widgets/PrimaryParametricWidget.ui \
    src/widgets/ControllingWidget.ui
RESOURCES += 

# device interface & stuff
INCLUDEPATH += ../../../stmtool/devices

# keep the working directory clean
MOC_DIR = ./moc
OBJECTS_DIR = ./built
DESTDIR = ../../dynamic
RCC_DIR = ./built
UI_DIR = ./built
