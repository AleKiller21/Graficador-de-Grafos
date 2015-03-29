#ifndef ARISTA_H
#define ARISTA_H

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>

template <class T>
class Vertice;

template <class T>
class Arista
{
public:
    Vertice<T>* origen;
    Vertice<T>* destino;
    QGraphicsLineItem* line;
    QGraphicsTextItem* text;
    int peso;

    Arista(Vertice<T>* origen, Vertice<T>* destino, int peso)
    {
        this->origen = origen;
        this->destino = destino;
        this->peso = peso;
        this->line = NULL;
        this->text = NULL;
    }

    virtual ~Arista() {}
};

#endif // ARISTA_H
