#include "shark.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>
#include "scene.h"
#include "nemo.h"

Shark::Shark() :
    topShark(new QGraphicsPixmapItem(QPixmap("C:\\Users\\User\\Desktop\\Images\\shark.png"))),
    bottomShark(new QGraphicsPixmapItem(QPixmap("C:\\Users\\User\\Desktop\\Images\\shark2.png"))),
    pastNemo(false)
{
    topShark->setPos(QPointF(0,0)-QPointF(topShark->boundingRect().width()/2,
                      topShark->boundingRect().height()+200));

    bottomShark->setPos(QPointF(0,0)+QPointF(bottomShark->boundingRect().width()/2,
                                             100));

    addToGroup(topShark);
    addToGroup(bottomShark);

    yPos=QRandomGenerator::global()->bounded(150);           // y positiony random enq vercnum
    int xRandomizer=QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0)+QPoint(260+xRandomizer, yPos));

    xAnimation=new QPropertyAnimation(this,"x",this);        //animacia
    xAnimation->setStartValue(300+xRandomizer);              //skselu arjeqy 300
    xAnimation->setEndValue(-760);                          //verjacnelu arjeqy  -760
    xAnimation->setEasingCurve(QEasingCurve::Linear);              //animaciayi dzevy
    xAnimation->setDuration(2500);

    connect(xAnimation,&QPropertyAnimation::finished,[=](){
        qDebug()<<"Animation finished";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();


    addToGroup(topShark);
    addToGroup(bottomShark);
}

Shark::~Shark()
{
    qDebug()<<"Deleting Shark";
    delete topShark;
    delete bottomShark;
}

qreal Shark::x() const
{
    return m_x;

}

void Shark::freezeInPlace()
{
    xAnimation->stop();
}

void Shark::setX(qreal x)
{
   // qDebug()<<"Shark position: "<<x;
    m_x=x;

    if(x<0 && !pastNemo){
        pastNemo=true;
        QGraphicsScene *mScene=scene();
        Scene * myScene = dynamic_cast<Scene * >(mScene);
        if(myScene){
            myScene->incrementScore();
        }
    }


    if(collidesWithNemo()){
        emit collideFail();
    }
    setPos(QPointF(0,0)+QPointF(x,yPos));           //aranc sra animacian cher lini
}

bool Shark::collidesWithNemo()
{
    QList<QGraphicsItem*>collidingItems=topShark->collidingItems();
    collidingItems.append(bottomShark->collidingItems());

    foreach (QGraphicsItem * item, collidingItems){
        Nemo *nemo=dynamic_cast<Nemo*>(item);
        if(nemo){
            return true;
        }
    }
    return false;
}
