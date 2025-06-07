#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include <QPixmap>
#include "config.h"

class EnemyPlane
{
public:
    EnemyPlane();

    //更新坐标
    void updatePosition();

    //----------------------------------------------------------------------
    //发射子弹
    void shoot();
    //设置位置
    void setPosition(int x, int y);
    //获取当前血量
    int getHealth() const;
    //设置血量
    void setHealth(int health);
    //设置速度
    void setSpeed(int speed);
    //减少血量
    void reduceHealth(int damage = 1);
    //判断敌机是否存活
    bool isAlive() const;
    //重置敌机状态
    void reset();
    //-----------------------------------------------------------------------5.22

    //敌机资源对象
    QPixmap m_enemy;

    //位置
    int m_X;
    int m_Y;

    //敌机的矩形边框
    QRect m_Rect;

    //状态
    bool m_Free;

    //速度
    int m_Speed;

    //------------------------------------------------------
private:
    // 敌机血量
    int m_health;
    // 最大血量
    const int m_maxHealth = 100;
    // 敌机速度
    int m_speed;
    //------------------------------------------------------5.22
};

#endif // ENEMYPLANE_H
