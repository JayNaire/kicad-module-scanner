TEMPLATE = lib

# TARGET is built into both the debug and release directories.
# feature flex is defined in /usr/local/QtSDK/Desktop/Qt/4.8.0/gcc/mkspecs/features/flex.prf
CONFIG += debug_and_release_target \
    flex

# in qmake.conf QMAKE_CXXFLAGS_DEBUG = -g
QMAKE_CXXFLAGS_DEBUG += -O0
TARGET = FootprintWidget
QT += core \
    gui
#footprint_lex.h is produced from footprint.l with %option header-file="footprint_lex.h"
QLALRHEADERS += footprint_grammar_p.h \
#	footprint_lex.h\
    footprint_parser.h
HEADERS += \
#    mainform.h \
    qparser.h \
#    ModWidget.h\
    ModView.h\
    Pip.h\
    $$QLALRHEADERS
QLALRSOURCES += footprint_grammar.cpp \
    footprint_parser.cpp \
    qparser.cpp
SOURCES += \
#    main.cpp \
#    mainform.cpp \
#    ModWidget.cpp\
    ModView.cpp\
    Pip.cpp\
    $$QLALRSOURCES
#FORMS += mainform.ui
RESOURCES += 
FLEXSOURCES += footprint.l
#note:LEXSOURCES has gone, FLEXSOURCES replaces it
#Because we have added CONFIG+=flex
#qmake picks up our definition for turning a .l file into a .cpp from our feature file:
# /usr/local/QtSDK/Desktop/Qt/4.8.0/gcc/mkspecs/features/flex.prf
#this uses the -o option to flex to produce file_lex.cpp directly rather then the shuffling around
#with lex that the lex.prf specifies which mucks up line/file comments in the cpp file.
#Now footprint.l will get processed by flex to directly produce: 
# footprint_lex.cpp
#Also:
# %option header-file="footprint_lex.h" will produce that file also for inclusion in QParser

