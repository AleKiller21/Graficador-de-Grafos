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
    int tipo_grafo;

    Grafo(int tipo_grafo)
    {
        this->tipo_grafo = tipo_grafo;
    }

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
            Vertice<T>* vertice = new Vertice<T>(valor, tipo_grafo);
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

            if(no_dirigido)
            {
                Arista<T>* arista2 = new Arista<T>(ver_destino, ver_origen, peso);
                aristas.agregar(arista2);
                ver_destino->aristas.agregar(arista2);
                ver_origen->aristas_destino.agregar(arista2);

                arista->line = addLine(ver_origen->pos().x()+100, ver_origen->pos().y()+50, ver_destino->pos().x(), ver_destino->pos().y()+50);
            }

            else
            {
                arista->line = addLine(ver_origen->pos().x()+100, ver_origen->pos().y()+50, ver_destino->pos().x(), ver_destino->pos().y()+50);
                QGraphicsEllipseItem* punto = addEllipse(ver_destino->pos().x(), ver_destino->pos().y()+50, 6, 6, QPen(), QBrush(Qt::SolidPattern));
                ver_destino->puntos.agregar(punto);
            }

            arista->text = addText(QString::number(peso));
            arista->text->setPos((ver_origen->pos().x() + ver_destino->pos().x())/2, (ver_origen->pos().y() + ver_destino->pos().y())/2);
        }
    }

    void eliminarArista(T origen, T destino)
    {
        Vertice<T>* ver_origen = obtenerVertice(origen);
        Vertice<T>* ver_destino = obtenerVertice(destino);
        Arista<T>* arista = NULL;

        for(int i = 0; i < ver_origen->aristas.getCantidad(); i++)
        {
            if(ver_origen->aristas.obtenerValor(i)->destino == ver_destino)
            {
                if(ver_origen->aristas.obtenerValor(i)->line != NULL)
                    removeItem(ver_origen->aristas.obtenerValor(i)->line);

                if(ver_origen->aristas.obtenerValor(i)->text != NULL)
                    removeItem(ver_origen->aristas.obtenerValor(i)->text);

                ver_origen->aristas.eliminar(i);
                break;
            }
        }

        for(int i = 0; i < ver_destino->aristas_destino.getCantidad(); i++)
        {
            if(ver_destino->aristas_destino.obtenerValor(i)->origen == ver_origen)
            {
                ver_destino->aristas_destino.eliminar(i);

                if(ver_destino->puntos.getCantidad() > 0)
                {
                    removeItem(ver_destino->puntos.obtenerValor(ver_destino->puntos.getCantidad()-1));
                    ver_destino->puntos.eliminar(ver_destino->puntos.getCantidad()-1);
                }

                break;
            }
        }

        for(int i = 0; i < aristas.getCantidad(); i++)
        {
            if(aristas.obtenerValor(i)->origen == ver_origen && aristas.obtenerValor(i)->destino == ver_destino)
            {
                arista = aristas.obtenerValor(i);
                aristas.eliminar(i);
                break;
            }
        }

        if(arista != NULL)
            delete arista;
    }

    void eliminarVertice(T valor)
    {
        Vertice<T>* vertice = obtenerVertice(valor);

        for(int i = 0; i < vertices.getCantidad(); i++)
        {
            if(vertices.obtenerValor(i) == vertice)
                continue;

            eliminarArista(vertice->valor, vertices.obtenerValor(i)->valor);
        }

        for(int i = 0; i < vertices.getCantidad(); i++)
        {
            if(vertices.obtenerValor(i) == vertice)
                continue;

            eliminarArista(vertices.obtenerValor(i)->valor, vertice->valor);
        }

        for(int i = 0; i < vertices.getCantidad(); i++)
        {
            if(vertices.obtenerValor(i) == vertice)
            {
                vertices.eliminar(i);
                break;
            }
        }

        removeItem(vertice);
        delete vertice;
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

        for(int i = 0; i < cantidad; i++)
        {
            for(int j = 0; j < cantidad; j++)
            {
                matriz[i][j] = 0;
            }
        }

        for(int i = 0; i < aristas.getCantidad(); i++)
        {
            int origen = vertices.obtenerPosicion(aristas.obtenerValor(i)->origen);
            int destino = vertices.obtenerPosicion(aristas.obtenerValor(i)->destino);
            matriz[origen][destino] = aristas.obtenerValor(i)->peso;
        }

        return matriz;
    }

    template <typename U>
    void borrarMatriz(U** matriz)
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

    template <class U>
    void actualizarMatrizEscena(QGraphicsScene* scene, U** matriz)
    {
        QGraphicsTextItem* peso;
        int pos_x = 0;
        int pos_y = 0;

        for(int i = 0; i < vertices.getCantidad(); i++)
        {
            for(int j = 0; j < vertices.getCantidad(); j++)
            {
                peso = scene->addText(QString::number(matriz[i][j]));
                peso->setFlag(QGraphicsItem::ItemIsMovable);
                peso->setPos(pos_x, pos_y);
                peso->setFont(QFont("Arial", 12, QFont::Bold));
                pos_x+= 25;
            }

            pos_y+= 25;
            pos_x = 0;
        }
    }

    void Floyd(int** matriz, int cantidad)
    {
        for(int k = 0; k < cantidad; k++)
        {
            for(int i = 0; i < cantidad; i++)
            {
                for(int j = 0; j < cantidad; j++)
                {
                    if((matriz[i][k] * matriz[k][j] != 0) && (i != j))
                    {
                        if(matriz[i][k] + matriz[k][j] < matriz[i][j] || matriz[i][j] == 0)
                        {
                            matriz[i][j] = matriz[i][k] + matriz[k][j];
                        }
                    }
                }
            }
        }
    }

    bool** Warshall(int** matriz, int cantidad)
    {
        bool** caminos = new bool*[cantidad];

        for(int i = 0; i < cantidad; i++)
        {
            caminos[i] = new bool[cantidad];
        }

        for(int i = 0; i < cantidad; i++)
        {
            for(int j = 0; j < cantidad; j++)
            {
                if(matriz[i][j] == 0)
                {
                    caminos[i][j] = false;
                }

                else
                    caminos[i][j] = true;
            }
        }

        for(int k = 0; k < cantidad; k++)
        {
            for(int i = 0; i < cantidad; i++)
            {
                for(int j = 0; j < cantidad; j++)
                {
                    if(caminos[i][k] && caminos[k][j] || caminos[i][j])
                        caminos[i][j] = true;
                }
            }
        }

        return caminos;
    }

    void Prim(int** matriz, int cantidad, int pos_origen, QGraphicsScene* scene)
    {
        int visitados[cantidad];
        int minimo;
        int u = 0;
        int v = 0;
        int total = 0;
        int pos_y_scene = 0;
        QGraphicsTextItem* text;
        QString text_prim;

        for(int i = 0; i < cantidad; i++)
        {
            visitados[i] = 0;
            for(int j = 0; j < cantidad; j++)
            {
                if(matriz[i][j] == 0)
                    matriz[i][j] = 999;
            }
        }

        visitados[pos_origen] = 1;

        //start of algorithm
        for(int counter = 0; counter < cantidad-1; counter++)
        {
            minimo = 999;

            for(int i = 0; i < cantidad; i++)
            {
                if(visitados[i] == 1)
                {
                    for(int j = 0; j < cantidad; j++)
                    {
                        if(visitados[j] != 1)
                        {
                            if(minimo > matriz[i][j])
                            {
                                minimo = matriz[i][j];
                                u = i;
                                v = j;
                            }
                        }
                    }
                }
            }

            if(visitados[v] != 1 && minimo != 999)
            {
                visitados[v] = 1;
                total+= minimo;
                text_prim = "Vertice encontrado: " + vertices.obtenerValor(u)->valor + "->" + vertices.obtenerValor(v)->valor + ": Longitud:" + QString::number(minimo);
                text = scene->addText(text_prim);
                text->setPos(0, pos_y_scene);
                pos_y_scene+= 25;
            }
        }

        text_prim = "El peso del Arbol Abarcador de Costo Minimo: " + QString::number(total);
        pos_y_scene+= 10;
        text = scene->addText(text_prim);
        text->setPos(0, pos_y_scene);
    }

