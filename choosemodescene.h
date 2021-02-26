#ifndef CHOOSEMODESCENE_H
#define CHOOSEMODESCENE_H

#include <QMainWindow>
#include <playscene.h>

class ChooseModeScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseModeScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    //游戏场景
    PlayScene * play = NULL;

signals:
    void chooseSceneBack();

};

#endif // CHOOSEMODESCENE_H
