#include "graficador.h"
#include "ui_graficador.h"

Graficador::Graficador(QWidget *parent) : QWidget(parent), ui(new Ui::Graficador)
{
    ui->setupUi(this);
    grafo = new Grafo<QString>();
    ui->GrafoView->setScene(grafo);
    grafo->setSceneRect(0, 0, 851, 691);
}

Graficador::~Graficador()
{
    delete ui;
}

void Graficador::on_btnAgregarVertice_clicked()
{
    if(ui->lineEditVerticeValor->text() != "")
    {
        grafo->agregarVertice(ui->lineEditVerticeValor->text());
    }

    ui->lineEditVerticeValor->setText("");
}

void Graficador::on_btnAgregarArista_clicked()
{
    if(ui->lineEditOrigen->text() != "" && ui->lineEditDestino->text() != "" && ui->lineEditPeso->text() != "")
    {
        QString origen = ui->lineEditOrigen->text();
        QString destino = ui->lineEditDestino->text();
        int peso = ui->lineEditPeso->text().toInt();

        grafo->agregarArista(origen, destino, peso, false);
    }

    ui->lineEditOrigen->setText("");
    ui->lineEditDestino->setText("");
    ui->lineEditPeso->setText("");
}

void Graficador::on_btnEliminarVertice_clicked()
{
    if(ui->lineEditEliminarVertice->text() != "")
    {
        QString vertice_valor = ui->lineEditEliminarVertice->text();
        grafo->eliminarVertice(vertice_valor);
    }

    ui->lineEditEliminarVertice->setText("");
}

void Graficador::on_btnEliminarArista_clicked()
{
    if(ui->lineEditEliminarAristaOrigen->text() != "" && ui->lineEditEliminarAristaDestino->text() != "")
    {
        QString origen = ui->lineEditEliminarAristaOrigen->text();
        QString destino = ui->lineEditEliminarAristaDestino->text();

        grafo->eliminarArista(origen, destino);
    }
}
