#ifndef VISUALIZADOR_H
#define VISUALIZADOR_H

#include <QWidget>
#include <QGraphicsScene>
#include "Vertice.h"

namespace Ui {
    class Visualizador;
}


class Visualizador : public QWidget
{
    Q_OBJECT

public:

    explicit Visualizador(Lista<Vertice<QString>*>* lista, int tipo_grafo, QWidget *parent = 0);

    void showOnScene(int** matriz);
    void showOnScene(bool** caminos);
    void showOnScene(int* distancias, int origen);
    void showOnScene(Lista<Arista<QString>*>* lista);

    ~Visualizador();

private slots:
    void on_btnClose_clicked();

private:
    Ui::Visualizador *ui;
    Lista<Vertice<QString>*>* lista_temporal;
    Lista<Vertice<QString>*> vertices;
    QGraphicsScene* scene;
    int tipo_grafo;

    void buildScene();
    void Floyd(int** matrizAdyacencia);
    void Warshall(bool** caminos);
    void Dijkstra(int* distancias, int origen);
    void Prim(Lista<Arista<QString>*>* lista);
};

#endif // VISUALIZADOR_H
