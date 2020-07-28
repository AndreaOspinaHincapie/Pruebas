#include "animacion.h"

void Animacion::setScene(QGraphicsScene *value)
{
    Scene = value;
}

bool Animacion::getActivado() const
{
    return activado;
}

void Animacion::setActivado(bool value)
{
    activado = value;
}

int Animacion::getNivel() const
{
    return nivel;
}

void Animacion::setNivel(int value)
{
    nivel = value;
}

Animacion::Animacion(QObject *parent): QObject{parent}
{

}

void Animacion::AnimacionNivel1()
{
    //Método que controla animación de nivel 1
    if(progreso<Nivel1.size()){
        qDebug()<<"Cambio"<<endl;
        slide.load(Direccion+Nivel1.at(progreso));
        QPixmap scaled=slide.scaled(escalaW,escalaH);
        item= Scene->addPixmap(scaled);
        item->scale();
        item->setPos(posX,posY);
        progreso++;
        qDebug()<<"Mostrando slide"<<endl;
    }
    else{
        qDebug()<<"fin animacion"<<endl;
        Scene->clear();
        qDebug()<<"Limpiando escena"<<endl;
        activado=false;
    }
}

void Animacion::AnimacionNivel2()
{
    //método que muestra animación del nivel 2
    if(progreso<Nivel2.size()){
        qDebug()<<"Cambio"<<endl;
        slide.load(Direccion+Nivel2.at(progreso));
        QPixmap scaled=slide.scaled(escalaW,escalaH);
        item= Scene->addPixmap(scaled);
        item->scale();
        item->setPos(posX,posY);
        progreso++;
        qDebug()<<"Mostrando slide"<<endl;
    }
    else{
        qDebug()<<"fin animacion"<<endl;
        Scene->clear();
        qDebug()<<"Limpiando escena"<<endl;
        activado=false;
    }
}

void Animacion::AnimacionNivel3()
{
    //Método que muestra animación del nivel 3

    if(progreso<Nivel3.size()){
        //Condición para animación de cuerpos que se mueven por gravitación:
        if(Nivel3.at(progreso)=="cuerpos"){
            Scene->setBackgroundBrush(Qt::black);
            Scene->clear();
            Scene->addItem(cuerpo1);
            Scene->addItem(cuerpo2);
            timer=new QTimer;
            connect(timer,SIGNAL(timeout()),this,SLOT(mover()));
            timer->start(inicioTimer);
            progreso++;
        }
        else{
            if(progreso==5){
                Scene->clear();
                timer->stop();
            }
            Scene->setBackgroundBrush(Qt::white);
            qDebug()<<"Cambio"<<endl;
            slide.load(Direccion+Nivel3.at(progreso));
            QPixmap scaled=slide.scaled(escalaW,escalaH);
            item= Scene->addPixmap(scaled);
            item->scale();
            item->setPos(posX,posY);
            progreso++;
            qDebug()<<"Mostrando slide"<<endl;
        }
    }
    else{
        qDebug()<<"fin animacion"<<endl;
        Scene->clear();
        Cuerpos.clear();
        qDebug()<<"Limpiando escena"<<endl;
        activado=false;
    }

}

void Animacion::AnimacionFinal()
{
    //Método que muestra animación del final.
    if(progreso<Final.size()){
        qDebug()<<"Cambio"<<endl;
        slide.load(Direccion+Final.at(progreso));
        QPixmap scaled=slide.scaled(escalaW,escalaH);
        item= Scene->addPixmap(scaled);
        item->setPos(posX,posY);
        progreso++;
        qDebug()<<"Mostrando slide"<<endl;
    }
    else{
        qDebug()<<"fin animacion"<<endl;
        Scene->clear();
        qDebug()<<"Limpiando escena"<<endl;
        activado=false;
    }
}

void Animacion::Presentar()
{
    if(nivel==1){
        AnimacionNivel1();
    }
    else if(nivel==2){
        AnimacionNivel2();
    }
    else if(nivel==3){
        AnimacionNivel3();
    }
    else if(nivel==4){
        AnimacionFinal();
    }
}

void Animacion::EstablecerAceleracion()
{
    //método que calcula la aceleración de los cuerpos de la animación del nivel 3
    Cuerpos.value(0)->ActualizarAceleracion(Cuerpos.value(1)->getMasa(),Cuerpos.value(1)->getPosx(),Cuerpos.value(1)->getPosy());
    Cuerpos.value(1)->ActualizarAceleracion(Cuerpos.value(0)->getMasa(),Cuerpos.value(0)->getPosx(),Cuerpos.value(0)->getPosy());
}

void Animacion::mover()
{
    //Método que actualiza la posición de los cuerpos del nivel 3
    cont++; //Registro del tiempo que ha pasado para detener simulación si
            //usuario no presiona la tecla en un tiempo determinado
    if(cont<intervalo && Cuerpos.empty()==false){
        EstablecerAceleracion();
        for(int i=0; i<Cuerpos.size();i++){
            Cuerpos.at(i)->ActualizarPosicion();
            Cuerpos.at(i)->setPos(Cuerpos.at(i)->getPosx(), Cuerpos.at(i)->getPosy());
            Cuerpos.at(i)->setAY(0);
            Cuerpos.at(i)->setAX(0);
        }

    }
    else{
        timer->disconnect(timer,SIGNAL(timeout()),this,SLOT(mover()));
        //delete timer;
    }
}
