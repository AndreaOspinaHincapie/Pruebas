#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QBrush>
#include<QDebug>

extern QVector<Aliado *> jugadores;
extern QVector<Plataforma *> elementosNivel1;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(unsigned(time(nullptr)));
    //ElementosN3();
   ElementosNivel2();
   IniciarNivel();
    //Nivel=2;
    //Niveles();


}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::IniciarNivel()
{
//    if(event->key()==Qt::Key_X && A->getActivado()){
//      A->Presentar();
//
    timer=new QTimer;
    if(Nivel==2)
        connect(timer,SIGNAL(timeout()),this,SLOT(Actualizar())); //Si nivel es 2.
    else if(Nivel==3)
        connect(timer,SIGNAL(timeout()),this,SLOT(ActualizarN3()));

    timer->start(50);

}

void MainWindow::NuevaMoneda()
{
    //Nivel 2
    Monedas.push_back(new Moneda(50,15,0,5+(std::rand()%(671)),110+(std::rand()%(271-110)),0,std::rand()%501));
    Scene->addItem(Monedas.back());
    Monedas.back()->Aparecer();
}

void MainWindow::ElementosNivel2()
{
    //Nivel 2
    Nivel=2;
    Scene=new QGraphicsScene;
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Scene->setSceneRect(QRect(0,0,680,400));
    this->installEventFilter(this);
    //Definiendo fondo nivel2
    QPixmap fondo("../PruebasFinal/animacion/fondo nivel 2.png");
    fondo=fondo.scaled(680,400);
    Scene->setBackgroundBrush(fondo);
    if(tipo==1) cantidadMonedas=30;
    else if(tipo==2)cantidadMonedas=60;


    jugadores.push_back(new Aliado(3, 5));
    Scene->addItem(jugadores.back());
    jugadores.at(0)->setFlag(QGraphicsItem::ItemIsFocusable);
    jugadores.push_back(new Aliado(4, 5));        //Multijugador (BOTÓN)
    Scene->addItem(jugadores.back());            //Multijugador (BOTÓN)
    jugadores.at(1)->setFlag(QGraphicsItem::ItemIsFocusable);
    if(jugadores.size()>1){
            multijugador = true;
            J_vivo[1]=true;
            }//VARIABLE GLOBAL
    AddEnemigos();
    Trackers();
}

void MainWindow::ElementosN3()
{
    contTime=0;
    puntajeNivel=0;
    Scene=new QGraphicsScene;
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Scene->setSceneRect(QRect(0,0,680,400));
    this->installEventFilter(this);
    //Definiendo fondo nivel3
    QPixmap fondo("../PruebasFinal/animacion/1781.jpg");
    fondo=fondo.scaled(680,400);
    Scene->setBackgroundBrush(fondo);
    Plataformas.push_back(new Plataforma(60,10,0,75,0,0,0,0));
    Scene->addItem(Plataformas.back());
    Plataformas.push_back(new Plataforma(60,10,308,75,0,0,0,0));
    Scene->addItem(Plataformas.back());
    jugadores.push_back(new Aliado(5,5));
    J_vivo[0]=true;
    Scene->addItem(jugadores.back());
    jugadores.at(0)->setFlag(QGraphicsItem::ItemIsFocusable);
    if(multijugador){
        jugadores.push_back(new Aliado(6,5));
        Scene->addItem(jugadores.back());
        jugadores.at(1)->setFlag(QGraphicsItem::ItemIsFocusable);
        J_vivo[1]=true;
    }
    EnemEstaticos.push_back(new Enemigo(2,1,3,0,110,60,110,0,0,20,0,7*M_PI/4,10,100));
    Scene->addItem(EnemEstaticos.back());
    EnemEstaticos.push_back(new Enemigo(2,1,3,615,110,600,110,0,0,0,0,5*M_PI/4,10,100));
    Scene->addItem(EnemEstaticos.back());
    Trackers();
}

void MainWindow::EnemigosN3()
{
    //angulos[1+rand()%2]
    double angulos[2]={M_PI_4,3*M_PI_4};
    int posX=120+rand()%(451);
    Enemigos.push_back(new Enemigo(2,1,1,posX,0,posX+30,60,posX,0,0,5,3*M_PI_2,10,20));
    Scene->addItem(Enemigos.back());

}

void MainWindow::Niveles()
{
    if(Nivel==2){
        ElementosNivel2();
    }
    else if(Nivel==3){
        ElementosN3();
    }
    IniciarNivel();

}

