#include "bala.h"

double Bala::getPosX() const
{
    return posX;
}

double Bala::getPosY() const
{
    return posY;
}

void Bala::setDelta(int value)
{
    delta = value;
}


Bala::Bala(double _radio, double X, double Y, double _V0, double _angulo,QObject *parent): QObject{parent}
{

    radio=_radio;
    posX=X;
    posY=Y;
    angulo=_angulo; //Por default se tiene 3PI/2
    V0=_V0;
    setPos(posX,posY);
    connect(timer,SIGNAL(timeout()),this,SLOT(Mover()));
    timer->start(50);
}

QRectF Bala::boundingRect() const
{
     return QRectF(-radio,-radio,2*radio,2*radio);
}

void Bala::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

        painter->setBrush(Qt::cyan);
        painter->drawEllipse(boundingRect());
}

void Bala::rebotar()
{
    //Posible metodo para rebote
    Vy=-Vy;
}

void Bala::ActualizarPosicion()
{
    //Segun ecuaciones de MRUA
    posX+=Vx*delta;
    posY-=Vy*delta-0.5*a*delta*delta; //Resta por sistema de coordenadas de la escena
    //(Si al implementarlo se genera una parabola que abre hacia arriba entonces cambiar
    //por +=)
    setPos(posX,posY);
}

void Bala::ActualizarVelocidad()
{
    //Segun ecuaciones de lanzamiento de proyectiles.
    Vx=V0*cos(angulo);
    Vy=V0*sin(angulo)-a*delta;
    V0=sqrt(Vy*Vy+Vx*Vx);
    angulo=atan2(Vy,Vx);
}
void Bala::Colisiones(){
    QList<QGraphicsItem*>Colision=collidingItems();
    for(int i=0; i<Colision.size();i++){
        if(typeid(*(Colision.at(i)))==typeid(Moneda)){
                scene()->removeItem(Colision.at(i));
                Colision.removeAt(i);
                puntajeNivel+=50;
                qDebug()<<puntajeNivel<<endl;
                delete this;
    }
        else if(typeid(*(Colision.at(i)))==typeid(Plataforma)){
            Colision.removeAt(i);
            delete this;
        }
    }
}
void Bala::Mover()
{
    Colisiones();
    if((posY>0 && posY<400 )&&
            (posX>-20 && posX<680)){
                ActualizarVelocidad();
                ActualizarPosicion();
    }else{
        Desaparecer();
        delete this;
    }
}

void Bala::Desaparecer()
{
    //Remover cuerpo de escena ingresada.
    scene()->removeItem(this);
}


void Bala::setA(double value)
{
    a = value;
}
