#include "chess.h"
#include <QTimer>
#include <QPixmap>
#include <QLabel>

Chess::Chess(QString chessStatus)
{
    chessStatusIndex = chessStatus;
    QString chessImg = ":/res/chessWhite.png";
    if(chessStatusIndex == white)
        chessImg = ":/res/chessWhite.png";
    else
        chessImg = ":/res/chessBlack.png";
    QPixmap pix;
    pix.load(chessImg);
    this->setFixedSize(80, 80);
    pix = pix.scaled(this->size());
    this->setPixmap(pix);
    timerBlack = new QTimer(this);
    timerWhite = new QTimer(this);
    connect(timerBlack, &QTimer::timeout, [=](){
        if(minPix <= maxPix)
        {
            QString str = QString(":/res/chess0%1.png").arg(Chess::minPix);
            QPixmap pix;
            pix.load(str);
            this->setFixedSize(80, 80);
            pix = pix.scaled(this->size());
            this->setPixmap(pix);
            minPix++;
        }
        else
        {
            minPix = 1;
            timerBlack->stop();
            QString str = QString(":/res/chessWhite.png");
            QPixmap pix;
            pix.load(str);
            this->setFixedSize(80, 80);
            pix = pix.scaled(this->size());
            this->setPixmap(pix);
        }
    });
    connect(timerWhite, &QTimer::timeout, [=](){
        if(minPix <= maxPix)
        {
            QString str = QString(":/res/chess0%1.png").arg(Chess::maxPix);
            QPixmap pix;
            pix.load(str);
            this->setFixedSize(80, 80);
            pix = pix.scaled(this->size());
            this->setPixmap(pix);
            maxPix--;
        }
        else
        {
            maxPix = 6;
            timerWhite->stop();
            QString str = QString(":/res/chessBlack.png");
            QPixmap pix;
            pix.load(str);
            this->setFixedSize(80, 80);
            pix = pix.scaled(this->size());
            this->setPixmap(pix);
        }
    });
}

void Chess::changeStatus()
{
    if(chessStatusIndex == black)
    {
        chessStatusIndex = white;
        timerBlack->start(50);
    }
    else
    {
        chessStatusIndex = black;
        timerWhite->start(50);
    }
}
