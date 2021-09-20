#include "mainscene.h"

#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QMenuBar>
#include <ctime>
#include <QSound>
#include <QFile>
#include <QDebug>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    //设置菜单栏(待实现功能)
//    QMenuBar * menu = new QMenuBar(this);
//    QMenu * file = menu->addMenu("文件");
//    QAction * save = file->addAction("保存进度"); //记录飞机位置
//    file->addSeparator(); //分隔线
//    QAction * recovery = file->addAction("恢复存档");//恢复飞机位置
//    file->addSeparator();
//    QAction * quit  = file->addAction("退出游戏");

//    //实现退出游戏功能
//    connect(quit, QAction::triggered, [=](){
//       this->close();
//    });

    //1、调用接口进行初始化主窗口
    this->initScene();

    //2、启动游戏
    this->palyGame();
}

//记录得分初始化
int MainScene::m_Score = 0;

MainScene::~MainScene()
{

}

inline
void MainScene::initScene()
{
    //随机数种子
    srand((unsigned int)time(NULL));

    //初始化窗口为固定大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);

    //设置图标资源
    setWindowIcon(QIcon(GAME_ICON));

    //定时器设置 时间间隔
    m_Timer.setInterval(GAME_RATE);

    this->m_Score = 0;////
    this->m_Recorder = 0;
}


inline
void MainScene::palyGame()
{
    ////启动背景音乐
    QSound::play(SOUND_BACKGROUND);

    //启动定时器
    m_Timer.start();

    //监听定时器
    connect(&m_Timer, &QTimer::timeout, [=](){
        //敌机出场
        this->enemyToScene();

        //更新游戏中地图、子弹坐标
        this->updatePosition();

        //重新绘制地图(相当于调用paintEvent事件)
        this->update();

        //碰撞检测
        this->collisionDetection();

//        if(m_Score <= 100000) //设定最高分为100000，高于则不写入文件
//        {
//            ////保存最终得分到文件
//            QFile file(QString(FILE_PATH));
//            file.open(QIODevice::Append | QIODevice::Truncate); //追加并重写的方式打开，写入新的数据时会将原有数据全部清除
//            QString str = QString::number(m_Score); //int转为QString
//            const char *score = str.toStdString().c_str(); //Qstring 转换为 char *
//            file.write(score);
//            file.write("\n");
//            file.close();
//        }

    });

}

inline
void MainScene::updatePosition()
{
    //更新地图坐标
    m_Map.mapPosition();

    //发射子弹
    m_Hp.shoot();
    //计算子弹坐标
    for(int i = 0; i<BULLET_NUM; ++i)
    {
        //如果子弹状态为非空闲，计算发射位置
        if( !m_Hp.m_Bullets[i].m_Free)
        {
            m_Hp.m_Bullets[i].updatePosition();
        }
    }

    //计算敌机坐标
    for(int i = 0; i<ENEMY_NUM; ++i)
    {
        //非空闲敌机 更新坐标
        if( !m_Enemys[i].m_Free)
        {
            m_Enemys[i].updatePosition();
        }
    }

    //计算爆炸播放的效果图
    for(int i = 0; i < BOMB_MAX; ++i)
    {
        //非空闲敌机 更新图片下标信息
        if( !m_Bombs[i].m_Free)
        {
            m_Bombs[i].updateInfo();
        }
    }


//    //测试子弹代码
//    temp_Bullet.m_Free = false; //子弹非空闲
//    temp_Bullet.updatePosition();
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //在当前窗口画，头文件#include <QPainter>

    //绘制地图
    painter.drawPixmap(0,m_Map.m_map1_posY,m_Map.m_Map1); //第一张
    painter.drawPixmap(0,m_Map.m_map2_posY,m_Map.m_Map2); //第二张

    //绘制英雄飞机
    painter.drawPixmap(m_Hp.m_X, m_Hp.m_Y, m_Hp.m_Plane);

    //绘制子弹
    for(int i = 0; i<BULLET_NUM; ++i)
    {
        //如果子弹状态为非空闲
        if( !m_Hp.m_Bullets[i].m_Free)
        {
            painter.drawPixmap(m_Hp.m_Bullets[i].m_X, m_Hp.m_Bullets[i].m_Y,m_Hp.m_Bullets[i].m_Bullet);
        }
    }

    //绘制敌机
    for(int j = 0; j<ENEMY_NUM; ++j)
    {
        //非空闲敌机 绘制敌机
        if( m_Enemys[j].m_Free == false)
        {
            painter.drawPixmap(m_Enemys[j].m_X, m_Enemys[j].m_Y, m_Enemys[j].m_Enemy);
        }
    }

    //绘制爆炸图片
    for(int k = 0; k < BOMB_MAX; ++k)
    {
        //非空闲敌机 根据vector数组 m_PixArr 绘制图片
        if( !m_Bombs[k].m_Free)
        {
            painter.drawPixmap(m_Bombs[k].m_X, m_Bombs[k].m_Y, m_Bombs[k].m_PixArr[m_Bombs[k].m_Index]);
        }
    }

//    //测试子弹
//    painter.drawPixmap(temp_Bullet.m_X,temp_Bullet.m_Y,temp_Bullet.m_Bullet);
}

