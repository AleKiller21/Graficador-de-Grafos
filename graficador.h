#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <QWidget>
#include "Grafo.h"
//#include "grafoseleccion.h"

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

private:
    Ui::Graficador *ui;
    Grafo<QString>* grafo;
    //GrafoSeleccion* grafoSeleccion;
};

#endif // GRAFICADOR_H
