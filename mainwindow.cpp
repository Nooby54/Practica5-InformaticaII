#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>

#include "pacman.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *escena = new QGraphicsScene(this);
    escena->setSceneRect(0,0,600,600);
    ui->graphicsView->setScene(escena);
    ui->graphicsView->setFixedSize(600 + (ui->graphicsView->frameWidth() * 2), 600 + (ui->graphicsView->frameWidth() * 2));

    Pacman *pacman = new Pacman;
    pacman->setOffset(-pacman->pixmap().width()/2, -pacman->pixmap().height()/2);
    escena->addItem(pacman);
    pacman->setPos(300, 300);
}

MainWindow::~MainWindow()
{
    delete ui;
}
