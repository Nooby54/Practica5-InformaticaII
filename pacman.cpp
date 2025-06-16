#include "pacman.h"
#include <QKeyEvent>

Pacman::Pacman() {
    x = 300;
    y = 300;

    setFlag(QGraphicsItem::ItemIsFocusable);
    hojaSprites.load(":/sprites/PacMan (52x52).png");
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(40, 40, Qt::KeepAspectRatio);
    setPixmap(spriteActual);

}

void Pacman::keyPressEvent(QKeyEvent *event) {
    switch(event->key()){
    case Qt::Key_W:
        movimiento(0,-5);
        configurarSprite(3);
        break;
    case Qt::Key_A:
        movimiento(-5,0);
        configurarSprite(2);
        break;
    case Qt::Key_S:
        movimiento(0,5);
        configurarSprite(1);
        break;
    case Qt::Key_D:
        movimiento(5,0);
        configurarSprite(0);
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}

void Pacman::movimiento(int dx, int dy){
    if(x>590) x=0;
    else if(x<0) x = 590;
    else x+=dx;
    y+=dy;
    setPos(x,y);
}

void Pacman::configurarSprite(int dir){
    spriteY = dir*spriteAlto;
    spriteX = spriteAncho*contador;
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(40, 40, Qt::KeepAspectRatio);
    setPixmap(spriteActual);
    contador++;
    if(contador==4) contador = 0;
}
