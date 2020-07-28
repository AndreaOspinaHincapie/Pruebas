#include "moneda.h"

int Moneda::getTiempo() const
{
    return tiempo;
}

void Moneda::setTiempo(int value)
{
    tiempo = value;
}


bool Moneda::getInScene() const
{
    return InScene;
}

void Moneda::setInScene(bool value)
{
    InScene = value;
}

Moneda::Moneda(int _valor, double radio_moneda, double radio_giro, double x_inicial, double y_inicial, double _velAngular, int _tiempo)
{
    valor=_valor;
    radioMoneda=radio_moneda;
    radioGiro=radio_giro;
    posX=x_inicial;
    posY=y_inicial;
    Xinicial=x_inicial;
    Yinicial=y_inicial;
    velAngular=_velAngular;
    tiempo=_tiempo;
}

void Moneda::Aparecer()
{
    setPos(posX,posY);
}

void Moneda::Mover()
{
    angulo+=velAngular;
    posX=Xinicial+radioGiro*cos(angulo);
    posY=Yinicial+radioGiro*sin(angulo);
    setPos(posX,posY);

}

QRectF Moneda::boundingRect() const
{
  return QRectF(-radioMoneda,-radioMoneda,2*radioMoneda,2*radioMoneda);

}

void Moneda::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap moneda;
    moneda.load("../PruebasFinal/moneda.png");
    painter->drawPixmap(boundingRect(),moneda,moneda.rect());
}
