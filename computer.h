#ifndef COMPUTER_H
#define COMPUTER_H

#include <QObject>
#include <QPair>

class Computer : public QObject
{
    Q_OBJECT
public:
    explicit Computer(QObject *parent = nullptr);
    QPair<int, int> placeChess(int sta[8][8], QString statue = "White");
    //statue执棋
    int num(int x, int y, int sta[8][8], QString statue = "White");
    //statue被翻转棋
    const QString white = "White";
    const QString black = "Black";

signals:

};

#endif // COMPUTER_H
