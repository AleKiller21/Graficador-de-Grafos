#include "graficador.h"
#include "ui_graficador.h"

Graficador::Graficador(QWidget *parent) : QWidget(parent), ui(new Ui::Graficador)
{
    ui->setupUi(this);
    grafo = new Grafo<QString>(this->tipo_grafo);
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
        ui->cmbOrigenes->addItem(ui->lineEditVerticeValor->text());
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

        for(int i = 0; i < grafo->aristas.getCantidad(); i++)
        {
            if(grafo->aristas.obtenerValor(i)->origen->valor == origen && grafo->aristas.obtenerValor(i)->destino->valor == destino)
                return;
        }

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
        int pos = grafo->vertices.obtenerPosicion(grafo->obtenerVertice(vertice_valor));
        if(pos == -1)
            return;
        grafo->eliminarVertice(vertice_valor);
        ui->cmbOrigenes->removeItem(pos);
    }

    ui->lineEditEliminarVertice->setText("");
}

void Graficador::on_btnEliminarArista_clicked()
{
    if(ui->lineEditEliminarAristaOrigen->text() != "" && ui->lineEditEliminarAristaDestino->text() != "")
    {
        QString origen = ui->lineEditEliminarAristaOrigen->text();
        QString destino = ui->lineEditEliminarAristaDestino->text();
        int pos = grafo->vertices.obtenerPosicion(grafo->obtenerVertice(origen));
        int pos2 = grafo->vertices.obtenerPosicion(grafo->obtenerVertice(destino));

        if(pos == -1 || pos2 == -1)
            return;

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
        {
            grafo->Floyd(matrizAdyacencia, grafo->vertices.getCantidad());
            break;
        }

        case 2:
        {
            caminos = grafo->Warshall(matrizAdyacencia, grafo->vertices.getCantidad());
            warshall = true;
            break;
        }

        case 3:
        {
            grafo->Dijkstra(matrizAdyacencia, grafo->vertices.getCantidad(), ui->cmbOrigenes->currentIndex(), matrizView);
            return;
        }

        case 4:
        {
            grafo->Prim(matrizAdyacencia, grafo->vertices.getCantidad(), ui->cmbOrigenes->currentIndex(), matrizView);
            return;
        }

        case 5:
        {
            if(grafo->aristas.getCantidad() == 0)
                return;

            grafo->Kruskal2(matrizAdyacencia, grafo->vertices.getCantidad(), this->tipo_grafo, matrizView);
            return;
        }
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

void Graficador::on_cmbAlgoritmos_currentIndexChanged(int index)
{
    if((index == 4 || index == 3) && grafo->vertices.getCantidad() > 0)
    {
        ui->cmbOrigenes->setEnabled(true);
    }

    else
    {
        ui->cmbOrigenes->setEnabled(false);
    }
}
