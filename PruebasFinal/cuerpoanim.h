#ifndef CUERPOANIM_H
#define CUERPOANIM_H
#include<math.h>
#include<QGraphicsItem>
#include<QPainter>
#include<QColor>
#include<ctime>
#include<stdlib.h>

class CuerpoAnim: public QGraphicsItem
{
public:
    double posx=0, posy=0,velx=0,vely=0,masa=0,radio=0,aX=0,aY=0;
    int delta=1, G=1;
    double r=0, angulo=0; //angulo en radianes
    int tipo=0;

public:
    double getMasa() const;
    CuerpoAnim();
    CuerpoAnim(int tipo_,double x,double y, double vx, double vy, double m, double R);
    double getPosx() const;
    double getPosy() const;
    void setPosy(double value);
    void ActualizarPosicion();
    void ActualizarVelocidad();
    void ActualizarAceleracion(double m2, double x, double y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void setAX(double value);
    void setAY(double value);
};

#endif // CUERPOANIM_H
