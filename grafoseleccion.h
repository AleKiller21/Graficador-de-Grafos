#ifndef GRAFOSELECCION_H
#define GRAFOSELECCION_H

#include <QWidget>
#include "graficador.h"

namespace Ui {
    class GrafoSeleccion;
}

class GrafoSeleccion : public QWidget
{
    Q_OBJECT

public:
    int opcion;

    explicit GrafoSeleccion(QWidget *parent = 0);
    ~GrafoSeleccion();

private slots:
    void on_btnIniciar_clicked();

private:
    Ui::GrafoSeleccion *ui;
    Graficador* graficador;
};

#endif // GRAFOSELECCION_H
