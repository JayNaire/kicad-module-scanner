TEMPLATE = app
#TARGET is built into both the debug and release directories.
CONFIG += debug_and_release_target
#in qmake.conf QMAKE_CXXFLAGS_DEBUG = -g
QMAKE_CXXFLAGS_DEBUG += -O0
TARGET = kicad_module_scanner
QT += core \
    gui \
    xml \
    xmlpatterns
HEADERS += main.h \
    kicad_module_scanner.h
#    /home/root/Projects/kicad-module-scanner/FootprintWidget/ModView.h
SOURCES += main.cpp \
    kicad_module_scanner.cpp
FORMS += kicad_module_scanner.ui \
    kicad_module_scanner.ui
RESOURCES += 
#LIBS += -lm -L/home/root/Projects/kicad-module-scanner/FootprintWidget/debug/ -lFootprintWidget
LIBS += -lm -L../FootprintWidget/debug/ -lFootprintWidget
#LIBS += -l/home/root/Projects/kicad-module-scanner/FootprintWidget/debug/libFootprintWidget.so
#INCLUDEPATH += /home/root/Projects/kicad-module-scanner/FootprintWidget
INCLUDEPATH += ../FootprintWidget