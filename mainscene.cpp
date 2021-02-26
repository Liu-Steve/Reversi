#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QPixmap>
#include "mypushbutton.h"
#include "choosemodescene.h"
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景
    this->setFixedSize(800, 600);
    this->setWindowIcon(QPixmap(":/res/icon.png"));
    this->setWindowTitle("黑白棋");

    //按钮音效
    QSound * clickSound = new QSound(":/res/click.wav", this);

    //退出按钮
    connect(ui->actionExit, &QAction::triggered, [=](){
        this->close();
    });

    MyPushButton * startBtn = new MyPushButton(":/res/start.png");
    startBtn->setParent(this);
    startBtn->move(this->width()/2 - startBtn->width()/2, this->height()/2);

    chooseScene = new ChooseModeScene;

    connect(chooseScene, &ChooseModeScene::chooseSceneBack, [=](){
        chooseScene->hide();
        this->setGeometry(chooseScene->geometry());
        this->show();
    });

    connect(startBtn, &MyPushButton::clicked, [=](){
        startBtn->zoom1();
        startBtn->zoom2();
        clickSound->play();

        //延时进入选择界面
        QTimer::singleShot(200, this,[=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/res/title.png");
    pix = pix.scaled(300, 180);
    painter.drawPixmap(this->width()/2 - pix.width()/2, 50, pix);
}

MainScene::~MainScene()
{
    delete ui;
}

