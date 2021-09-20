#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include "map.h"
#include "heroplane.h"
#include "bullet.h"
#include "enemyplane.h"
#include "bomb.h"

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = 0);
    ~MainScene();

    //初始化游戏主场景
    void initScene();

    //启动游戏  用于启动定时器对象
    void palyGame();

    //更新坐标
    void updatePosition();

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *);

    //碰撞检测
    void collisionDetection();

    //地图对象
    Map m_Map;

    //英雄飞机对象
    HeroPlane m_Hp;

    //敌机出场
    void enemyToScene();
    //敌机数组
    EnemyPlane m_Enemys[ENEMY_NUM];

    //爆炸数组
    Bomb m_Bombs[BOMB_NUM];

//    //测试子弹代码
//    Bullet temp_Bullet;

    //定时器对象
    QTimer m_Timer;

private:
    //敌机出场间隔记录
    int m_Recorder;

    ////记录最终得分(击败1架飞机100分)
    static int m_Score;

};

#endif // MAINSCENE_H
