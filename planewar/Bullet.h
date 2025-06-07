#ifndef BULLET_H
#define BULLET_H
#include "config.h"
#include <QPixmap>

class Bullet
{
public:
    Bullet();

    //更新子弹坐标
    void updatePosition();

    //子弹资源对象
    QPixmap m_Bullet;

    // 新增：获取和设置子弹伤害
    int getDamage() const;
    void setDamage(int damage);

    //子弹坐标
    int m_X;
    int m_Y;

    //子弹移动速度
    int m_Speed;

    //子弹是否闲置
    bool m_Free;

    //子弹的矩形边框（用于碰撞检测）
    QRect m_Rect;

protected:
    int m_damage;  // 子弹伤害值
};

#endif // BULLET_H
