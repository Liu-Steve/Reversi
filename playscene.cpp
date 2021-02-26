#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QTimer>
#include "mypushbutton.h"
#include <QPainter>
#include <QLabel>
#include <QFont>
#include <QString>
#include "chess.h"
#include "computer.h"
#include <QPair>
#include <QSound>

void PlayScene::setChess(int x, int y, QString statue)
{
    if(statue != black && statue != white)
        statue = black;
    if(x < 0 || x > 7)
        x = 0;
    if(y < 0 || y > 7)
        y = 0;
    Chess * chess = new Chess(statue);
    chess->setParent(this);
    map[x][y] = chess;
    chess->move(310 + x*100, 60 + y*100);
    chess->show();
    //qDebug() << "下棋" << chess->x() << chess->y();
}

void PlayScene::setSelectBtn(int x, int y)
{
    if(x < 0 || x > 7)
        x = 0;
    if(y < 0 || y > 7)
        y = 0;
    MyPushButton * selectBtn = new MyPushButton(":/res/chessToPlace.png");
    selectBtn->setParent(this);
    selectBtn->move(310 + x*100, 60 + y*100);
    selectBtn->show();
    connect(selectBtn, &MyPushButton::clicked, [=](){
        emit this->selected(x, y);
    });
    //清除selectBtn
    connect(this, &PlayScene::selected, selectBtn, [=](){
        delete selectBtn;
    });
}

void PlayScene::reverse(int x, int y, QString statue)
{
    bool isValid;
    int statueIndex, opposite;
    int cx, cy;
    if(statue == white)
    {
        opposite = 2;
        statueIndex = 1;
    }
    else
    {
        opposite = 1;
        statueIndex = 2;
    }
    if(x > 1)
    {
        isValid = false;
        for(int i = x - 2; i >= 0; i--)
        {
            if(sta[i][y] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[i][y] == 0)
                break;
            else
                continue;
        }
        if(isValid)
        {
            for(int i = x - 1; i >= 0; i--)
            {
                if(sta[i][y] == statueIndex)
                {
                    sta[i][y] = opposite;
                    map[i][y]->changeStatus();
                }
                else
                {
                    break;
                }
            }
        }
    }
    if(x < 6)
    {
        isValid = false;
        for(int i = x + 2; i <= 7; i++)
        {
            if(sta[i][y] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[i][y] == 0)
                break;
            else
                continue;
        }
        if(isValid)
        {
            for(int i = x + 1; i <= 7; i++)
            {
                if(sta[i][y] == statueIndex)
                {
                    sta[i][y] = opposite;
                    map[i][y]->changeStatus();
                }
                else
                {
                    break;
                }
            }
        }
    }
    if(y > 1)
    {
        isValid = false;
        for(int i = y - 2; i >= 0; i--)
        {
            if(sta[x][i] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[x][i] == 0)
                break;
            else
                continue;
        }
        if(isValid)
        {
            for(int i = y - 1; i >= 0; i--)
            {
                if(sta[x][i] == statueIndex)
                {
                    sta[x][i] = opposite;
                    map[x][i]->changeStatus();
                }
                else
                {
                    break;
                }
            }
        }
    }
    if(y < 6)
    {
        isValid = false;
        for(int i = y + 2; i <= 7; i++)
        {
            if(sta[x][i] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[x][i] == 0)
                break;
            else
                continue;
        }
        if(isValid)
        {
            for(int i = y + 1; i <= 7; i++)
            {
                if(sta[x][i] == statueIndex)
                {
                    sta[x][i] = opposite;
                    map[x][i]->changeStatus();
                }
                else
                {
                    break;
                }
            }
        }
    }
    if(x > 1 && y > 1)
    {
        isValid = false;
        cx = x - 2;
        cy = y - 2;
        while(cx >= 0 && cy >= 0)
        {
            if(sta[cx][cy] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[cx][cy] == 0)
                break;
            else
                {}
            cx--;
            cy--;
        }
        if(isValid)
        {
            cx = x - 1;
            cy = y - 1;
            while(cx >= 0 && cy >= 0)
            {
                if(sta[cx][cy] == statueIndex)
                {
                    sta[cx][cy] = opposite;
                    map[cx][cy]->changeStatus();
                }
                else
                {
                    break;
                }
                cx--;
                cy--;
            }
        }
    }
    if(x < 6 && y > 1)
    {
        isValid = false;
        cx = x + 2;
        cy = y - 2;
        while(cx <= 7 && cy >= 0)
        {
            if(sta[cx][cy] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[cx][cy] == 0)
                break;
            else
                {}
            cx++;
            cy--;
        }
        if(isValid)
        {
            cx = x + 1;
            cy = y - 1;
            while(cx <= 7 && cy >= 0)
            {
                if(sta[cx][cy] == statueIndex)
                {
                    sta[cx][cy] = opposite;
                    map[cx][cy]->changeStatus();
                }
                else
                {
                    break;
                }
                cx++;
                cy--;
            }
        }
    }
    if(x > 1 && y < 6)
    {
        isValid = false;
        cx = x - 2;
        cy = y + 2;
        while(cx >= 0 && cy <= 7)
        {
            if(sta[cx][cy] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[cx][cy] == 0)
                break;
            else
                {}
            cx--;
            cy++;
        }
        if(isValid)
        {
            cx = x - 1;
            cy = y + 1;
            while(cx >= 0 && cy <= 7)
            {
                if(sta[cx][cy] == statueIndex)
                {
                    sta[cx][cy] = opposite;
                    map[cx][cy]->changeStatus();
                }
                else
                {
                    break;
                }
                cx--;
                cy++;
            }
        }
    }
    if(x < 6 && y < 6)
    {
        isValid = false;
        cx = x + 2;
        cy = y + 2;
        while(cx <= 7 && cy <= 7)
        {
            if(sta[cx][cy] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[cx][cy] == 0)
                break;
            else
                {}
            cx++;
            cy++;
        }
        if(isValid)
        {
            cx = x + 1;
            cy = y + 1;
            while(cx <= 7 && cy <= 7)
            {
                if(sta[cx][cy] == statueIndex)
                {
                    sta[cx][cy] = opposite;
                    map[cx][cy]->changeStatus();
                }
                else
                {
                    break;
                }
                cx++;
                cy++;
            }
        }
    }
}

