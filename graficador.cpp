#include "graficador.h"
#include "ui_graficador.h"

Graficador::Graficador(QWidget *parent) : QWidget(parent), ui(new Ui::Graficador)
{
    ui->setupUi(this);
    grafo = new Grafo<QString>(tipo_grafo);
    ui->GrafoView->setScene(grafo);
    grafo->setSceneRect(0, 0, 851, 691);
    this->matrizView = new QGraphicsScene();
    this->matrizView->setSceneRect(0, 0, 421, 361);
    this->matrizAdyacencia = NULL;
    this->caminos = NULL;
    this->warshall = false;
    ui->MatrizView->setScene(matrizView);
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

        if(tipo_grafo == 1)
        {
            grafo->agregarArista(origen, destino, peso, false);
        }

        else
        {
            grafo->agregarArista(origen, destino, peso, true);
        }
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

        if(tipo_grafo == 1)
        {
            grafo->eliminarArista(origen, destino);
        }

        else
        {
            grafo->eliminarArista(origen, destino);
            grafo->eliminarArista(destino, origen);
        }
    }

    ui->lineEditEliminarAristaOrigen->setText("");
    ui->lineEditEliminarAristaDestino->setText("");
}

void Graficador::on_btnMatrizAdyacencia_clicked()
{
    if(grafo->vertices.getCantidad() == 0)
        return;

    if(matrizAdyacencia != NULL)
    {
        grafo->borrarMatriz<int>(this->matrizAdyacencia);
        this->matrizAdyacencia = NULL;
        matrizView->clear();
        matrizView->update();
    }

    if(caminos != NULL)
    {
        grafo->borrarMatriz<bool>(caminos);
        caminos = NULL;
    }

    this->matrizAdyacencia = grafo->crearMatrizAdyacencia();

    switch(ui->cmbAlgoritmos->currentIndex())
    {
        case 0:
            break;

        case 1:
            grafo->Floyd(matrizAdyacencia, grafo->vertices.getCantidad());
            break;

        case 2:
           caminos = grafo->Warshall(matrizAdyacencia, grafo->vertices.getCantidad());
           warshall = true;
           break;
    }

    if(warshall != true)
    {
        grafo->actualizarMatrizEscena<int>(matrizView, matrizAdyacencia);
    }

    else
    {
        grafo->actualizarMatrizEscena<bool>(matrizView, caminos);
        warshall = false;
    }
}
