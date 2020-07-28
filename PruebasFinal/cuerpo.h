#ifndef CUERPO_H
#define CUERPO_H


#include <QBrush>

class cuerpo
{

public:
    //Funciones virtuales puras:
    virtual void dibujarItem() = 0;
    virtual void mover(int evento) = 0;
    virtual void disparar()=0;
    virtual void verificarMovimiento() = 0;
    //virtual ~cuerpo();
};


#endif // CUERPO_H
