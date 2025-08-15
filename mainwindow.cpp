#include "mainwindow.h"
#include "pacman.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QFile>
#include <QTextStream>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/data/icon.ico"));

    const int filas = 31;
    const int columnas = 28;
    const int tamCelda = 24;

    QGraphicsScene *escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0, 0, columnas * tamCelda, filas * tamCelda);

    QFile archivo(":/data/mapa.csv");
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    vector<vector<char>> mapa(filas, vector<char>(columnas));
    vector<pair<QGraphicsEllipseItem *, int>> vectorPuntos;
    QTextStream in(&archivo);
    int fila = 0;
    while (!in.atEnd() && fila < filas)
    {
        QString linea = in.readLine();
        QStringList valores = linea.split(",");
        for (int col = 0; col < valores.size() && col < columnas; ++col)
        {
            int valor = valores[col].toInt();
            mapa[fila][col] = valor;
            int x = col * tamCelda;
            int y = fila * tamCelda;
            if (valor == 3)
            {
                QGraphicsRectItem *pared = new QGraphicsRectItem(x, y, tamCelda - 0.5, tamCelda - 0.5);
                pared->setPen(QPen(Qt::blue, 2));
                escena->addItem(pared);
            }
            else if (valor == 1)
            {
                QGraphicsEllipseItem *punto = new QGraphicsEllipseItem(0, 0, tamCelda / 4, tamCelda / 4);
                escena->addItem(punto);
                punto->setPos(x + (tamCelda - tamCelda / 4) / 2, y + (tamCelda - tamCelda / 4) / 2);
                punto->setBrush(Qt::white);
                vectorPuntos.push_back(make_pair(punto, 1));
            }
            else if (valor == 2)
            {
                QGraphicsEllipseItem *especial = new QGraphicsEllipseItem(0, 0, (tamCelda * 2) / 3, (tamCelda * 2) / 3);
                especial->setBrush(Qt::white);
                escena->addItem(especial);
                especial->setPos(x + tamCelda / 6, y + tamCelda / 6);
                vectorPuntos.push_back(make_pair(especial, 2));
            }
        }
        fila++;
    }
    Pacman *pacman = new Pacman(mapa, vectorPuntos);
    escena->addItem(pacman);
    pacman->setPos(310, 410);
    pacman->setFocus();
    ui->puntos->setText(QString::number(vectorPuntos.size()));

    connect(pacman, &Pacman::puntuacionActualizada, this, [=](int puntos)
            { ui->puntuacion->setText(QString::number(puntos)); });

    connect(pacman, &Pacman::puntosRestantes, this, [=](size_t puntosRestantes)
            { ui->puntos->setText(QString::number(puntosRestantes)); });
    ui->graphicsView->setFixedSize(674, 746);

    this->setFixedSize(700, 820);
}

MainWindow::~MainWindow()
{
    delete ui;
}
