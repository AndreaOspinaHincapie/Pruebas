#include "mainwindow.h"
#include <QApplication>

QVector<Aliado *> jugadores;
int puntajeNivel=0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
