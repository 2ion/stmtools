#############################################################################
# Makefile for building: libfrom-file.so
# Generated by qmake (2.01a) (Qt 4.7.2) on: Wed Apr 6 13:31:32 2011
# Project:  from-file.pro
# Template: lib
# Command: /usr/bin/qmake -o Makefile from-file.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DDEBUG -DQT_NO_DEBUG -DQT_PLUGIN -DQT_WEBKIT_LIB -DQT_SVG_LIB -DQT_XML_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtSvg -I/usr/include/qt4/QtWebKit -I/usr/include/qt4 -I../../../stmtool/devices -Imoc -Ibuilt
LINK          = g++
LFLAGS        = -Wl,-O1 -shared
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtWebKit -lQtSvg -lQtXml -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = built/

####### Files

SOURCES       = src/widgets/PrimaryParametricWidget.cpp \
		src/widgets/ControllingWidget.cpp \
		src/stmDevice.cpp moc/moc_PrimaryParametricWidget.cpp \
		moc/moc_ControllingWidget.cpp \
		moc/moc_stmDevice.cpp
OBJECTS       = built/PrimaryParametricWidget.o \
		built/ControllingWidget.o \
		built/stmDevice.o \
		built/moc_PrimaryParametricWidget.o \
		built/moc_ControllingWidget.o \
		built/moc_stmDevice.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		from-file.pro
QMAKE_TARGET  = from-file
DESTDIR       = ../../dynamic/
TARGET        = libfrom-file.so
TARGETD       = libfrom-file.so

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile  ../../dynamic/$(TARGET)

../../dynamic/$(TARGET): built/ui_PrimaryParametricWidget.h built/ui_ControllingWidget.h $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	@$(CHK_DIR_EXISTS) ../../dynamic/ || $(MKDIR) ../../dynamic/ 
	-$(DEL_FILE) $(TARGET)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-$(MOVE) $(TARGET) ../../dynamic/



Makefile: from-file.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/libQtWebKit.prl \
		/usr/lib/libQtSvg.prl \
		/usr/lib/libQtXml.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -o Makefile from-file.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/libQtWebKit.prl:
/usr/lib/libQtSvg.prl:
/usr/lib/libQtXml.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile from-file.pro

dist: 
	@$(CHK_DIR_EXISTS) built/from-file1.0.0 || $(MKDIR) built/from-file1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) built/from-file1.0.0/ && $(COPY_FILE) --parents src/mkxml/GMakeXml.h src/mkxml/mkxml.h src/widgets/PrimaryParametricWidget.h src/widgets/ControllingWidget.h src/stmDevice.h built/from-file1.0.0/ && $(COPY_FILE) --parents src/widgets/PrimaryParametricWidget.cpp src/widgets/ControllingWidget.cpp src/stmDevice.cpp built/from-file1.0.0/ && $(COPY_FILE) --parents src/widgets/PrimaryParametricWidget.ui src/widgets/ControllingWidget.ui built/from-file1.0.0/ && (cd `dirname built/from-file1.0.0` && $(TAR) from-file1.0.0.tar from-file1.0.0 && $(COMPRESS) from-file1.0.0.tar) && $(MOVE) `dirname built/from-file1.0.0`/from-file1.0.0.tar.gz . && $(DEL_FILE) -r built/from-file1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc/moc_PrimaryParametricWidget.cpp moc/moc_ControllingWidget.cpp moc/moc_stmDevice.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc/moc_PrimaryParametricWidget.cpp moc/moc_ControllingWidget.cpp moc/moc_stmDevice.cpp
moc/moc_PrimaryParametricWidget.cpp: built/ui_PrimaryParametricWidget.h \
		src/widgets/PrimaryParametricWidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/widgets/PrimaryParametricWidget.h -o moc/moc_PrimaryParametricWidget.cpp

moc/moc_ControllingWidget.cpp: built/ui_ControllingWidget.h \
		src/mkxml/mkxml.h \
		src/stmDevice.h \
		src/widgets/ControllingWidget.h \
		src/mkxml/GMakeXml.h \
		src/widgets/PrimaryParametricWidget.h \
		built/ui_PrimaryParametricWidget.h \
		src/widgets/ControllingWidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/widgets/ControllingWidget.h -o moc/moc_ControllingWidget.cpp

moc/moc_stmDevice.cpp: src/widgets/ControllingWidget.h \
		built/ui_ControllingWidget.h \
		src/mkxml/mkxml.h \
		src/stmDevice.h \
		src/widgets/PrimaryParametricWidget.h \
		built/ui_PrimaryParametricWidget.h \
		src/mkxml/GMakeXml.h \
		src/stmDevice.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/stmDevice.h -o moc/moc_stmDevice.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: built/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) built/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: built/ui_PrimaryParametricWidget.h built/ui_ControllingWidget.h
compiler_uic_clean:
	-$(DEL_FILE) built/ui_PrimaryParametricWidget.h built/ui_ControllingWidget.h
built/ui_PrimaryParametricWidget.h: src/widgets/PrimaryParametricWidget.ui
	/usr/bin/uic-qt4 src/widgets/PrimaryParametricWidget.ui -o built/ui_PrimaryParametricWidget.h

built/ui_ControllingWidget.h: src/widgets/ControllingWidget.ui
	/usr/bin/uic-qt4 src/widgets/ControllingWidget.ui -o built/ui_ControllingWidget.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

built/PrimaryParametricWidget.o: src/widgets/PrimaryParametricWidget.cpp src/widgets/PrimaryParametricWidget.h \
		built/ui_PrimaryParametricWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o built/PrimaryParametricWidget.o src/widgets/PrimaryParametricWidget.cpp

built/ControllingWidget.o: src/widgets/ControllingWidget.cpp src/widgets/ControllingWidget.h \
		built/ui_ControllingWidget.h \
		src/mkxml/mkxml.h \
		src/stmDevice.h \
		src/widgets/PrimaryParametricWidget.h \
		built/ui_PrimaryParametricWidget.h \
		src/mkxml/GMakeXml.h \
		src/widgets/xmacro_qimg_formats.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o built/ControllingWidget.o src/widgets/ControllingWidget.cpp

built/stmDevice.o: src/stmDevice.cpp src/stmDevice.h \
		src/widgets/ControllingWidget.h \
		built/ui_ControllingWidget.h \
		src/mkxml/mkxml.h \
		src/mkxml/GMakeXml.h \
		src/widgets/PrimaryParametricWidget.h \
		built/ui_PrimaryParametricWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o built/stmDevice.o src/stmDevice.cpp

built/moc_PrimaryParametricWidget.o: moc/moc_PrimaryParametricWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o built/moc_PrimaryParametricWidget.o moc/moc_PrimaryParametricWidget.cpp

built/moc_ControllingWidget.o: moc/moc_ControllingWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o built/moc_ControllingWidget.o moc/moc_ControllingWidget.cpp

built/moc_stmDevice.o: moc/moc_stmDevice.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o built/moc_stmDevice.o moc/moc_stmDevice.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