void MainScene::mouseMoveEvent(QMouseEvent * event)
{
    int x = event->x()-m_Hp.m_Rect.width() * 0.5; //鼠标位置 - 飞机矩形的一半
    int y = event->y()-m_Hp.m_Rect.height() * 0.5; //记录y坐标

    //边缘检测
    if(x<=0)
    {
        x = 0;
    }
    if(x>=GAME_WIDTH-m_Hp.m_Rect.width())
    {
        x = GAME_WIDTH-m_Hp.m_Rect.width();
    }
    if(y<=0)
    {
        y = 0;
    }
    if(y>=GAME_HEIGHT-m_Hp.m_Rect.height())
    {
        y = GAME_HEIGHT-m_Hp.m_Rect.height();
    }

    //设置飞机位置
    this->m_Hp.setPosition(x, y);
}

void MainScene::enemyToScene()
{
    //累加时间间隔记录变量
    this->m_Recorder++;
    //判断如果记录数字 未达到发射间隔，直接return
    if(m_Recorder < ENEMY_INTERVAL)
    {
        return;
    }

    //到达时间间隔
    //重置飞机 发射时间间隔记录
    this->m_Recorder = 0;

    //敌机出场
    for(int i = 0; i<ENEMY_NUM; ++i)
    {
        if(m_Enemys[i].m_Free)
        {
            //敌机空闲状态改为false
            m_Enemys[i].m_Free = false;
            //设置出场坐标
            m_Enemys[i].m_X = rand() % (GAME_WIDTH - m_Enemys[i].m_Rect.width()); //0到屏幕宽-飞机宽
            m_Enemys[i].m_Y = -m_Enemys[i].m_Rect.height();
            break; //一次时间间隔内只发射一个
        }
    }
}

void MainScene::collisionDetection()
{
     //遍历所有非空闲的敌机
    for(int i = 0; i<ENEMY_NUM; ++i)
    {
        if(m_Enemys[i].m_Free)
        {
            continue; //空闲飞机 跳转下一次循环
        }

         //遍历所有 非空闲的子弹
        for(int j = 0; j<BULLET_NUM; ++j)
        {
            if(m_Hp.m_Bullets[j].m_Free)
            {
                continue;//空闲子弹 跳转下一次循环
            }

            //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可（intersects函数）
            if(m_Enemys[i].m_Rect.intersects(m_Hp.m_Bullets[j].m_Rect))
            {
                m_Enemys[i].m_Free = true;
                m_Hp.m_Bullets[j].m_Free = true;

                m_Score+=100; ////得分以100分递增
                qDebug()<< m_Score; //测试代码，头文件#include <QDebug>
//                if(m_Score <= 100000) //设定最高分为100000，高于则不写入文件
//                {
//                    ////保存最终得分到文件
//                    QFile file(QString(FILE_PATH));
//                    file.open(QIODevice::Append | QIODevice::Truncate); //追加并重写的方式打开，写入新的数据时会将原有数据全部清除
//                    QString str = QString::number(m_Score); //int转为QString
//                    const char *score = str.toStdString().c_str(); //Qstring 转换为 char *
//                    file.write(score);
//                    file.write("\n");
//                    file.close();
//                }

                //播放爆炸效果
                for(int k = 0; k<BOMB_MAX; ++k)
                {
                    if(m_Bombs[k].m_Free)
                    {
                        ////播放爆炸音效
                        QSound::play(SOUND_BOMB);

                        //爆炸状态设置为非空闲
                        m_Bombs[k].m_Free = false;
                        //更新坐标
                        m_Bombs[k].m_X = m_Enemys[i].m_X;
                        m_Bombs[k].m_Y = m_Enemys[i].m_Y;
                        break;
                    }
                }
            }
        }
    }

}
