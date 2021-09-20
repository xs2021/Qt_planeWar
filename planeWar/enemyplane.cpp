#include "enemyplane.h"
#include "config.h"

EnemyPlane::EnemyPlane()
{
    //敌机资源加载
    this->m_Enemy.load(ENEMY_PATH);

    //敌机位置
    this->m_X = 0;
    this->m_Y = 0;

    //敌机空闲状态
    this->m_Free = true;

    //敌机速度
    this->m_Speed = ENEMY_SPEED;

    //敌机矩形边框
    this->m_Rect.setWidth(this->m_Enemy.width());
    this->m_Rect.setHeight(this->m_Enemy.height());
    this->m_Rect.moveTo(m_X, m_Y);
}

void EnemyPlane::updatePosition()
{
    //空闲状态，不计算坐标
    if(m_Free)
    {
        return;
    }

    //发射飞机
    this->m_Y += this->m_Speed;
    this->m_Rect.moveTo(m_X, m_Y);

    //飞出屏幕外部，变为空闲
    if(m_Y >= GAME_HEIGHT)
    {
        this->m_Free = true;
    }
}
