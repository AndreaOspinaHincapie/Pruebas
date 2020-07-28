#include "parabolico.h"
#include <QDebug>

void Parabolico::setA(double value)
{
    a = value;
}

void Parabolico::rebotar()
{
  Vy=-Vy;
  V0=V0/2;
  angulo=atan2(Vy,Vx);
}

void Parabolico::ActualizarPosicion()
{
    posX+=Vx*delta;
    posY-=Vy*delta-0.5*a*delta*delta;
    setPos(posX,posY);
}

void Parabolico::ActualizarVelocidad(QGraphicsItem *item)
{
    Vx=V0*cos(angulo);
    Vy=V0*sin(angulo)-a*delta;
    V0=sqrt(Vy*Vy+Vx*Vx);
    angulo=atan2(Vy,Vx);
    if(this->collidesWithItem(item)){
        rebotar();
        ActualizarPosicion();
        contRebote++;
    }
}
void Parabolico::Desaparecer(QGraphicsScene *Scene){
    if(contRebote==4)
        Scene->removeItem(this);
}

Parabolico::Parabolico(double _radio, double X, double Y, double _angulo, double _V0)
{
    radio=_radio;
    posX=X;
    posY=Y;
    angulo=_angulo;
    V0=_V0;
    setPos(posX,posY);

}

QRectF Parabolico::boundingRect() const
{
    return QRectF(-radio,-radio,2*radio,2*radio);

}

void Parabolico::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(boundingRect());
}
