#include "map.h"
#include "config.h"

Map::Map()
{
    //初始化加载地图对象
    m_Map1.load(MAP_PATH);
    m_Map2.load(MAP_PATH);

    //设置两张地图起始y轴坐标
    m_map1_posY = -GAME_HEIGHT; //在窗口的负高度
    m_map2_posY = 0;  //从窗口开始

    //设置地图滚动速度
    m_scroll_speed = MAP_SCROLL_SPEED;
}

void Map::mapPosition()
{
    //处理第一张图片滚动
    m_map1_posY += MAP_SCROLL_SPEED;
    if(m_map1_posY >= 0)
    {
        m_map1_posY = -GAME_HEIGHT; //回原始位置
    }

    //处理第二张图片滚动
    m_map2_posY += MAP_SCROLL_SPEED;
    if(m_map2_posY >= GAME_HEIGHT)
    {
        m_map2_posY = 0; //回原始位置
    }
}
