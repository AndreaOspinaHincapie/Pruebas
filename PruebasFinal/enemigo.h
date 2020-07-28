#ifndef ENEMIGO_H
#define ENEMIGO_H


#include <QGraphicsRectItem>
#include "cuerpo.h"
#include "meteorito.h"
#include"bala.h"

class Enemigo: public QGraphicsRectItem, public cuerpo
{
public:
    Enemigo(unsigned int tipo, unsigned short int tipo_b, unsigned short int life, int posX, int posY, int posX_arma, int posY_arma, int pos_inicialX, int pos_inicialY, float vel, float a, float theta_disparo, int radio_bala, float vel_bala);

    void dibujarItem() override;
    void disparar() override;
    void mover(int evento) override;
    void verificarMovimiento() override;
    bool ActualizarPosicion();
    void ColisionBala();
    bool IsColliding();
    QList<Meteorito *> getDisparos() const;

    int getPosicion_x() const;

    int getPosicion_y() const;

private:
    unsigned short int enemigo;
    unsigned short int disparo;
    unsigned short int vidas;
    int ancho = 60, alto = 60;

    int posicion_x;
    int posicion_y;
    int posicioninicial_x;
    int posicioninicial_y;
    float velocidad;
    float aceleracion;

    float angulo_b;
    int radio_b;
    float velocidad_b;
    int posicionX_arma;
    int posicionY_arma;

    Meteorito *bala;
    QList<Meteorito*> disparos = {};

    //float velocidad = 200;
    //float tiempo = 0.4;
};

#endif // ENEMIGO_H
