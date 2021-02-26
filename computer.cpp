#include "computer.h"
#include <QPair>
#include <QTime>
#include <QDebug>

Computer::Computer(QObject *parent) : QObject(parent)
{

}

int Computer::num(int x, int y, int sta[8][8], QString statue)
{
    int out = 0;
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
                out += x - i - 1;
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
                out += i - x - 1;
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
                out += y - i - 1;
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
                out += i - y - 1;
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
                out += x - cx - 1;
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
                out += cx - x - 1;
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
                out += x - cx - 1;
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
                out += cx - x - 1;
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
    //qDebug() << x << y << out;
    return out;
}

QPair<int, int> Computer::placeChess(int sta[8][8], QString statue)
{
    QPair<int, int> out;
    int maxNumber = 0, choiceNumber = 0, temp;
    int choice[64][2];
    if(statue == white)
        statue = black;
    else
        statue = white;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            temp = 0;
            if(sta[i][j] == 0)
                temp = num(i, j, sta, statue);
            if(temp > maxNumber)
            {
                maxNumber = temp;
                choiceNumber = 1;
                choice[0][0] = i;
                choice[0][1] = j;
            }
            else if(temp == maxNumber && temp > 0)
            {
                choice[choiceNumber][0] = i;
                choice[choiceNumber][1] = j;
                choiceNumber++;
            }
            else
                continue;
        }
    }
    if(maxNumber == 0)
    {
        out.first = -1;
        out.second = -1;
    }
    else
    {
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int n = qrand() % choiceNumber;             //生成随机数
        out.first = choice[n][0];
        out.second = choice[n][1];
    }
    qDebug() << out.first << out.second;
    return out;
}
