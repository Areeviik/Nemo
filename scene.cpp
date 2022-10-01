#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false),score(0),
    bestScore(0)
{
    setUpSharkTimer();

    //nemo=new Nemo(QPixmap("C:\\Users\\User\\Desktop\\Images\\nemoup.png"));
}

void Scene::addNemo()
{
    nemo=new Nemo(QPixmap("C:\\Users\\User\\Desktop\\Images\\nemoup.png"));
    addItem(nemo);

}

void Scene::startGame()
{
    //Nemo
    nemo->startSwiming();
    //Sharks
    if(!sharkTimer->isActive()){
        cleanSharks();
        setGameOn(true);
        setScore(0);
        hideGameOverGraphics();
        sharkTimer->start(2000);
    }

}

void Scene::setUpSharkTimer()
{
    sharkTimer = new QTimer(this);
    connect(sharkTimer, &QTimer::timeout,[=](){

        Shark * shark = new Shark();        //amen mek vrky mek nory kstexci
        connect(shark,&Shark::collideFail,[=](){      //ete nemon kpav sharkin
            sharkTimer->stop();                       //el nor shark chstexcvi
            freezeNemoAndSharksInPlace();

            setGameOn(false);
            showGameOverGraphics();
        });

        addItem(shark);                       //u kdni ekranin
    });

    // sharkTimer->start(2000);           //amen vayrkyany mek nor shnadzuk avelana
}

void Scene::freezeNemoAndSharksInPlace()
{
    //Sarecvi nemon
    nemo->freezeInPlace();                      //nemon saruma
    //sarecven sharkery

    QList<QGraphicsItem*>sceneItems=items();
    foreach(QGraphicsItem * item, sceneItems){
        Shark * shark=dynamic_cast<Shark *>(item);
        if(shark){
            shark->freezeInPlace();
        }
    }
}

void Scene::setScore(int value)
{
    score = value;
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()            //score+1
{
    score++;
    if(score > bestScore)
        bestScore=score;
    qDebug()<<"Score : "<<score<<"Best Score : "<<bestScore;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){
        if(gameOn){
            nemo->shootUp();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        if(gameOn){
            nemo->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);

}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap("C:\\Users\\User\\Desktop\\Images\\gameover.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0)-QPointF(gameOverPix->boundingRect().width()/2,
                                             gameOverPix->boundingRect().height()/2));
    scoreTextItem= new QGraphicsTextItem();
    QString htmlString = "<p> Score :" + QString::number(score) + "</p>"
            +"<p> Best Score : " + QString::number(bestScore) + "</p>";
    QFont mFont("Consolas",70, QFont::Bold);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::yellow);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0)-QPointF(scoreTextItem->boundingRect().width()/2,
                                               -gameOverPix->boundingRect().height()/2));
}

void Scene::hideGameOverGraphics()
{
    if(gameOverPix){
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix=nullptr;
    }
    if(scoreTextItem){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem=nullptr;
    }
}

void Scene::cleanSharks()                       //naxqan nor game sksely call enq anum es functiony
{
    QList<QGraphicsItem *>sceneItems=items();                //sax itemneri listy
    foreach(QGraphicsItem *item, sceneItems){
        Shark * shark = dynamic_cast<Shark *>(item);
        if(shark){
            removeItem(shark);
            delete shark;
        }
    }
}


