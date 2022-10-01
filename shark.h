#ifndef SHARK_H
#define SHARK_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>                      //sharki animaciayi hamar dzaxic aj

class Shark : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX )                  //sharki animaciayi hamar
public:
    explicit Shark();
    ~Shark();
    qreal x() const;

    void freezeInPlace();                //sharky sarecvi erb playery partvuma


signals:
    void collideFail();                      //playery fail kani ete nemon kpav sharkin
public slots:

    void setX(qreal x);


private:
    bool collidesWithNemo();

    QGraphicsPixmapItem * topShark;                   //verevi hamar
    QGraphicsPixmapItem * bottomShark;                //nerqevi hamar
    QPropertyAnimation * xAnimation;
    int yPos;
    qreal m_x;

    bool pastNemo;           //scorei hamar
};

#endif // SHARK_H
