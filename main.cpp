#include "graficador.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Graficador w;
    w.show();

    return a.exec();
}
