#include "cuerpoanim.h"

double CuerpoAnim::getPosx() const
{
    return posx;
}

double CuerpoAnim::getPosy() const
{
    return posy;
}

void CuerpoAnim::setPosy(double value)
{
    posy = value;
}

void CuerpoAnim::ActualizarPosicion()
{
    //Método para actualizar la posición del cuerpo. Se calcula la velocidad y se aplica la ecuación de movimiento:
    ActualizarVelocidad();
    posx=posx+velx*delta+(aX*delta*delta)/2;
    posy=posy+vely*delta+(aY*delta*delta)/2;
}

void CuerpoAnim::ActualizarVelocidad()
{
    //Método que actualiza la velocidad del cuerpo a partir de la ecuación de movimiento:
    velx=velx+aX*delta;
    vely=vely+aY*delta;
}

void CuerpoAnim::ActualizarAceleracion(double m2, double x, double y)
{
    //Método que recibe los datos de masa, posición en x y posición en y del otro cuerpo y calcula la separación y
    //el ángulo entre estos, así como las nuevas aceleraciones según las ecuaciones de movimiento:
        r=sqrt(((x-posx)*(x-posx))+((y-posy)*(y-posy)));
        angulo=atan2(y-posy,x-posx);
        aX=aX+((G*m2*cos(angulo))/(r*r));
        aY=aY+((G*m2*sin(angulo))/(r*r));

}

QRectF CuerpoAnim::boundingRect() const
{
    return QRectF(-radio,-radio,2*radio,2*radio);
}

void CuerpoAnim::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Estableciendo forma y color de los cuerpos. El color se define al azar según los valores de Red, Green y Blue de los que se
    //Obtiene un color con la clase QColor.
    if(tipo==1){
        painter->setBrush(Qt::green);
        painter->drawEllipse(boundingRect());
    }
    else if(tipo==2){
        painter->setBrush(Qt::red);
        painter->drawEllipse(boundingRect());
    }
}


void CuerpoAnim::setAX(double value)
{
    aX = value;
}
void CuerpoAnim::setAY(double value)
{
    aY = value;
}

double CuerpoAnim::getMasa() const
{
    return masa;
}

CuerpoAnim::CuerpoAnim()
{

}

CuerpoAnim::CuerpoAnim(int _tipo,double x, double y, double vx, double vy, double m, double R)
{
    //Constructor que recibe posición inicial, velocidad inicial, masa y radio de cada cuerpo y obtiene al azar valores de Red,
    //Green, Blue que definirán el color del cuerpo.
    srand(unsigned(time(nullptr)));
    posx=x;
    posy=y;
    velx=vx;
    vely=vy;
    masa=m;
    radio=R;
    tipo=_tipo;
    setPos(posx,posy);
}
