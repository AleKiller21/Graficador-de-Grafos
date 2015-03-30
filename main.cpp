#include "graficador.h"
#include "grafoseleccion.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GrafoSeleccion seleccion;
    seleccion.show();
//    Graficador w;
//    w.show();

    return a.exec();
}
