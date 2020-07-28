#ifndef MONEDA_H
#define MONEDA_H
#include<QtDebug>
#include<math.h>
#include<QGraphicsItem>
#include<QPainter>
class Moneda: public QGraphicsItem
{
private:
    int valor=0, tiempo=0;
    double posX=0,posY=0,radioGiro=0,radioMoneda=0;
    double velAngular=0, angulo=0,Xinicial=0,Yinicial=0;
    bool InScene=true;


public:
    Moneda(int _valor, double radio_moneda, double radio_giro,double x_inicial, double y_inicial, double _velAngular,int _tiempo=0);
    void Aparecer();
    void Mover();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    int getTiempo() const;
    void setTiempo(int value);
    bool getInScene() const;
    void setInScene(bool value);
};

#endif // MONEDA_H
