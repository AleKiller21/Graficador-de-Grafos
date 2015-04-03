#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <QWidget>
#include "Grafo.h"
#include "visualizador.h"

namespace Ui
{
    class Graficador;
}

class Graficador : public QWidget
{
    Q_OBJECT

public:
    int tipo_grafo;

    explicit Graficador(QWidget *parent = 0);
    ~Graficador();

private slots:
    void on_btnAgregarVertice_clicked();

    void on_btnAgregarArista_clicked();

    void on_btnEliminarVertice_clicked();

    void on_btnEliminarArista_clicked();

    void on_btnMatrizAdyacencia_clicked();

    void on_cmbAlgoritmos_currentIndexChanged(int index);

    void on_btnVisualizador_clicked();

private:
    Ui::Graficador *ui;
    Grafo<QString>* grafo;
    QGraphicsScene* matrizView;
    Visualizador* visualizer;
    int** matrizAdyacencia;
    bool** caminos;
    bool warshall;
    int* dijkstra_distancias;//distancias para voder mostrar el grafo en el Visualizador
    Lista<Arista<QString>*>* lista_prim;//Lista de aristas que ocupo en la ventana de Visualizador para mostrar la representacion de Prim
    Lista<Arista<QString>*>* lista_kruskal;//Lista de aristas que ocupo en la ventana de Visualizador para mostrar la representacion de Kruskal
};

#endif // GRAFICADOR_H
