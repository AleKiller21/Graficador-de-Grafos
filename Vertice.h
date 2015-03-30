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
    Lista<Arista<T>*> aristas;//Aristas que parten de mi
    Lista<Arista<T>*> aristas_destino;//Aristas que vienen a mi
    Lista<QGraphicsEllipseItem*> puntos;

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

    QVariant itemChange(GraphicsItemChange change, const QVariant &value)
    {
        if(change == ItemPositionHasChanged)
        {
            for(int i = 0; i < aristas.getCantidad(); i++)
            {
                Arista<T>* arista = aristas.obtenerValor(i);
                arista->line->setLine(pos().x()+50, pos().y()+50, arista->destino->pos().x(), arista->destino->pos().y()+50);
                arista->text->setPos((pos().x() + arista->destino->pos().x())/2, (pos().y() + arista->destino->pos().y())/2);
            }

            for(int i = 0; i < aristas_destino.getCantidad(); i++)
            {
                Arista<T>* arista = aristas_destino.obtenerValor(i);
                QGraphicsEllipseItem* punto = puntos.obtenerValor(i);
                arista->line->setLine(arista->origen->pos().x()+50, arista->origen->pos().y()+50, pos().x(), pos().y()+50);
                arista->text->setPos((arista->origen->pos().x() + pos().x())/2, (arista->origen->pos().y() + pos().y())/2);
                //punto->setRect( pos().x(), pos().y()+50, 6, 6);
            }

            for(int i = 0; i < puntos.getCantidad(); i++)
            {
                puntos.obtenerValor(i)->setRect( pos().x(), pos().y()+50, 6, 6);
            }
        }

        return QGraphicsItem::itemChange(change, value);
    }

    virtual ~Vertice() {}
};

#endif // VERTICE_H
