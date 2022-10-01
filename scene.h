#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "shark.h"
#include "nemo.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addNemo();

    void startGame();

    bool getGameOn() const;
    void setGameOn(bool value);

    void incrementScore();

    void setScore(int value);

signals:

public slots:

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    void showGameOverGraphics();
    void hideGameOverGraphics();

    void cleanSharks();                 //nra hamar vor partveluc heto nor xax skseluc hin sharkery chmna u norery stexcvi dra vra
    void setUpSharkTimer();
    void freezeNemoAndSharksInPlace();

    QTimer * sharkTimer;
    Nemo * nemo;
    bool gameOn;

    int score;
    int bestScore;

    QGraphicsPixmapItem *gameOverPix;
    QGraphicsTextItem *scoreTextItem;

};

#endif // SCENE_H
