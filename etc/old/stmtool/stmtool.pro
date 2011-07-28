# #################################################################
# stmtool
# (C) 2011 by Jens Oliver John <jens.o.john@gmail.com>
# #################################################################
TEMPLATE = app
TARGET = stmtool
QT += core \
    gui \
    xml
CONFIG += warn_off
HEADERS += ComputationController/filters/Placeholder.h \
    general/StmtLib.h \
    general/StmtTypedefs.h \
    ComputationController/filters/SF_SDMSave.h \
    ComputationController/FilterTable.h \
    ComputationController/StackableFilter.h \
    ComputationController/ComputationController.h \
    general/StmtComponentDock.h \
    general/StmtComponent.h \
    general/MyUndoer.h \
    general/maindefs.h \
    gui/colorScales/CSVDisplayDock.h \
    general/HelperMacros.h \
    gui/colorScales/GradientScrollbar.h \
    gui/colorScales/GradientLabel.h \
    gui/GuiHelper/GuiHelper.h \
    main-doc.h \
    viewportManager/viewportManager.h \
    sdm/SDMB_openWidget.h \
    general/DebugMacros.h \
    gui/colorScales/MyColorScale.h \
    gui/colorScales/ColorOperations.h \
    gui/colorScales/ColorScaleLoader.h \
    gui/colorScales/ColorScaleViewer.h \
    gui/colorScales/CSKodak1.h \
    gui/colorScales/ColorScale.h \
    sdm/SDMBrowser.h \
    viewport/RenderArea.h \
    viewport/Viewport.h \
    devices/iDevice.h \
    devices/stmData.h \
    sdm/SDM.h \
    gui/mightyEditor/cwBoolean.h \
    gui/mightyEditor/keyValueDialog.h \
    gui/mightyEditor/mightyEditor.h \
    gui/homeWidget/homeWidget.h \
    gui/logViewDialog/logDirBrowser.h \
    gui/deviceSelector/dsLWI.h \
    gui/deviceSelector/deviceSelector.h \
    deviceManager/deviceManager.h \
    gui/logViewDialog/logLWI.h \
    gui/logViewDialog/logViewDialog.h \
    gui/prefDialog/prefDialog.h \
    gui/aboutDialog/aboutDialog.h \
    general/stmr.h \
    general/eStmError.h \
    settingsManager/settingsManager.h \
    core/Core.h \
    gui/baseWindow/baseWindow.h
SOURCES += ComputationController/filters/SF_SDMSave.cpp \
    ComputationController/FilterTable.cpp \
    ComputationController/ComputationController.cpp \
    general/StmtComponentDock.cpp \
    gui/colorScales/CSVDisplayDock.cpp \
    gui/colorScales/GradientScrollbar.cpp \
    gui/colorScales/GradientLabel.cpp \
    viewportManager/viewportManager.cpp \
    sdm/SDMB_openWidget.cpp \
    gui/colorScales/MyColorScale.cpp \
    gui/colorScales/ColorScaleLoader.cpp \
    gui/colorScales/ColorScaleViewer.cpp \
    gui/colorScales/CSKodak1.cpp \
    sdm/SDMBrowser.cpp \
    viewport/RenderArea.cpp \
    viewport/Viewport.cpp \
    devices/stmData.cpp \
    sdm/SDM.cpp \
    gui/mightyEditor/cwBoolean.cpp \
    gui/mightyEditor/keyValueDialog.cpp \
    gui/mightyEditor/mightyEditor.cpp \
    gui/homeWidget/homeWidget.cpp \
    gui/logViewDialog/logDirBrowser.cpp \
    gui/deviceSelector/dsLWI.cpp \
    gui/deviceSelector/deviceSelector.cpp \
    deviceManager/deviceManager.cpp \
    gui/logViewDialog/lvd_slots.cpp \
    gui/logViewDialog/logLWI.cpp \
    gui/logViewDialog/logViewDialog.cpp \
    gui/prefDialog/prefDialog_slots.cpp \
    gui/prefDialog/prefDialog.cpp \
    gui/aboutDialog/aboutDialog.cpp \
    gui/baseWindow/slots.cpp \
    settingsManager/settingsManager.cpp \
    core/Core.cpp \
    gui/baseWindow/baseWindow.cpp \
    main.cpp
FORMS += gui/colorScales/GradientLabel.ui \
    sdm/SDMB_openWidget.ui \
    gui/colorScales/ColorScaleViewer.ui \
    sdm/SDMBrowser.ui \
    viewport/RenderArea.ui \
    viewport/Viewport.ui \
    gui/mightyEditor/cwBoolean.ui \
    gui/mightyEditor/keyValueDialog.ui \
    gui/mightyEditor/mightyEditor.ui \
    gui/homeWidget/homeWidget.ui \
    gui/logViewDialog/logDirBrowser.ui \
    gui/deviceSelector/deviceSelector.ui \
    gui/logViewDialog/logViewDialog.ui \
    gui/prefDialog/prefDialog.ui \
    gui/aboutDialog/aboutDialog.ui \
    gui/baseWindow/baseWindow.ui

# #################################################################
# FOR GRAPHICAL RESOURCES
RESOURCES += ../res/guires.qrc

# #################################################################
# FOR STATIC PLUGINS
LIBS += -L \
    ../color-scales/static \
    -lcolorScale_KODAK1

# #################################################################
# FOR LIBSHERLOG
INCLUDEPATH += ../libsherlog/src
LIBS += -L../libsherlog/bin \
    -lsherlog

# #################################################################
# LIBCIMG
INCLUDEPATH += ../libcimg
LIBS *= -lm \
    -lX11

# for fast image display
# QMAKE_CXXFLAGS += -Dcimg_use_xshm
# LIBS *= -lXext
# for screen mode switching
# QMAKE_CXXFLAGS += -Dcimg_use_xrandr
# LIBS *= -lXrandr
# for native png support (-lz is basically defined by qt)
# QMAKE_CXXFLAGS += -Dcimg_use_png
# LIBS *= -lpng
# for native jpeg support
# QMAKE_CXXFLAGS += -Dcimg_use_jpeg
# LIBS *= -ljpeg
# for native tiff support
# QMAKE_CXXFLAGS += -Dcimg_use_tiff
# LIBS *= -ltiff
# for libmagick++
# MAGICK_CXX_FLAGS = $$system(Magick++-config --cxxflags)
# MAGICK_INCLUDE_PATHS = $$system(Magick++-config --cppflags)
# MAGICK_LDFLAGS = $$system(Magick++-config --ldflags)
# MAGICK_LIBS = $$system(Magick++-config --libs)
# LIBS *= $${MAGICK_LIBS}
# LIBS *= $${MAGICK_LDFLAGS}
# QMAKE_CXXFLAGS *= $${MAGICK_CXX_FLAGS}
# INCLUDEPATH *= $${MAGICK_INCLUDE_PATH}
# for fast fourier transformation (fftw3 library)
# QMAKE_CXXFLAGS += -Dcimg_use_fftw3
# LIBS += -lfftw3
# #################################################################
# FOR ADDITIONAL LOGGING
DEFINES += DEBUG
# #################################################################
# FOR KEEPING EVERYTHING NEATLY ARRANGED
MOC_DIR = ./moc
OBJECTS_DIR = ./built
DESTDIR = ./bin
RCC_DIR = ./built
UI_DIR = ./built
