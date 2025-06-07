#ifndef BOSS_H
#define BOSS_H
#include <QPixmap>
#include "BOSSbullet.h"
#include "config.h"

class BOSS
{
public:
    BOSS();

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
    //减少血量
    void reduceHealth(int damage = 1);
    //判断敌机是否存活
    bool isAlive() const;
    //重置敌机状态
    void reset();
    //设置子弹伤害
    void setBulletDamage(int damage);
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
    //子弹数组
    BOSSbullet m_bullets[ENEMY_BULLET_NUM];
    //发射间隔记录
    int m_shootTimer;
private:
    // 敌机血量
    int m_health;
    // 最大血量
    const int m_maxHealth = 1000;
    //------------------------------------------------------5.22
};

#endif // BOSS_H
