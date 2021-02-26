#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "chess.h"
#include "computer.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(QString mod = "twoPlayerMod");

    const QString twoPlayerMod = "twoPlayerMod";
    const QString onePlayerMod = "onePlayerMod";
    const QString whiteZh = "白棋";
    const QString blackZh = "黑棋";
    QString modIndex;
    QString moveSide = blackZh;
    QLabel * moveLabel = NULL;
    QLabel * blackLabel = NULL;
    QLabel * whiteLabel = NULL;
    Computer * com = NULL;
    int scoreBlack = 2;
    int scoreWhite = 2;
    const QString white = "White";
    const QString black = "Black";

    void setChess(int x, int y, QString statue = "Black");
    void setSelectBtn(int x, int y);
    void reverse(int x, int y, QString statue = "Black");
    bool canChoose(int x, int y, QString statue = "Black");
    bool choice(QString statue = "Black");
    //statue means chess's statues to be reversed
    void paintEvent(QPaintEvent *);

    Chess * map[8][8];
    int sta[8][8];
    /*
     * 0:空
     * 1:白
     * 2:黑
     */

signals:
    void chooseSceneBack();
    void selected(int x, int y);

};

#endif // PLAYSCENE_H
