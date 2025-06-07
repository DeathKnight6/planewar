#ifndef HEROPLANE_H
#define HEROPLANE_H
#include <QPixmap>
#include <QRect>
#include <QGraphicsItem>
#include "Bullet.h"

class HeroPlane
{

public:
    HeroPlane();


    //发射子弹
    void shoot();
    //设置飞机位置
    void setPosition(int x,int y);

    //-----------------------------------------------------------------
    //获取当前血量
    int getHealth() const;
    //设置血量
    void setHealth(int health);
    //减少血量
    void reduceHealth(int damage = 1);
    //判断飞机是否存活
    bool isAlive() const;
    //重置飞机状态
    void reset();
    //------------------------------------------------------------------25.5.22

    //飞机资源 对象
    QPixmap m_Plane;
    //飞机坐标
    int m_X;
    int m_Y;

    //飞机的矩形边框
    QRect m_Rect;

    //弹匣
    Bullet m_bullets[BULLET_NUM];

    //发射间隔记录
    int m_recorder = 0;

    // 5.22新增：设置子弹伤害
    void setBulletDamage(int damage);
    //-----------------------------------------------------------------
private:
    // 飞机血量
    int m_health;
    // 最大血量
    const int m_maxHealth = 100;
    //-----------------------------------------------------------------25.5.22
};

#endif // HEROPLANE_H
