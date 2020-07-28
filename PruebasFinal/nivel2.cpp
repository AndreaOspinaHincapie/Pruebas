#include "nivel2.h"

Nivel2::Nivel2(int tipo_, QObject *parent): QObject{parent}
{
   connect(timer,SIGNAL(timeout()),this,SLOT(PlayGameL2()));
   SetBackground();
   tipo=tipo_;
   if(tipo==1) cantidadMeteoritos=12;
   else if(tipo==2) cantidadMeteoritos=24;
   timer->start(10);
}

void Nivel2::setScene(QGraphicsScene *value)
{
    Scene = value;
}

void Nivel2::SetBackground()
{
    QPixmap fondo("../PruebasFinal/animacion/fondo nivel 2.png");
    fondo=fondo.scaled(670,390);
    Scene->setBackgroundBrush(fondo);
}

void Nivel2::StopGameL2()
{
    timer->stop();
}

void Nivel2::PlayGameL2()
{


}

//void Nivel2::AñadirMeteoritos()
//{

//}

void Nivel2::Colision()
{
    for(int i=0; i<Meteoritos.size();i++){
        for(int j=0;j<Disparos.size();j++){
            if(Disparos.at(j)->collidesWithItem(Meteoritos.at(i))){
               Disparos.at(j)->Desaparecer();
               Meteoritos.at(i)->Desaparecer();
               puntaje+=50;
            }
        }
    }
}

void Nivel2::ObtenerTiempos()
{

}
