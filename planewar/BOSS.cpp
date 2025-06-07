#include "BOSS.h"
#include "config.h"
#include <QRandomGenerator>

BOSS::BOSS()
{
    //--------------------------------------------------
    // 初始化血量
    m_health = m_maxHealth;
    //--------------------------------------------------5.22
    //敌机资源加载
    m_enemy.load(BOSS_PATH);

    //敌机位置
    m_X = 0;
    m_Y = 0;

    //敌机状态
    m_Free = true;


    //敌机矩形框
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_X,m_Y);
}

//发射子弹
void BOSS::shoot()
{
    // 射击间隔控制
    m_shootTimer++;
    if (m_shootTimer < ENEMY_SHOOT_INTERVAL) {
        return;
    }

    m_shootTimer = 0;

    // 随机发射子弹（增加游戏趣味性）
    if (QRandomGenerator::global()->bounded(100) < 30) {
        return;
    }

    // 发射子弹
    for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
        if (m_bullets[i].m_Free) {
            // 设置子弹位置（从敌机底部中央发射）
            m_bullets[i].m_Xe = m_X + m_Rect.width() / 2 - m_bullets[i].m_Rect.width() / 2;
            m_bullets[i].m_Ye = m_Y + m_Rect.height();
            m_bullets[i].m_Free = false;
            break;
        }
    }
}

//设置敌机子弹伤害
void BOSS::setBulletDamage(int damage)
{
    for (int i = 0; i < ENEMY_BULLET_NUM; i++)
    {
        m_bullets[i].setDamage(damage);
    }
}

void BOSS::updatePosition()
{
    //空闲状态敌机 不计算坐标
    if(m_Free)
    {
        return;
    }

    m_Y += m_Speed;
    m_Rect.moveTo(m_X,m_Y);

    //如果超出屏幕
    if(m_X >= GAME_HEIGHT + m_Rect.height())
    {
        m_Free = true;
    }
}
//-----------------------------------------------------------------------------
int BOSS::getHealth() const
{
    //获取血量
    return m_health;
}

void BOSS::setHealth(int health)
{
    //设置血量
    m_health = qBound(0, health, m_maxHealth);//设置health的最小值和最大值
}

void BOSS::reduceHealth(int damage)
{
    //减少血量
    m_health = qMax(0, m_health - damage);//用于比较两者大小，取值较大的一个
}

bool BOSS::isAlive() const
{
    //判断飞机是否存活
    return m_health > 0;
}

void BOSS::reset()
{
    //重置飞机状态
    m_health = m_maxHealth;
    m_Free = true;
    m_shootTimer = 0;
}
//------------------------------------------------------------------------
