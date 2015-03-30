#include "grafoseleccion.h"
#include "ui_grafoseleccion.h"

GrafoSeleccion::GrafoSeleccion(QWidget *parent) : QWidget(parent), ui(new Ui::GrafoSeleccion)
{
    ui->setupUi(this);
    this->opcion = 0;
    graficador = new Graficador();
}

GrafoSeleccion::~GrafoSeleccion()
{
    delete ui;
}

void GrafoSeleccion::on_btnIniciar_clicked()
{
    if(ui->radioDirigido->isChecked())
    {
        this->opcion = 1;
        graficador->tipo_grafo = opcion;
        this->hide();
        this->graficador->show();
    }

    else if(ui->radioNoDirigido->isChecked())
    {
        this->opcion = 2;
        graficador->tipo_grafo = opcion;
        this->hide();
        this->graficador->show();
    }
}