bool PlayScene::canChoose(int x, int y, QString statue)
{
    bool isValid = false;
    int statueIndex, opposite;
    int cx, cy;
    if(statue == white)
    {
        statueIndex = 1;
        opposite = 2;
    }
    else
    {
        statueIndex = 2;
        opposite = 1;
    }
    if(x > 1 && sta[x - 1][y] == statueIndex)
    {
        for(int i = x - 2; i >= 0; i--)
        {
            if(sta[i][y] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[i][y] == 0)
                break;
            else
                continue;
        }
    }
    if(x < 6 && sta[x + 1][y] == statueIndex)
    {
        for(int i = x + 2; i <= 7; i++)
        {
            if(sta[i][y] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[i][y] == 0)
                break;
            else
                continue;
        }
    }
    if(y > 1 && sta[x][y - 1] == statueIndex)
    {
        for(int i = y - 2; i >= 0; i--)
        {
            if(sta[x][i] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[x][i] == 0)
                break;
            else
                continue;
        }
    }
    if(y < 6 && sta[x][y + 1] == statueIndex)
    {
        for(int i = y + 2; i <= 7; i++)
        {
            if(sta[x][i] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[x][i] == 0)
                break;
            else
                continue;
        }
    }
    if(x > 1 && y > 1 && sta[x - 1][y - 1] == statueIndex)
    {
        cx = x - 2;
        cy = y - 2;
        while(cx >= 0 && cy >= 0)
        {
            if(sta[cx][cy] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[cx][cy] == 0)
                break;
            else
                {}
            cx--;
            cy--;
        }
    }
    if(x < 6 && y > 1 && sta[x + 1][y - 1] == statueIndex)
    {
        cx = x + 2;
        cy = y - 2;
        while(cx <= 7 && cy >= 0)
        {
            if(sta[cx][cy] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[cx][cy] == 0)
                break;
            else
                {}
            cx++;
            cy--;
        }
    }
    if(x > 1 && y < 6 && sta[x - 1][y + 1] == statueIndex)
    {
        cx = x - 2;
        cy = y + 2;
        while(cx >= 0 && cy <= 7)
        {
            if(sta[cx][cy] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[cx][cy] == 0)
                break;
            else
                {}
            cx--;
            cy++;
        }
    }
    if(x < 6 && y < 6 && sta[x + 1][y + 1] == statueIndex)
    {
        cx = x + 2;
        cy = y + 2;
        while(cx <= 7 && cy <= 7)
        {
            if(sta[cx][cy] == opposite)
            {
                isValid = true;
                break;
            }
            else if(sta[cx][cy] == 0)
                break;
            else
                {}
            cx++;
            cy++;
        }
    }
    return isValid;
}

