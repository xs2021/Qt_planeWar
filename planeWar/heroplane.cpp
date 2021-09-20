#include "heroplane.h"
#include "config.h"
#include <QFile>
#include <QString>

HeroPlane::HeroPlane()
    :m_Recorder(0)//初始化发射间隔记录
{
    //初始化加载飞机图片资源
    this->m_Plane.load(HERO_PATH);

    //初始化飞机坐标
    this->m_X = GAME_WIDTH * 0.5 - m_Plane.width() * 0.5;
    this->m_Y = GAME_HEIGHT-m_Plane.height();

    //初始化矩形框
    this->m_Rect.setWidth(m_Plane.width());
    this->m_Rect.setHeight(m_Plane.height());
    this->m_Rect.moveTo(m_X, m_Y);
}

void HeroPlane::setPosition(const int &x, const int &y)
{
    //自身位置等于拖动的位置
    this->m_X = x;
    this->m_Y = y;

//    ////保存自身位置
//    QFile file(QString(FILE_PATH));
//    file.open(QIODevice::Append);
//    QString strX = QString::number(m_X); //int转为QString
//    const char *p = strX.toStdString().c_str(); //Qstring 转换为 char *
//    file.write(p);
//    file.close();

    this->m_Rect.moveTo(this->m_X, this->m_Y);
}

void HeroPlane::shoot()//一直在不停的调用
{
    //累加时间间隔记录变量
    this->m_Recorder++;
    //判断如果记录数字 未达到发射间隔，直接return
    if(m_Recorder < BULLET_INTERVAL)
    {
        return;
    }

    //到达时间间隔
    //重置子弹发射时间间隔记录
    this->m_Recorder = 0;

    //发射子弹
    for(int i = 0; i<BULLET_NUM; ++i)
    {
        //如果是空闲的子弹进行发射
        if( m_Bullets[i].m_Free)
        {
            //将改子弹空闲状态改为假
            this->m_Bullets[i].m_Free = false;
            //设置发射的子弹坐标
            this->m_Bullets[i].m_X = m_X + m_Rect.width()*0.5 - 10;
            this->m_Bullets[i].m_Y = m_Y - 25;
            break; //一次时间间隔发射一个
        }

    }
}


