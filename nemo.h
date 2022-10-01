#ifndef NEMO_H
#define NEMO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Nemo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Nemo(QPixmap pixmap);

    qreal rotation() const;

    qreal y() const;

    void shootUp();

    void startSwiming();

    void freezeInPlace();             //sarecni nemoyin erb  playery partvel e

signals:

public slots:
    void setRotation(qreal rotation);

    void setY(qreal y);

    void rotateTo(const qreal &end, const int& duration, const QEasingCurve& curve);

    void fallToGroundIfNecessary();
private:
    enum nemoPosition{
        Up,
        Middle,
        Down
    };
    void updatePixmap();


    nemoPosition nemoPosition;
    bool nemoDirection;             //0:down, 1:Up
    qreal m_rotation;
    qreal m_y;
    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;
    qreal groundPosition;
};

#endif // NEMO_H
