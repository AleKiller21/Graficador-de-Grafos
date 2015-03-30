#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T18:11:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProyecoFinalGrafo
TEMPLATE = app


SOURCES += main.cpp\
        graficador.cpp \
    Lista.cpp \
    Nodo.cpp \
    grafoseleccion.cpp

HEADERS  += graficador.h \
    Arista.h \
    Grafo.h \
    Lista.h \
    Nodo.h \
    Vertice.h \
    grafoseleccion.h

FORMS    += graficador.ui \
    grafoseleccion.ui
