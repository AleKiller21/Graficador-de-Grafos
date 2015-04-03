#include "visualizador.h"
#include "ui_visualizador.h"

Visualizador::Visualizador(Lista<Vertice<QString>*>* lista, int tipo_grafo, QWidget *parent) : QWidget(parent), ui(new Ui::Visualizador)
{
    ui->setupUi(this);
    this->lista_temporal = lista;
    this->scene = new QGraphicsScene();
    this->scene->setSceneRect(0, 0, 851, 691);
    this->tipo_grafo = tipo_grafo;
    ui->VisualizerView->setScene(scene);
    //setWindowFlags(Qt::CustomizeWindowHint);
}

void Visualizador::Floyd(int** matrizAdyacencia)
{
    for(int origen = 0; origen < lista_temporal->getCantidad(); origen++)
    {
        for(int destino = 0; destino < lista_temporal->getCantidad(); destino++)
        {
            if(matrizAdyacencia[origen][destino] != 999 && matrizAdyacencia[origen][destino] != 0)
            {
                int pos_origen_x = vertices.obtenerValor(origen)->pos_scene_x;
                int pos_origen_y = vertices.obtenerValor(origen)->pos_scene_y;
                int pos_destino_x = vertices.obtenerValor(destino)->pos_scene_x;
                int pos_destino_y = vertices.obtenerValor(destino)->pos_scene_y;

                this->scene->addLine(pos_origen_x, pos_origen_y, pos_destino_x, pos_destino_y);
                QGraphicsTextItem* text;
                text = scene->addText(QString::number(matrizAdyacencia[origen][destino]));
                text->setPos((vertices.obtenerValor(origen)->pos().x() + vertices.obtenerValor(destino)->pos().x())/2,
                             (vertices.obtenerValor(origen)->pos().y() + vertices.obtenerValor(destino)->pos().y())/2);
            }
        }
    }
}

void Visualizador::Warshall(bool** caminos)
{
    for(int origen = 0; origen < lista_temporal->getCantidad(); origen++)
    {
        for(int destino = 0; destino < lista_temporal->getCantidad(); destino++)
        {
            if(caminos[origen][destino] != 999 && caminos[origen][destino] != 0)
            {
                int pos_origen_x = vertices.obtenerValor(origen)->pos_scene_x;
                int pos_origen_y = vertices.obtenerValor(origen)->pos_scene_y;
                int pos_destino_x = vertices.obtenerValor(destino)->pos_scene_x;
                int pos_destino_y = vertices.obtenerValor(destino)->pos_scene_y;

                QGraphicsLineItem* line = this->scene->addLine(pos_origen_x, pos_origen_y, pos_destino_x, pos_destino_y);
                QGraphicsTextItem* text;
                text = scene->addText(QString::number(caminos[origen][destino]));
                text->setPos((vertices.obtenerValor(origen)->pos().x() + vertices.obtenerValor(destino)->pos().x())/2,
                             (vertices.obtenerValor(origen)->pos().y() + vertices.obtenerValor(destino)->pos().y())/2);
            }
        }
    }
}

void Visualizador::Dijkstra(int* distancias, int origen)
{
    for(int destino = 0; destino < lista_temporal->getCantidad(); destino++)
    {
        Vertice<QString>* ver_origen = vertices.obtenerValor(origen);
        if(distancias[destino] != 0)
        {
            int pos_origen_x = ver_origen->pos_scene_x;
            int pos_origen_y = ver_origen->pos_scene_y;
            int pos_destino_x = vertices.obtenerValor(destino)->pos_scene_x;
            int pos_destino_y = vertices.obtenerValor(destino)->pos_scene_y;

            this->scene->addLine(pos_origen_x, pos_origen_y, pos_destino_x, pos_destino_y);
            QGraphicsTextItem* text;
            text = scene->addText(QString::number(distancias[destino]));
            text->setPos((pos_origen_x + pos_destino_x)/2, (pos_origen_y + pos_destino_y)/2);
        }
    }

    delete[] distancias;
}

void Visualizador::Prim(Lista<Arista<QString>*>* lista)
{
    Vertice<QString>* ver_origen;
    Vertice<QString>* ver_destino;

    for(int k = 0; k < lista->getCantidad(); k++)
    {
        for(int i = 0; i < vertices.getCantidad(); i++)
        {
            if(vertices.obtenerValor(i)->valor == lista->obtenerValor(k)->origen->valor)
            {
                ver_origen = vertices.obtenerValor(i);
                break;
            }
        }

        for(int i = 0; i < vertices.getCantidad(); i++)
        {
            if(vertices.obtenerValor(i)->valor == lista->obtenerValor(k)->destino->valor)
            {
                ver_destino = vertices.obtenerValor(i);
                break;
            }
        }

        int pos_origen_x = ver_origen->pos_scene_x;
        int pos_origen_y = ver_origen->pos_scene_y;
        int pos_destino_x = ver_destino->pos_scene_x;
        int pos_destino_y = ver_destino->pos_scene_y;

        this->scene->addLine(pos_origen_x, pos_origen_y, pos_destino_x, pos_destino_y);
        QGraphicsTextItem* text = scene->addText(QString::number(lista->obtenerValor(k)->peso));
        text->setPos((pos_origen_x + pos_destino_x)/2, (pos_origen_y + pos_destino_y)/2);
    }

    Arista<QString>* arista;

    for(int i = 0; i < lista->getCantidad(); i++)
    {
        arista = lista->obtenerValor(i);
        lista->eliminar(i);
        delete arista;
        i--;
    }

    delete lista;
}

void Visualizador::buildScene()
{
    for(int i = 0; i < this->lista_temporal->getCantidad(); i++)
    {
        Vertice<QString>* vertice = new Vertice<QString>(this->lista_temporal->obtenerValor(i)->valor, this->tipo_grafo);
        vertice->pos_scene_x = this->lista_temporal->obtenerValor(i)->pos_scene_x;
        vertice->pos_scene_y = this->lista_temporal->obtenerValor(i)->pos_scene_y;
        vertices.agregar(vertice);
        this->scene->addItem(vertice);
        vertice->setPos(lista_temporal->obtenerValor(i)->pos_scene_x, lista_temporal->obtenerValor(i)->pos_scene_y);
    }
}

void Visualizador::showOnScene(int** matriz)
{
    this->buildScene();

    Floyd(matriz);
}

void Visualizador::showOnScene(bool** caminos)
{
    this->buildScene();

    Warshall(caminos);
}

void Visualizador::showOnScene(int* distancias, int origen)
{
    this->buildScene();

    Dijkstra(distancias, origen);
}

void Visualizador::showOnScene(Lista<Arista<QString>*>* lista)
{
    this->buildScene();

    Prim(lista);
}

Visualizador::~Visualizador()
{
    delete ui;
}

void Visualizador::on_btnClose_clicked()
{
    Vertice<QString>* vertice;
    for(int i = 0; i < vertices.getCantidad(); i++)
    {
        vertice = vertices.obtenerValor(i);
        vertices.eliminar(i);
        delete vertice;
        i--;
    }

    scene->clear();
    scene->update();

    this->hide();
}