void MainWindow::Trackers()
{

    Score->setPlainText(QString("Score: ")+QString::number(puntajeNivel));
    Score->setDefaultTextColor(Qt::white);
    Score->setFont(QFont("times",16));

    Lives1->setPlainText(QString("Lives P1: ")+QString::number(jugadores.at(0)->getVidas()));
    Lives1->setDefaultTextColor(Qt::white);
    Lives1->setFont(QFont("times",16));
    Lives1->setPos(Lives1->x(),Lives1->y()+20);
    if(multijugador){
        Lives2->setPlainText(QString("Lives P2: ")+QString::number(jugadores.at(1)->getVidas()));
        Lives2->setDefaultTextColor(Qt::white);
        Lives2->setFont(QFont("times",16));
        Lives2->setPos(Lives2->x(),Lives2->y()+40);
        Scene->addItem(Lives2);
    }

    Time->setPlainText(QString("Time: ")+TimeAsSting());
    Time->setDefaultTextColor(Qt::white);
    Time->setFont(QFont("times",16));
    Time->setPos(Time->x()+580,Time->y());

    Scene->addItem(Score);
    Scene->addItem(Lives1);
    Scene->addItem(Time);


}

void MainWindow::AumentarPuntaje()
{
  Score->setPlainText(QString("Score: ")+QString::number(puntajeNivel));
}

void MainWindow::DisminuirVidas()
{

    Lives1->setPlainText(QString("Lives P1: ")+QString::number(jugadores.at(0)->getVidas()));
    if(multijugador)
         Lives2->setPlainText(QString("Lives P2: ")+QString::number(jugadores.at(1)->getVidas()));

}

void MainWindow::ActualizarCountdown()
{
    Time->setPlainText(QString("Time: ")+TimeAsSting());
}

QString MainWindow::TimeAsSting()
{
    int minutos=0, segundos=0;
    minutos=((duracion-contTime)/20)/60;
    segundos=((duracion-contTime)/20)%60;
    if(segundos>9)
        return QString(QString::number(minutos)+":"+QString(QString::number(segundos)));
    else
         return QString(QString::number(minutos)+":0"+QString(QString::number(segundos)));

}

void MainWindow::AddEnemigos()
{
    //Nivel 2
    Enemigos.push_back( new Enemigo(1,2,3,100,10,130,60,0,0,0,0,0,10,0));
    Scene->addItem(Enemigos.back());

    Enemigos.push_back( new Enemigo(1,2,3,200,10,230,60,0,0,0,0,0,10,0));
    Scene->addItem(Enemigos.back());

    Enemigos.push_back( new Enemigo(1,2,3,300,10,330,60,0,0,0,0,0,10,0));
    Scene->addItem(Enemigos.back());

    Enemigos.push_back( new Enemigo(1,2,3,400,10,430,60,0,0,0,0,0,10,0));
    Scene->addItem(Enemigos.back());

    Enemigos.push_back( new Enemigo(1,2,3,500,10,530,60,0,0,0,0,0,10,0));
    Scene->addItem(Enemigos.back());


}

void MainWindow::DisparosEnemigos()
{
    //Nivel 2
    if(contTime%10==0 && Enemigos.size()>0){
        int EnemDisparando=rand()%(Enemigos.size()+1);
        for(int i=0;i<=EnemDisparando;i++){
            Enemigos.at(rand()%(Enemigos.size()))->disparar();
        }

    }
}

void MainWindow::LimpiarEscena()
{
    Enemigos.clear();
    Monedas.clear();
    EnemEstaticos.clear();
    for(int i=0; i<jugadores.size();i++){

    }
}


void MainWindow::Actualizar()
{
    //Nivel 2
    contTime++;
    ActualizarCountdown();
    DisparosEnemigos();
    if(contTime<duracion && (J_vivo[0]|| J_vivo[1])){
        if(contTime%(duracion/cantidadMonedas)==0){
            NuevaMoneda();
        }
        //Actualización de tiempos de monedas
        if(Monedas.size()!=0){
            for(int i=0; i<Monedas.size();i++){
                if(Monedas.at(i)->getTiempo()>0) Monedas.at(i)->setTiempo(Monedas.at(i)->getTiempo()-1);
                else{
                    Scene->removeItem(Monedas.at(i));
                    Moneda *moneda=Monedas.at(i);
                    Monedas.removeAt(i);
                    delete moneda;


                }
            }
        }
        // jugadores.at(0)->actualizarDisparos();
           for(int i=0; i<jugadores.size();i++){
               if(jugadores.at(i)->VerificarVida()){
                   //jugadores.at(i)->actualizarDisparos();
                   if(jugadores.at(i)->saltando)
                       jugadores.at(i)->saltar();
               }
               else{
                   Scene->removeItem(jugadores.at(i));
                   jugadores.at(i)->setVidas(0);
                   J_vivo[i]=false;
                   //jugadores.remove(i);
               }
           }


            /* if(jugadores.at(0)->saltando == true)
                 jugadores.at(0)->saltar();
             if(multijugador == true){
                 //jugadores.at(1)->actualizarDisparos();
                 if(jugadores.at(1)->saltando == true)
                     jugadores.at(1)->saltar();
             }*/
             if(Enemigos.size()>=0){
                 for(int i=0; i<Enemigos.size();i++){
                     if(Enemigos.at(i)->IsColliding()){
                         Enemigo *enem=Enemigos.at(i);
                         Enemigos.removeAt(i);
                         delete enem;
                     }
                 }
             }
        //--------------------------------------------------------------------------------
     }
    else{
        timer->stop();
        estado_juego=!estado_juego;
        //LimpiarEscena();
       
    }


        DisminuirVidas();
        AumentarPuntaje();
}

