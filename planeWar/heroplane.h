#ifndef HEROPLANE_H
#define HEROPLANE_H

#include <QPixmap>
#include "bullet.h"

class HeroPlane
{
public:
    HeroPlane();

    //发射子弹
    void shoot();

    //设置飞机位置
    void setPosition(const int &x, const int &y);

public:
    //飞机资源 对象
    QPixmap m_Plane;

    //飞机坐标
    int m_X;
    int m_Y;

    //飞机矩形边框
    QRect m_Rect;

    //弹匣数组
    Bullet m_Bullets[BULLET_NUM];

    //发射间隔记录
    int m_Recorder;
};

#endif // HEROPLANE_H
