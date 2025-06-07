#include "Enemyplane.h"
#include "config.h"
#include <QRandomGenerator>

EnemyPlane::EnemyPlane()
{
    //--------------------------------------------------
    // 初始化血量
    m_health = m_maxHealth;
    //--------------------------------------------------5.22
    //敌机资源加载
    m_enemy.load(ENEMY_PATH);

    //敌机位置
    m_X = 0;
    m_Y = 0;

    //敌机状态
    m_Free = true;

    //敌机速度
    m_Speed = ENEMY_SPEED;

    //敌机矩形框
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_X,m_Y);
}

void EnemyPlane::updatePosition()
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
int EnemyPlane::getHealth() const
{
    //获取血量
    return m_health;
}

void EnemyPlane::setHealth(int health)
{
    //设置血量
    m_health = qBound(0, health, m_maxHealth);//设置health的最小值和最大值
}

void EnemyPlane::setSpeed(int speed)
{
    //设置速度
    m_speed = ENEMY_SPEED;
}

void EnemyPlane::reduceHealth(int damage)
{
    //减少血量
    m_health = qMax(0, m_health - damage);//用于比较两者大小，取值较大的一个
}

bool EnemyPlane::isAlive() const
{
    //判断飞机是否存活
    return m_health > 0;
}

void EnemyPlane::reset()
{
    //重置飞机状态
    m_health = m_maxHealth;
    m_Free = true;
}
//------------------------------------------------------------------------
