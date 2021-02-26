#ifndef CHESS_H
#define CHESS_H

#include <QLabel>
#include <QTimer>

class Chess : public QLabel
{
    Q_OBJECT
public:
    Chess(QString chessStatus);
    QString chessStatusIndex;
    void changeStatus();
    QTimer * timerBlack;
    QTimer * timerWhite;
    int minPix = 1;
    int maxPix = 6;
    const QString white = "White";
    const QString black = "Black";

signals:

};

#endif // CHESS_H
