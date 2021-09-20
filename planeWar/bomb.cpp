#include "bomb.h"

Bomb::Bomb()
    :m_X(0),m_Y(0),m_Free(true),m_Index(0),m_Recoder(0)
{
    //初始化爆炸图片数组
    for(int i = 1; i<BOMB_NUM; ++i)
    {
        //字符串拼接，类似  ":/res/bomb-1.png"
        QString str = QString(BOMB_PATH).arg(i);
        m_PixArr.push_back(QPixmap(str));
    }

//    //初始化坐标
//    this->m_X = 0;
//    this->m_Y = 0;

//    //初始化空闲状态
//    this->m_Free = true;

//    //当前播放图片下标
//    this->m_Index = 0;

//    //爆炸间隔记录
//    this->m_Recoder = 0;
}

void Bomb::updateInfo()
{
    //空闲状态
    if(m_Free)
    {
        return;
    }

    m_Recoder++;
    //如果记录 小于 爆炸间隔，直接return，不需要切图
    if(m_Recoder < BOMB_INTERVAL)
    {
        return;
    }

    //重置记录为0
    m_Recoder = 0;

    //切换爆炸播放图片
    m_Index++;
    //注：数组中的下标从0开始，最大是6
    if(m_Index > BOMB_MAX-1)
    {
        m_Index = 0;//如果计算的下标大于6，重置为0
        m_Free = true; //同时爆炸为空闲
    }

}