//    void Kruskal(int** matriz, int cantidad, int tipo_grafo, QGraphicsScene* scene)
//    {
//        int parent[cantidad];
//        int minimo;
//        int u = 0;
//        int v = 0;
//        int noOfEdges = 1;
//        int total = 0;
//        int pos_y_scene = 0;
//        QString text_kruskal;
//        QGraphicsTextItem* text;

//        for(int i = 0; i < cantidad; i++)
//        {
//            parent[i] = 0;

//            for(int j = 0; j < cantidad; j++)
//            {
//                if(matriz[i][j] == 0)
//                {
//                    matriz[i][j] = 999;
//                }
//            }
//        }

//        //start of algorithm
//        while(noOfEdges < cantidad)
//        {
//            minimo = 999;

//            for(int i = 0; i < cantidad; i++)
//            {
//                for(int j = 0; j < cantidad; j++)
//                {
//                    if(matriz[i][j] < minimo)
//                    {
//                        minimo = matriz[i][j];
//                        u = i;
//                        v = j;
//                    }
//                }
//            }

//            while(parent[u] != 0)
//            {
//                u = parent[u];
//            }

////            while(parent[v] != 0)
////            {
////                v = parent[v];
////            }

//            if(v != u)
//            {
//                noOfEdges++;
//                if(minimo == 999)
//                    continue;
//                text_kruskal = "Arista encontrada: " + vertices.obtenerValor(u)->valor + "->" + vertices.obtenerValor(v)->valor + "Minimo: " + QString::number(minimo);
//                text = scene->addText(text_kruskal);
//                text->setPos(0, pos_y_scene);
//                total+= minimo;
//                parent[v] = u;
//                pos_y_scene+= 25;
//            }

