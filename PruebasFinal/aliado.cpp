#include "aliado.h"

#include <QDebug>
#include <math.h>
#include "plataforma.h"


extern QVector<Aliado *> jugadores;

Aliado::Aliado(int tipo, int life)        // tipo: 1 o 2 astronautas del nivel 1, 3 o 4 a naves, 5 o 6 astronautas del nivel 3.
{
    jugador = tipo;
    vidas = life;
    dibujarItem();
    setPos(posicion_x, posicion_y);
}

void Aliado::dibujarItem()
{
    if(jugador == 1)
    {
        setBrush(Qt::red);
    }
    if(jugador == 2)
    {
        setBrush(Qt::darkRed);
        posicion_x = posicioninicial_x = 30;
    }
    if(jugador == 3)
    {
        setBrush(Qt::cyan);
        posicion_x = posicioninicial_x = 305;
    }
    if(jugador == 4)
    {
        setBrush(Qt::darkCyan);
        posicion_x = posicioninicial_x = 350;
    }
    if(jugador == 5)
    {
        setBrush(Qt::yellow);
        posicion_x = posicioninicial_x = 50;
    }
    if(jugador == 6)
    {
        setBrush(Qt::darkYellow);
        posicion_x = posicioninicial_x = 605;
    }
    setRect(0,0,ancho,alto);
}

void Aliado::mover(int evento)
{
    if(evento == Qt::Key_A)     //SE MUEVE A LA IZQUIERDA
        posicion_x += -10;
    if(evento == Qt::Key_S)     //SE MUEVE A LA DERECHA
        posicion_x += 10;
    if(evento == Qt::Key_W && jugador<=2)     //SALTA (Sólo para el nivel 1)
        saltando = true;
    if(evento == Qt::Key_D && jugador>2)      //DISPARA (Para los niveles 2 y 3)
        disparar();
    if(evento == Qt::Key_R && jugador>4)      //MUEVE EL ARMA HACIA DERECHA (Sólo para el nivel 3)
        moverArma(angulo_disparo-45.0*(Pi/180.0), evento);
    if(evento == Qt::Key_F && jugador>4)      //MUEVE EL ARMA HACIA IZQUIERDA (Sólo para el nivel 3)
        moverArma(angulo_disparo+45.0*(Pi/180.0), evento);
    verificarMovimiento();
}

void Aliado::disparar()
{
    if(jugador>4)
    {
        for(int j=0;j<7;j++){
            posicion_arma[j][0] = posicion_x;
            posicion_arma[j][1] = posicion_y;
            if(j==0 || j==6)
                posicion_arma[j][1] += ancho;
            if(j==1 || j==5)
                posicion_arma[j][1] += (ancho/2);
            if(j==3)
                posicion_arma[j][0] += (ancho/2);
            if(j>3 && j<7)
                posicion_arma[j][0] += ancho;
        }

        bala = new Bala(5,posicion_arma[indica_posicion_arma][0],posicion_arma[indica_posicion_arma][1],120, angulo_disparo);
        bala->setA(15);
    }
    else
        bala = new Bala(5,posicion_x+(ancho/2),posicion_y,200, angulo_disparo);  //SÓLO ESTÁ DISPARANDO EN 90 GRADOS
    balas_lanzadas.push_back(bala);
    bala->setFlag(QGraphicsItem::ItemIsFocusable);
    scene()->items().push_back(bala);
    scene()->addItem(bala);
}

void Aliado::saltar()
{
    //posicion_y = posicioninicial_y - short( velocidad * abs(sin(theta)) * tiempo + ( Gravedad * (tiempo*tiempo) / 2.0));

    Vy=velocidad*sin(theta)-Gravedad*tiempo;
    velocidad=sqrt(Vy*Vy);
    theta=atan2(Vy,0);
    posicion_y-=Vy*tiempo-0.5*Gravedad*tiempo*tiempo;

    qDebug() << "SALTO  cuerpo"<< jugador << ": X:" << jugadores.at(0)->x() << "  Y:" << jugadores.at(0)->y() << " theta:" << theta;
    verificarMovimiento();
    //theta -= 0.09;
}

void Aliado::moverArma(float posibleangulo, int direccion)
{
    if(direccion == Qt::Key_R){
        if(posibleangulo>(-46.0*(Pi/180.0))){
            angulo_disparo = posibleangulo;
            indica_posicion_arma+=1;
        }
    }else{
        if(posibleangulo<(226.0*(Pi/180.0))){
            angulo_disparo = posibleangulo;
            indica_posicion_arma-=1;
        }
    }
}

/*void Aliado::actualizarDisparos()
{
    for(int n=0; n<this->balas_lanzadas.size(); n++)
    {
        balas_lanzadas.at(n)->Colisiones();
        if((balas_lanzadas.at(n)->getPosY()>0 && balas_lanzadas.at(n)->getPosY()<400 )&&
                (balas_lanzadas.at(n)->getPosX()>-20 && balas_lanzadas.at(n)->getPosY()<680)){
                    balas_lanzadas.at(n)->ActualizarVelocidad();
                    balas_lanzadas.at(n)->ActualizarPosicion();
        }else{
           balas_lanzadas.at(n)->Desaparecer();
           balas_lanzadas.removeAt(n);
        }
    }
}*/

void Aliado::verificarMovimiento() //HAY QUE VERIFICAR SI CHOCA CON ALGÚN ELEMENTO
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; i++){
        if(typeid(*(colliding_items[i]))==typeid (Plataforma)){
            qDebug() << "chocó";

            posY_barra = colliding_items.at(i)->pos().y();
            if((posY_barra*2)<(this->y()+alto))
                colision = true;

            colliding_items.removeAt(i);
        }
        else
            colision = false;
    }

    if(posicion_x+ancho>680)
        posicion_x -=10;
    if(posicion_x<0)
        posicion_x+=10;
    if(posicion_y>361)
    {
        saltando = false;
        posicion_y = posicioninicial_y;
        velocidad = V;
        theta = Pi/180.0;
    }
    if(colision == true )
    {
        saltando = false;
        qDebug() << "pos_y " << this->y()+alto << "posY_barra " <<posY_barra*2;
        return;
    }


    posicionx_bala = posicion_x+(ancho/2);
    posiciony_bala = posicion_y;
    setPos(posicion_x,posicion_y);

}

bool Aliado::VerificarVida()
{
    ColisionMeteorito();
    if(vidas>0)
        return true;
    else{
        return false;
}
}

void Aliado::ColisionMeteorito()
{
    QList<QGraphicsItem*>Colisiones=collidingItems();
    if(Colisiones.size()>0){
        for(int i=0; i<Colisiones.size();i++){
            if(typeid(*Colisiones.at(i))==typeid(Meteorito)){
                vidas--;
                delete Colisiones.at(i);
            }
        }
    }

}

QList<Bala *> Aliado::getBalas_lanzadas() const
{
    return balas_lanzadas;
}

int Aliado::getPuntaje() const
{
    return puntaje;
}

unsigned short Aliado::getVidas() const
{
    return vidas;
}

void Aliado::setVidas(unsigned short value)
{
    vidas = value;
}
