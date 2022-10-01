#include "nemo.h"
#include <QTimer>
#include <QGraphicsScene>

Nemo::Nemo(QPixmap pixmap)  :
    nemoPosition(nemoPosition::Up),
    nemoDirection(0)
{
    setPixmap(pixmap);

    QTimer * nemoPosTimer = new QTimer(this);
    connect(nemoPosTimer,&QTimer::timeout,[=]()
    {
        updatePixmap();
    });

    nemoPosTimer->start(500);          //nemoyi positionneri popoxman aragutyuny


    groundPosition= scenePos().y() + 290;

    yAnimation = new QPropertyAnimation(this,"y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

   // yAnimation->start();

    rotationAnimation = new QPropertyAnimation(this,"rotation",this);
   // rotateTo(90,1200,QEasingCurve::InQuad);
}

qreal Nemo::rotation() const
{
    return m_rotation;
}

qreal Nemo::y() const
{
    return m_y;
}


void Nemo::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal curPosY=y();

    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY-scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);

    connect(yAnimation,&QPropertyAnimation::finished,[=]()
    {
        fallToGroundIfNecessary();
    });
    yAnimation->start();

    rotateTo(-20,200,QEasingCurve::OutCubic);
}

void Nemo::startSwiming()
{
    yAnimation->start();

    rotateTo(90,1200,QEasingCurve::InQuad);
}

void Nemo::freezeInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void Nemo::setRotation(qreal rotation)
{
    m_rotation = rotation;

    QPointF c = boundingRect().center();

    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(rotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

void Nemo::setY(qreal y)
{
    moveBy(0,y-m_y);
    m_y = y;
}

void Nemo::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();

}

void Nemo::fallToGroundIfNecessary()
{
    if(y()<groundPosition){
        rotationAnimation->stop();
       // yAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(1200);
        yAnimation->start();

        rotateTo(90,1100,QEasingCurve::InCubic);

    }
}

void Nemo::updatePixmap()                //es methody stuguma nemoyi dirqeri, u hamap dirqin hamap photon dnum
{
    if(nemoPosition==nemoPosition::Middle){

        if(nemoDirection)
        {
            //Up
            setPixmap(QPixmap("C:\\Users\\User\\Desktop\\Images\\nemodown.png"));
            nemoPosition=nemoPosition::Up;
            nemoDirection = 0;
        }
        else{
            //Down
            setPixmap(QPixmap("C:\\Users\\User\\Desktop\\Images\\nemodown.png"));
            nemoPosition=nemoPosition::Down;
            nemoDirection = 1;
        }
    }
    else {
        setPixmap(QPixmap("C:\\Users\\User\\Desktop\\Images\\nemomid.png"));
        nemoPosition=nemoPosition::Middle;
    }

}