//            if(tipo_grafo == 1)
//            {
//                matriz[u][v] = 999;
//            }

//            else
//            {
//                matriz[u][v] = matriz[v][u] = 999;
//            }
//        }

//        text_kruskal = "El peso del Arbol Abarcador de Costo Minimo: " + QString::number(total);
//        text = scene->addText(text_kruskal);
//        text->setPos(0, pos_y_scene);
//    }

    void Kruskal2(int** matriz, int cantidad, int tipo_grafo, QGraphicsScene* scene)
    {
        int minimo;
        int u = 0;
        int v = 0;
        int noOfEdges = 1;
        int total = 0;
        int pos_y_scene = 0;
        Lista<Lista<Vertice<T>*>*> lista;
        QString text_kruskal;
        QGraphicsTextItem* text;

        for(int i = 0; i < cantidad; i++)
        {
            lista.agregar(new Lista<Vertice<T>*>());
        }

        for(int i = 0; i < cantidad; i++)
        {
            lista.obtenerValor(i)->agregar(vertices.obtenerValor(i));
        }

        for(int i = 0; i < cantidad; i++)
        {
            for(int j = 0; j < cantidad; j++)
            {
                if(matriz[i][j] == 0)
                {
                    matriz[i][j] = 999;
                }
            }
        }
        //start of algorithm
        while(noOfEdges < cantidad)
        {
            minimo = 999;
            bool ciclo = false;

            for(int i = 0; i < cantidad; i++)
            {
                for(int j = 0; j < cantidad; j++)
                {
                    ciclo = false;
                    if(matriz[i][j] < minimo)
                    {
                        for(int x = 0; x < lista.getCantidad(); x++)
                        {
                            if(lista.obtenerValor(x)->existe(vertices.obtenerValor(i)))
                            {
                                if(lista.obtenerValor(x)->existe(vertices.obtenerValor(j)))
                                {
                                    ciclo = true;
                                    break;
                                }

                                else
                                    break;
                            }
                        }

                        if(ciclo != true)
                        {
                            minimo = matriz[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }

            if(v != u)
            {
                noOfEdges++;
                text_kruskal = "Arista encontrada: " + vertices.obtenerValor(u)->valor + "->" + vertices.obtenerValor(v)->valor + "Minimo: " + QString::number(minimo);
                text = scene->addText(text_kruskal);
                text->setPos(0, pos_y_scene);
                total+= minimo;
                pos_y_scene+= 25;

                Lista<Vertice<T>*> lista_temporal;
                int posicion_lista_borrar;

                for(int i = 0; i < lista.getCantidad(); i++)
                {
                    if(lista.obtenerValor(i)->existe(vertices.obtenerValor(v)))
                    {
                        posicion_lista_borrar = i;

                        for(int j = 0; j < lista.obtenerValor(i)->getCantidad(); j++)
                        {
                            lista_temporal.agregar(lista.obtenerValor(i)->obtenerValor(j));
                        }
                        break;
                    }
                }

                for(int i = 0; i < lista.getCantidad(); i++)
                {
                    if(lista.obtenerValor(i)->existe(vertices.obtenerValor(u)))
                    {
                        for(int j = 0; j < lista_temporal.getCantidad(); j++)
                        {
                            lista.obtenerValor(i)->agregar(lista_temporal.obtenerValor(j));
                        }
                        break;
                    }
                }

                lista.eliminar(posicion_lista_borrar);
            }

            if(tipo_grafo == 1)
            {
                matriz[u][v] = 999;
            }

            else
            {
                matriz[u][v] = matriz[v][u] = 999;
            }
        }

        text_kruskal = "El peso del Arbol Abarcador de Costo Minimo: " + QString::number(total);
        text = scene->addText(text_kruskal);
        text->setPos(0, pos_y_scene);
    }

    virtual ~Grafo() {}
};

#endif // GRAFO_H
