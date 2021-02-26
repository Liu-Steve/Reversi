#include "choosemodescene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QSound>

ChooseModeScene::ChooseModeScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800, 600);
    this->setWindowIcon(QPixmap(":/res/icon.png"));
    this->setWindowTitle("选择模式");

    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("开始");
    QAction * returnAction = startMenu->addAction("返回");
    QAction * quitAction = startMenu->addAction("退出");

    //返回键
    MyPushButton * returnBtn = new MyPushButton(":/res/return.png", ":/res/returnPress.png");
    returnBtn->setParent(this);
    returnBtn->move(this->width() - returnBtn->width() - 10, this->height() - returnBtn->height() - 10);

    //按钮音效
    QSound * clickSound = new QSound(":/res/click.wav", this);

    //双人对战
    MyPushButton * twoPlayerModBtn = new MyPushButton(":/res/button.png");
    twoPlayerModBtn->setParent(this);
    twoPlayerModBtn->move(this->width()/3 - twoPlayerModBtn->width()/3*2, this->height()/2 - twoPlayerModBtn->height()/4);
    connect(twoPlayerModBtn, &MyPushButton::clicked, [=](){
        twoPlayerModBtn->zoom1();
        twoPlayerModBtn->zoom2();
        clickSound->play();
        QTimer::singleShot(200, this,[=](){
            this->hide();
            play = new PlayScene("twoPlayerMod");
            play->show();
            connect(play, &PlayScene::chooseSceneBack, [=](){
                delete play;
                play = NULL;
                this->show();
            });
        });
    });

    QLabel * twoPlayerModLabel = new QLabel;
    twoPlayerModLabel->setParent(this);
    twoPlayerModLabel->setFixedSize(twoPlayerModBtn->width(), twoPlayerModBtn->height());
    twoPlayerModLabel->setText("<font color=white>双人<br>对战</font>");
    QFont font;
    font.setPointSize(28);
    font.setBold(true);
    font.setFamily("方正字迹-仿颜简体");
    twoPlayerModLabel->setFont(font);
    twoPlayerModLabel->move(this->width()/3 - twoPlayerModBtn->width()/3*2, this->height()/2 - twoPlayerModBtn->height()/4);
    twoPlayerModLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中
    twoPlayerModLabel->setAttribute(Qt::WA_TransparentForMouseEvents);//鼠标穿透

    //人机对战
    MyPushButton * onePlayerModBtn = new MyPushButton(":/res/button.png");
    onePlayerModBtn->setParent(this);
    onePlayerModBtn->move(this->width()/3*2 - onePlayerModBtn->width()/3, this->height()/2 - onePlayerModBtn->height()/4);
    connect(onePlayerModBtn, &MyPushButton::clicked, [=](){
        onePlayerModBtn->zoom1();
        onePlayerModBtn->zoom2();
        clickSound->play();
        QTimer::singleShot(200, this,[=](){
            this->hide();
            play = new PlayScene("onePlayerMod");
            play->show();
            connect(play, &PlayScene::chooseSceneBack, [=](){
                play->close();
                this->show();
            });
        });
    });

    QLabel * onePlayerModLabel = new QLabel;
    onePlayerModLabel->setParent(this);
    onePlayerModLabel->setFixedSize(onePlayerModBtn->width(), onePlayerModBtn->height());
    onePlayerModLabel->setText("<font color=white>人机<br>对战</font>");
    onePlayerModLabel->setFont(font);
    onePlayerModLabel->move(this->width()/3*2 - onePlayerModBtn->width()/3, this->height()/2 - onePlayerModBtn->height()/4);
    onePlayerModLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中
    onePlayerModLabel->setAttribute(Qt::WA_TransparentForMouseEvents);//鼠标穿透

    //选择"退出"
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //选择"返回"
    connect(returnAction, &QAction::triggered, [=](){
        emit this->chooseSceneBack();
    });

    //选择返回键
    connect(returnBtn, &MyPushButton::clicked, [=](){
        clickSound->play();
        QTimer::singleShot(200, this,[=](){
            emit this->chooseSceneBack();
        });
    });
}

void ChooseModeScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/res/title.png");
    pix = pix.scaled(300, 180);
    painter.drawPixmap(this->width()/2 - pix.width()/2, 50, pix);
}
