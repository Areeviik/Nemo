#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include "shark.h"
#include "nemo.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene=new Scene(this);
    scene->setSceneRect(-250,-300,500,600);

    QGraphicsPixmapItem * pixItem= new QGraphicsPixmapItem(QPixmap("C:\\Users\\User\\Desktop\\Images\\bg.jpg"));  //etnankary
    scene->addItem(pixItem);
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,
                                           pixItem->boundingRect().height()/2));    //etnankari positiony dnum enq 0,0 vor ga mejtex


    //scene->addLine(-400,0,400,0,QPen(Qt::blue));
    //scene->addLine(0,-400,0,400,QPen(Qt::blue));           // xach, kentrony aveli hesht tesnelu hamar


  //  Shark * shark= new Shark();
 //   scene->addItem(shark);                                //saturny stexcecinq, drecinq ekranin

 //   Nemo *nemo= new Nemo(QPixmap("C:\\Users\\User\\Desktop\\Images\\nemoup.png"));
   // scene->addItem(nemo);                    // nemon stexcecinq, drecinq ekranin


    ui->graphicsView->setScene(scene);


    scene->addNemo();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startGameButton_clicked()
{
    scene->startGame();                                //erb sxmum enq start Game buttonin, kanchvi es functiony
}
