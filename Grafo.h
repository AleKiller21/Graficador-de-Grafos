#ifndef GRAFO_H
#define GRAFO_H

#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "Vertice.h"

template <class T>
class Grafo : public QGraphicsScene
{
public:
    Lista<Vertice<T>*> vertices;
    Lista<Arista<T>*> aristas;

    //Grafo() {}

    bool validarVertice(T valor)
    {
        for(int i = 0; i < vertices.getCantidad(); i++)
        {
            if(vertices.obtenerValor(i)->valor == valor)
            {
                throw new std::exception;
            }
        }

        return true;
    }

    Vertice<T>* obtenerVertice(T valor)
    {
        for(int i = 0; i < vertices.getCantidad(); i++)
        {
            if(vertices.obtenerValor(i)->valor == valor)
                return vertices.obtenerValor(i);
        }

        return NULL;
    }

    Arista<T>* obtenerArista(T origen, T destino)
    {
        for(int i = 0; i < aristas.getCantidad(); i++)
        {
            if(aristas.obtenerValor(i)->origen == origen && aristas.obtenerValor(i)->destino == destino)
                return aristas.obtenerValor(i);
        }

        return NULL;
    }

    void agregarVertice(T valor)
    {
        if(validarVertice(valor))
        {
            Vertice<T>* vertice = new Vertice<T>(valor);
            addItem(vertice);
            vertices.agregar(vertice);
            vertice->setFlag(QGraphicsItem::ItemIsMovable);
            vertice->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
        }

        //BORRAR
        else
            std::cout << "Ya existe un vertice con el mismo valor. Cambiar el valor" << std::endl;
    }

    void agregarArista(T origen, T destino, int peso, bool no_dirigido)
    {
        Vertice<T>* ver_origen = obtenerVertice(origen);
        Vertice<T>* ver_destino = obtenerVertice(destino);

        if(ver_origen != NULL && ver_destino != NULL)
        {
            Arista<T>* arista = new Arista<T>(ver_origen, ver_destino, peso);
            aristas.agregar(arista);
            ver_origen->aristas.agregar(arista);
            ver_destino->aristas_destino.agregar(arista);

            arista->line = addLine(ver_origen->pos().x()+50, ver_origen->pos().y()+50, ver_destino->pos().x(), ver_destino->pos().y()+50);
            QGraphicsEllipseItem* punto = addEllipse(ver_destino->pos().x(), ver_destino->pos().y()+50, 6, 6, QPen(), QBrush(Qt::SolidPattern));
            ver_destino->puntos.agregar(punto);

            arista->text = addText(QString::number(peso));
            arista->text->setPos((ver_origen->pos().x() + ver_destino->pos().x())/2, (ver_origen->pos().y() + ver_destino->pos().y())/2);

            if(no_dirigido)
            {
                Arista<T>* arista2 = new Arista<T>(ver_destino, ver_origen, peso);
                aristas.agregar(arista2);
                ver_destino->aristas.agregar(arista2);
                //ver_origen->aristas_destino.agregar(arista2);
            }
        }
    }

    int** crearMatrizAdyacencia()
    {
        int cantidad = vertices.getCantidad();
        int** matriz = new int*[cantidad];

        if(cantidad == 0 && aristas.getCantidad() == 0)
            return NULL;

        for(int i = 0; i < cantidad; i++)
        {
            matriz[i] = new int[cantidad];
        }

        for(int i = 0; i < aristas.getCantidad(); i++)
        {
            int origen = vertices.obtenerPosicion(aristas.obtenerValor(i)->origen);
            int destino = vertices.obtenerPosicion(aristas.obtenerValor(i)->destino);
            matriz[origen][destino] = aristas.obtenerValor(i)->peso;
        }

        return matriz;
    }

    void borrarMatriz(int** matriz)
    {
        int cantidad = vertices.getCantidad();

        for(int i = 0; i < cantidad; i++)
        {
            for(int j = 0; j < cantidad; j++)
            {
                delete[] matriz[i];
            }
        }

        delete[] matriz;
    }

    virtual ~Grafo() {}
};

#endif // GRAFO_H
