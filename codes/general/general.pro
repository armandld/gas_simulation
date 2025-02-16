TEMPLATE = lib

CONFIG = staticlib
QMAKE_CXXFLAGS += -std=c++17 -g

SOURCES = \
    Dessinable.cc \
    Enceinte.cc \
    GenerateurAleatoire.cc \
    Particule.cc \
    SupportADessin.cc \
    Systeme.cc \
    Vecteur3D.cc

HEADERS += \
    Dessinable.h \
    Enceinte.h \
    GenerateurAleatoire.h \
    Particule.h \
    SupportADessin.h \
    Systeme.h \
    Vecteur3D.h
