#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include<QGraphicsScene>
#include<QKeyEvent>
#include<QDebug>
#include<QGraphicsTextItem>
#include"moneda.h"
#include"plataforma.h"
#include"parabolico.h"
#include"meteorito.h"
#include"animacion.h"
#include"aliado.h"
#include"enemigo.h"
#include<cstdlib>
#include<ctime>
#include<QFont>
extern int puntajeNivel;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void keyPressEvent(QKeyEvent *event);
    void NuevaMoneda();
    void Elementos();
    void Trackers();
    void AumentarPuntaje();
    void DisminuirVidas();
    void ActualizarCountdown();
    QString TimeAsSting();
    bool Colisiones(int i);
    void AddEnemigos();
    void DisparosEnemigos();
    void LimpiarEscena();
    void IniciarNivel();
    void ElementosNivel2();


    //Nivel 3:
    void ElementosN3();
    void EnemigosN3();

    void Niveles();

private slots:
    void Actualizar();
    void ActualizarN3();

    //void on_pushButton_clicked();

private:
    int tipo=2; //1 un jugador, 2 multijugador.
    int duracion=1200, contTime=0;
    int cantidadMonedas;
    QGraphicsTextItem *Score=new QGraphicsTextItem;
    QGraphicsTextItem *Lives1=new QGraphicsTextItem;
    QGraphicsTextItem *Lives2=new QGraphicsTextItem;
    QGraphicsTextItem *Time=new QGraphicsTextItem;
    QGraphicsScene *Scene;
    Animacion *A;
    QList<Enemigo*>Enemigos;
    QList<Moneda*>Monedas;
    QList<Plataforma*>Plataformas;
    QList<Enemigo*>EnemEstaticos;
    QTimer *timer;
    Moneda *moneda;
    QKeyEvent *event;
    QSet<int> pressedKeys;
    float dt = 15;                                      //Rapidez con la que se ejecutan los saltos
    bool multijugador = true;
    bool estado_juego = true;
    bool J_vivo[2]={true,false};
    int Nivel=3;
    Ui::MainWindow *ui;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MAINWINDOW_H