bool PlayScene::choice(QString statue)//设选择点并统计得分
{
    bool isChoosed = false;
    scoreBlack = 0;
    scoreWhite = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(sta[i][j] == 0)
            {
                if(canChoose(i, j, statue))
                {
                    this->setSelectBtn(i, j);
                    isChoosed = true;
                }
            }
            else if(sta[i][j] == 1)
            {
                scoreWhite++;
            }
            else
            {
                scoreBlack++;
            }
            //qDebug() << i << j << sta[i][j];
        }
    }
    this->blackLabel->setText(QString::number(scoreBlack));
    this->whiteLabel->setText(QString::number(scoreWhite));
    return isChoosed;
}

PlayScene::PlayScene(QString mod)
{
    this->modIndex = mod;
    //qDebug() << mod;

    this->setFixedSize(1200, 900);
    this->setWindowIcon(QPixmap(":/res/icon.png"));
    if(mod == "onePlayerMod")
        this->setWindowTitle("人机对战");
    else
        this->setWindowTitle("双人对战");

    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("开始");
    QAction * returnAction = startMenu->addAction("返回");
    QAction * quitAction = startMenu->addAction("退出");

    //结束音效
    QSound * endSound = new QSound(":/res/end.wav", this);
    //返回键与落子音效
    QSound * clickSound = new QSound(":/res/click.wav", this);

    //返回键
    MyPushButton * returnBtn = new MyPushButton(":/res/return.png", ":/res/returnPress.png");
    returnBtn->setParent(this);
    returnBtn->move(30, this->height() - returnBtn->height() - 30);

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


    //模式标签
    QLabel * modLabel = new QLabel;
    modLabel->setParent(this);
    modLabel->setFixedSize(400, 150);
    QFont font;
    font.setPointSize(28);
    font.setBold(true);
    font.setFamily("方正字迹-仿颜简体");
    modLabel->setFont(font);
    modLabel->move(30, this->height() - modLabel->height() - 20 - returnBtn->height());
    QString modStr = QString("模式：<br>%1").arg(this->windowTitle());
    modLabel->setText(modStr);

    //走棋标签
    QLabel * moveLabel = new QLabel;
    moveLabel->setParent(this);
    moveLabel->setFixedSize(200, 150);
    moveLabel->setFont(font);
    moveLabel->move(30, 200);
    QString moveStr = QString("走棋：<br>%1").arg(this->moveSide);
    moveLabel->setText(moveStr);

    //黑棋得分
    blackLabel = new QLabel;
    blackLabel->setParent(this);
    blackLabel->setFixedSize(160, 120);
    blackLabel->setFont(font);
    blackLabel->move(160, 350);
    blackLabel->setText(QString::number(scoreBlack));

    //白棋得分
    whiteLabel = new QLabel;
    whiteLabel->setParent(this);
    whiteLabel->setFixedSize(160,120);
    whiteLabel->setFont(font);
    whiteLabel->move(160, 500);
    whiteLabel->setText(QString::number(scoreWhite));

    //初始布局
    this->setChess(3, 3, white);
    this->setChess(4, 4, white);
    this->setChess(3, 4, black);
    this->setChess(4, 3, black);
    this->setSelectBtn(3, 2);
    this->setSelectBtn(2, 3);
    this->setSelectBtn(4, 5);
    this->setSelectBtn(5, 4);
    for(int i = 0; i <= 63; i++)
        sta[i%8][i/8] = 0;
    sta[3][3] = 1;
    sta[3][4] = 2;
    sta[4][3] = 2;
    sta[4][4] = 1;

    //生成电脑
    com = new Computer(this);

    //落子
    connect(this, &PlayScene::selected, [=](int x, int y){
        bool haveChoice;
        if(moveSide == blackZh)
        {
            moveSide = whiteZh;
            this->setChess(x, y, black);
            clickSound->play();
            sta[x][y] = 2;
            this->reverse(x, y, white);
            if(mod == twoPlayerMod)                         //双人对战
            {
                haveChoice = this->choice(black);
                //qDebug() << x << y << haveChoice;
                if(!haveChoice)
                {
                    moveSide = blackZh;
                    haveChoice = this->choice(white);
                    //qDebug() << x << y << haveChoice;
                    if(!haveChoice)
                    {
                        moveSide = "结束";
                        endSound->play();
                    }
                }
            }
            else                                            //人机对战
            {
                QPair<int, int> temp = this->com->placeChess(sta, white);
                if(temp.first == -1)
                {
                    moveSide = blackZh;
                    haveChoice = this->choice(white);
                    if(!haveChoice)
                    {
                        moveSide = "结束";
                        endSound->play();
                    }
                }
                else
                {
                    moveSide = whiteZh;
                    QTimer::singleShot(1000, this,[=](){
                        emit this->selected(temp.first, temp.second);
                    });
                }
            }
        }
        else
        {
            moveSide = blackZh;
            this->setChess(x, y, white);
            clickSound->play();
            sta[x][y] = 1;
            this->reverse(x, y, black);
            if(mod == twoPlayerMod)                         //双人对战
            {
                haveChoice = this->choice(white);
                //qDebug() << x << y << haveChoice;
                if(!haveChoice)
                {
                    moveSide = whiteZh;
                    haveChoice = this->choice(black);
                    //qDebug() << x << y << haveChoice;
                    if(!haveChoice)
                    {
                        moveSide = "结束";
                        endSound->play();
                    }
                }
            }
            else                                            //人机对战
            {
                haveChoice = this->choice(white);
                moveSide = blackZh;
                if(!haveChoice)
                {
                    moveSide = whiteZh;
                    QPair<int, int> temp = this->com->placeChess(sta, white);
                    if(temp.first == -1)
                    {
                        moveSide = "结束";
                        endSound->play();
                    }
                    else
                    {
                        QTimer::singleShot(1000, this,[=](){
                            emit this->selected(temp.first, temp.second);
                        });
                    }
                }
            }
        }
        QString moveStr = QString("走棋：<br>%1").arg(this->moveSide);
        moveLabel->setText(moveStr);
    });

    //调试按钮
//    MyPushButton * test = new MyPushButton(":/res/icon.png");
//    test->setParent(this);
//    connect(test, &MyPushButton::clicked, [=](){
//        setChess(1, 1, black);
//    });

}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/backgroundPlay.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/res/title.png");
    pix = pix.scaled(200, 120);
    painter.drawPixmap(50, 50, pix);
    pix.load(":/res/map.png");
    painter.drawPixmap(300, 50, pix);//棋盘800x800
    pix.load(":/res/chessBlack.png");
    painter.drawPixmap(30, 350, pix);
    pix.load(":/res/chessWhite.png");
    painter.drawPixmap(30, 500, pix);
}
