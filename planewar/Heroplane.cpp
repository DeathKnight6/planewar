#include "Heroplane.h"
#include "config.h"

HeroPlane::HeroPlane() {
    //初始化加载飞机图片
    m_Plane.load(HERO_PATH);

    //初始化飞机坐标
    m_X = (GAME_WIDTH - m_Plane.width()) * 0.5;
    m_Y = (GAME_HEIGHT - m_Plane.height());

    //初始化矩形边框
    m_Rect.setWidth(m_Plane.width());
    m_Rect.setHeight(m_Plane.height());
    m_Rect.moveTo(m_X,m_Y);

    //----------------------------------------------------------
    // 初始化血量
    m_health = m_maxHealth;
    //----------------------------------------------------------5.22
}

void HeroPlane::shoot()
{
    //累加时间间隔记录变量
    m_recorder++;

    //如果记录的数字，未达到发射子弹时间间隔，直接return，不发射子弹
    if(m_recorder < BULLET_TNTERVAL)
    {
        return;
    }

    //达到发射时间
    m_recorder = 0;

    //发射子弹
    for(int i = 0; i < BULLET_NUM; i++)
    {
        //如果是空闲子弹，进行发射
        if(m_bullets[i].m_Free)
        {
            //将空闲状态更改为假
            m_bullets[i].m_Free = false;
            //设置子弹坐标
            m_bullets[i].m_X = m_X;
            m_bullets[i].m_Y = m_Y;
            break;
        }
    }
}

void HeroPlane::setPosition(int x,int y)
{
    m_X =x;
    m_Y =y;
    m_Rect.moveTo(m_X,m_Y);
}

//-----------------------------------------------------------------------------------
int HeroPlane::getHealth() const
{
    //获取血量
    return m_health;
}

void HeroPlane::setHealth(int health)
{
    //设置血量
    m_health = qBound(0, health, m_maxHealth);//设置health的最小值和最大值
}

void HeroPlane::reduceHealth(int damage)
{
    //减少血量
    m_health = qMax(0, m_health - damage);//用于比较两者大小，取值较大的一个
}

bool HeroPlane::isAlive() const
{
    //判断飞机是否存活
    return m_health > 0;
}

void HeroPlane::reset()
{
    //重置飞机状态
    m_health = m_maxHealth;
}

//设置我方飞机子弹伤害
void HeroPlane::setBulletDamage(int damage)
{
    for (int i = 0; i < BULLET_NUM; i++)
    {
        m_bullets[i].setDamage(damage);
    }
}
//-----------------------------------------------------------------------------------5.22
