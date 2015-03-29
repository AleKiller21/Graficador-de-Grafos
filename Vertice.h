#ifndef VERTICE_H
#define VERTICE_H

#include <QGraphicsItem>
#include <QPainter>
#include "Lista.h"
#include "Lista.cpp"
#include "Arista.h"

template <class T>
class Vertice : public QGraphicsItem
{
public:
    T valor;
    Lista<Arista<T>*> aristas;

    Vertice(T valor)
    {
        this->valor = valor;
    }

    QRectF boundingRect() const
    {
        return QRectF(0, 0, 100, 100);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        QBrush brush(Qt::red);
        QRectF rect = boundingRect();
        painter->fillRect(rect, brush);
        painter->drawRect(rect);
        painter->setFont(QFont("Arial", 12, QFont::Bold));
        painter->drawText(rect, valor);
    }

    virtual ~Vertice() {}
};

#endif // VERTICE_H
