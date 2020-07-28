#ifndef NIVEL2_H
#define NIVEL2_H
#include"meteorito.h"
#include<QGraphicsScene>
#include<QObject>
#include<QTimer>
#include<QVector>
class Nivel2: public QObject
{
    Q_OBJECT
private:
    int tipo=1, puntaje=0, contTiempo=0; //tipo: 1: un jugador, 2: multijugador
    int cantidadMeteoritos;
    QGraphicsScene *Scene;
    QTimer *timer=new QTimer;
    Meteorito *meteorito, *disparo;
    QVector<Meteorito*>Meteoritos;
    QVector<Meteorito*>Disparos;
    QVector<int>tiempos;
public:
    explicit Nivel2(int tipo_, QObject *parent=nullptr);
    void setScene(QGraphicsScene *value);
    void SetBackground();
    void StopGameL2();
    void PlayGameL2();
    //void AñadirMeteoritos();
    void Colision();
    void ObtenerTiempos();
};
#endif // NIVEL2_H
