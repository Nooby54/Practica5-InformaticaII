#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Pacman: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal x, y;
    int spriteX = 0, spriteY = 0;
    int spriteAncho = 13, spriteAlto = 13;
    QPixmap hojaSprites, spriteActual;
    int contador = 0;

public:
    Pacman();
    void keyPressEvent(QKeyEvent *event) override;
    void movimiento(int dx, int dy);
    void configurarSprite(int dir);
};

#endif // PACMAN_H
