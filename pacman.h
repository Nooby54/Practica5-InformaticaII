#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

using namespace std;

class Pacman : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal x, y;
    int spriteX = 0, spriteY = 0;
    int spriteAncho = 13, spriteAlto = 13;
    QPixmap hojaSprites, spriteActual;
    int contador = 0;
    int puntuacion = 0;
    int dx = 0, dy = 0, dir = 0;
    QTimer *timerMovimiento;
    vector<vector<char>> mapa;
    vector<pair<QGraphicsEllipseItem *, int>> vectorPuntos;

signals:
    void puntuacionActualizada(int nuevaPuntuacion);
    void puntosRestantes(size_t puntos);

public:
    Pacman(vector<vector<char>> &mapa, vector<pair<QGraphicsEllipseItem *, int>> vectorPuntos);
    void keyPressEvent(QKeyEvent *event) override;
    void movimiento(int dx, int dy);
    void configurarSprite(int dir);
};

#endif // PACMAN_H