void MainWindow::ActualizarN3()
{
    contTime++;
    ActualizarCountdown();
    if(contTime<duracion && (J_vivo[0]|| J_vivo[1])){
        if(contTime%20==0)
            EnemigosN3();
        for(int i=0; i<Enemigos.size();i++){
            if(Enemigos.at(i)->ActualizarPosicion() || Enemigos.at(i)->IsColliding()){
                Enemigo *enemigo=Enemigos.at(i);
                Scene->removeItem(enemigo);
                Enemigos.removeAt(i);
                delete enemigo;
            }
            else if(contTime%40==0) Enemigos.at(i)->disparar();

        }
        for(int i=0;i<EnemEstaticos.size();i++){
            if(EnemEstaticos.at(i)->IsColliding()){
                Enemigo *enemigo=EnemEstaticos.at(i);
                Scene->removeItem(enemigo);
                EnemEstaticos.removeAt(i);
                delete enemigo;
            }
            else if(contTime%30==0) EnemEstaticos.at(i)->disparar();
        }
        for(int i=0; i<jugadores.size();i++){
            if(jugadores.at(i)->VerificarVida()){
                //jugadores.at(i)->actualizarDisparos();
                if(jugadores.at(i)->saltando)
                    jugadores.at(i)->saltar();
            }
            else{
                Scene->removeItem(jugadores.at(i));
                jugadores.at(i)->setVidas(0);
                J_vivo[i]=false;
                //jugadores.remove(i);
            }
        }
    }
        else{
            timer->stop();
            estado_juego=!estado_juego;
            LimpiarEscena();
        }
    DisminuirVidas();
    AumentarPuntaje();
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
if (!estado_juego)
        return false;
    if(event->type()==QEvent::KeyPress)
    {
        pressedKeys += ((QKeyEvent*)event)->key();
        if(pressedKeys.contains(Qt::Key_A) && J_vivo[0] )
            jugadores.at(0)->mover(Qt::Key_A);
        if(pressedKeys.contains(Qt::Key_H) && multijugador==true && J_vivo[1] )
            jugadores.at(1)->mover(Qt::Key_A);
        ///////////////////////////////////////////////////////// DERECHA
        if(pressedKeys.contains(Qt::Key_S) && J_vivo[0])
            jugadores.at(0)->mover(Qt::Key_S);
        if(pressedKeys.contains(Qt::Key_J) && multijugador==true && J_vivo[1] )
            jugadores.at(1)->mover(Qt::Key_S);
        ///////////////////////////////////////////////////////// SALTAR
        if(pressedKeys.contains(Qt::Key_W) && J_vivo[0] )
            jugadores.at(0)->mover(Qt::Key_W);
        if(pressedKeys.contains(Qt::Key_U) && multijugador==true && J_vivo[1] )
            jugadores.at(1)->mover(Qt::Key_W);
        ///////////////////////////////////////////////////////// DISPARAR
        if(pressedKeys.contains(Qt::Key_D) && J_vivo[0] )
            jugadores.at(0)->mover(Qt::Key_D);
        if(pressedKeys.contains(Qt::Key_K) && multijugador==true && J_vivo[1] )
            jugadores.at(1)->mover(Qt::Key_D);
        ///////////////////////////////////////////////////////// MOVER-ARMA DERECHA
        if(pressedKeys.contains(Qt::Key_R) && J_vivo[0] )
            jugadores.at(0)->mover(Qt::Key_R);
        if(pressedKeys.contains(Qt::Key_O) && multijugador==true && J_vivo[1] )
            jugadores.at(1)->mover(Qt::Key_R);
        ///////////////////////////////////////////////////////// MOVER-ARMA IZQUIERDA
        if(pressedKeys.contains(Qt::Key_F) && J_vivo[0] )
            jugadores.at(0)->mover(Qt::Key_F);
        if(pressedKeys.contains(Qt::Key_L) && multijugador==true && J_vivo[1] )
            jugadores.at(1)->mover(Qt::Key_F);
    }
    else if(event->type()==QEvent::KeyRelease)
    {
        pressedKeys -= ((QKeyEvent*)event)->key();
    }
    return false;
}

/*void MainWindow::on_pushButton_clicked()
{
    WN3.setGeometry(this->geometry());
    this->close();                  //Cierra Inicio de sesion/ registro
    WN3.setVisible(true);
}
*/
