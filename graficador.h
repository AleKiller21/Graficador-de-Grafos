#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <QWidget>
#include "Grafo.h"

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

private:
    Ui::Graficador *ui;
    Grafo<QString>* grafo;
    QGraphicsScene* matrizView;
    int** matrizAdyacencia;
    bool** caminos;
    bool warshall;
};

#endif // GRAFICADOR_H
