#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
<<<<<<< HEAD
#include "BOSSbullet.h"
=======
>>>>>>> a8bb9635c82d0e3b992904b4a550a601c4f9fa07
#include <QPixmap>
#include <QRect>

//子弹方向
<<<<<<< HEAD
/*enum BulletDirection {
    DOWN,  // 向下（默认）
    UP     // 向上
};*/
=======
enum BulletDirection {
    DOWN,  // 向下（默认）
    UP     // 向上
};
>>>>>>> a8bb9635c82d0e3b992904b4a550a601c4f9fa07

class EnemyBullet
{
public:
    EnemyBullet();

    //更新子弹位置
    void updatePosition();

    //子弹资源对象
    QPixmap m_Bullet;

    //子弹坐标
    int m_Xe;
    int m_Ye;

    // 设置发射方向
    void setDirection(BulletDirection direction);

    //子弹的矩形边框
    QRect m_Rect;

    //子弹状态
    bool m_Free;

    //子弹速度
    int m_Speed;

    // 获取和设置子弹伤害
    int getDamage() const;
    void setDamage(int damage);

private:
    int m_damage;
    BulletDirection m_direction;  // 子弹发射方向
};

#endif // ENEMYBULLET_H
