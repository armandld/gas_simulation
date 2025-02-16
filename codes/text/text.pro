QMAKE_CXXFLAGS += -std=c++17 -g

CONFIG += console

TARGET = version_finale_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    Test_ExerciceP14.cc \
    Textviewer.cc

HEADERS += \
    ../general/Systeme.h \
    Textviewer.h \
    ../general/Dessinable.h \
    ../general/SupportADessin.h

