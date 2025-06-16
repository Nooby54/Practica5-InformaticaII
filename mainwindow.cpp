#include "mainwindow.h"
#include "pacman.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const int filas = 31;
    const int columnas = 28;
    const int tamCelda = 24;

    QGraphicsScene *escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);
    ui->graphicsView->setFixedSize(columnas * tamCelda + 2, filas * tamCelda + 2);
    escena->setSceneRect(0, 0, columnas * tamCelda, filas * tamCelda);


    QFile archivo(":/data/mapa.csv");
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    vector<vector<char>> mapa(filas, vector<char>(columnas));
    vector<pair<QGraphicsEllipseItem*,int>> vectorPuntos;
    QTextStream in(&archivo);
    int fila = 0;
    while (!in.atEnd() && fila < filas) {
        QString linea = in.readLine();
        QStringList valores = linea.split(",");
        for (int col = 0; col < valores.size() && col < columnas; ++col) {
            int valor = valores[col].toInt();
            mapa[fila][col] = valor;
            int x = col * tamCelda;
            int y = fila * tamCelda;

            if (valor == 3) {
                QGraphicsRectItem *pared = new QGraphicsRectItem(x, y, tamCelda-0.5, tamCelda-0.5);
                pared->setPen(QPen (Qt::blue,2));
                escena->addItem(pared);
            } else if (valor == 1) {
                QGraphicsEllipseItem *punto = new QGraphicsEllipseItem(0, 0, tamCelda/2, tamCelda/2);
                escena->addItem(punto);
                punto->setPos(x + tamCelda/4, y + tamCelda/4);
                punto->setBrush(Qt::white);
                vectorPuntos.push_back(make_pair(punto,1));
            } else if (valor == 2) {
                QGraphicsEllipseItem *especial = new QGraphicsEllipseItem(x + tamCelda/6, y + tamCelda/6, (tamCelda * 2) / 3, (tamCelda * 2) / 3);
                especial->setBrush(Qt::white);
                escena->addItem(especial);
                vectorPuntos.push_back(make_pair(especial,1));
            }
        }
        fila++;
    }

    Pacman *pacman = new Pacman(mapa,ui->graphicsView,vectorPuntos);
    escena->addItem(pacman);
    pacman->setPos(310, 410);
}

MainWindow::~MainWindow()
{
    delete ui;
}
