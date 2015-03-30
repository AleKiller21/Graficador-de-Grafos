#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <QWidget>
//#include <QtGui>
//#include <QtCore>
//#include <QGraphicsScene>
#include "Grafo.h"

namespace Ui
{
    class Graficador;
}

class Graficador : public QWidget
{
    Q_OBJECT

public:
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
};

#endif // GRAFICADOR_H
