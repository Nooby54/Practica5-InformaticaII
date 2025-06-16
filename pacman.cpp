#include "pacman.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

Pacman::Pacman(vector<vector<char>> &mapa, vector<pair<QGraphicsEllipseItem *, int>> vectorPuntos) : mapa(mapa), vectorPuntos(vectorPuntos)
{
    x = 310;
    y = 410;

    setFlag(QGraphicsItem::ItemIsFocusable);
    hojaSprites.load(":/sprites/PacMan (52x52).png");
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(20, 20, Qt::KeepAspectRatio);
    setPixmap(spriteActual);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, [=]()
            {
        if(dy!= 0 || dx != 0){
        movimiento(dx, dy);
            configurarSprite(dir);
        } });
    timerMovimiento->start(35);
}

void Pacman::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        dx = 0;
        dy = -2;
        dir = 3;
        break;
    case Qt::Key_A:
        dx = -2;
        dy = 0;
        dir = 2;
        break;
    case Qt::Key_S:
        dx = 0;
        dy = 2;
        dir = 1;
        break;
    case Qt::Key_D:
        dx = 2;
        dy = 0;
        dir = 0;
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}

void Pacman::movimiento(int dx, int dy)
{
    int nuevoX = x + dx;
    int nuevoY = y + dy;

    const int tamCelda = 24;
    const int anchoSprite = 12;
    const int altoSprite = 12;

    int colInicio = (nuevoX - 2) / tamCelda;
    int colFin = (nuevoX + anchoSprite + 8) / tamCelda;
    int filaInicio = nuevoY / tamCelda;
    int filaFin = (nuevoY + altoSprite + 8) / tamCelda;
    for (int fila = filaInicio; fila <= filaFin; ++fila)
    {
        for (int col = colInicio; col <= colFin; ++col)
        {
            if (mapa[fila][col] == 3)
            {
                return;
            }
            else if (mapa[fila][col] == 1 || mapa[fila][col] == 2)
            {
                for (auto it = vectorPuntos.begin(); it != vectorPuntos.end(); ++it)
                {
                    QGraphicsEllipseItem *punto = it->first;
                    QPointF puntoPos = punto->scenePos();
                    if (static_cast<int>(puntoPos.y()) / tamCelda == fila && static_cast<int>(puntoPos.x()) / tamCelda == col)
                    {
                        scene()->removeItem(punto);
                        delete punto;
                        puntuacion += (it->second == 1) ? 10 : 40;
                        emit puntuacionActualizada(puntuacion);
                        vectorPuntos.erase(it);

                        size_t restantes = vectorPuntos.size();
                        emit puntosRestantes(restantes);
                        mapa[fila][col] = 0;
                        break;
                    }
                }
            }
        }
    }

    x = nuevoX;
    y = nuevoY;
    if (x > 670)
        x = 0;
    else if (x < 0)
        x = 670;

    setPos(x, y);
}

void Pacman::configurarSprite(int dir)
{
    spriteY = dir * spriteAlto;
    spriteX = spriteAncho * contador;
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(20, 20, Qt::KeepAspectRatio);
    setPixmap(spriteActual);
    contador++;
    if (contador == 4)
        contador = 0;
}
