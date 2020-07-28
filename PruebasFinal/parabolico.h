#ifndef PARABOLICO_H
#define PARABOLICO_H

#include<QGraphicsItem>
#include<QPainter>
#include<QGraphicsScene>
#include<math.h>
#include"plataforma.h"
class Parabolico: public QGraphicsItem
{
private:
    long int contRebote=0;
    double posY=0,posX=0, V0=0, Vx=0,Vy=0,angulo=0, radio=0,a=9.8,delta=0.1;



public:
    Parabolico(double _radio,double X,double Y, double _angulo, double _V0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void setA(double value);
    void rebotar();
    void ActualizarPosicion();
    void ActualizarVelocidad(QGraphicsItem *item);
    void Desaparecer(QGraphicsScene *Scene);
};

#endif // PARABOLICO_H
