#include "bullet.h"

Bullet::Bullet()
{
    //加载子弹资源
    this->m_Bullet.load(BULLET_PATH);

    //子弹坐标 初始坐标可随意设置，后期会重置
    this->m_X = (GAME_WIDTH-m_Bullet.width())*0.5;
    this->m_Y = GAME_HEIGHT;

    //子弹空闲状态
    this->m_Free = true;

    //子弹速度
    this->m_Speed = BULLET_SPEED;

    //子弹矩形框
    this->m_Rect.setWidth(m_Bullet.width());
    this->m_Rect.setHeight(m_Bullet.height());
    this->m_Rect.moveTo(this->m_X,this->m_Y);
}

void Bullet::updatePosition()
{
    //如果子弹是空闲状态，不需要坐标计算
    if(m_Free)
    {
        return;
    }

    //飞机可以控制子弹的空闲状态为false
    this->m_Y -= this->m_Speed;    //子弹向上移动
    this->m_Rect.moveTo(m_X,m_Y); //边框更新位置

    //超出屏幕,重置子弹为空闲状态
    if(this->m_Y <= -this->m_Rect.height())
    {
        this->m_Free = true;
    }

}
