#include "BOSSbullet.h"
#include "config.h"

BOSSbullet::BOSSbullet()
{
    // 加载子弹资源
    m_Bullet.load(ENEMYBullet_PATH);

    // 初始化子弹位置
    m_Xe = 0;
    m_Ye = 0;

    // 初始化子弹状态
    m_Free = true;

    // 初始化子弹速度
    m_Speed = BOSSBullet_BULLET_SPEED;

    // 初始化子弹矩形
    m_Rect.setWidth(m_Bullet.width());
    m_Rect.setHeight(m_Bullet.height());
    m_Rect.moveTo(m_Xe, m_Ye);

    // 默认向下发射子弹
    m_direction = DOWN;
}

void BOSSbullet::setDirection(BulletDirection direction)
{
    m_direction = direction;
}

void BOSSbullet::updatePosition()
{
    // 如果子弹处于空闲状态，不更新位置
    if (m_Free) {
        return;
    }

    // 更新子弹位置
    m_Ye += m_Speed;
    m_Rect.moveTo(m_Xe, m_Ye);

    // 判断子弹是否超出屏幕
    if (m_Ye >= GAME_HEIGHT) {
        m_Free = true;
    }
}

int BOSSbullet::getDamage() const
{
    return m_damage;
}

void BOSSbullet::setDamage(int damage)
{
    m_damage = damage;
}
