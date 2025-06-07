#include "Mainsence2.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include <QCoreApplication>
#include <QAudioOutput>

Mainsence2::Mainsence2(QWidget *parent)
    : QWidget(parent)
{
    //调用初始化窗口函数
    initSence();

    //启动
    playGame();

}

Mainsence2::~Mainsence2() {}

void Mainsence2::initSence()
{
    //设置窗口固定
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置标题
    setWindowTitle(GAME_TITLE);

    //加载图标
    setWindowIcon(QIcon(GAME_ICON));

    //定时器初始化
    m_Timer.setInterval(GAME_RATE);

    //敌机出场间隔初始化
    m_recorder = 0;

    //随机数种子
    srand((unsigned int)time(NULL));

    // 设置我方子弹伤害
    m_hero.setBulletDamage(20);  // 我方普通子弹伤害为20

    // 设置敌机子弹伤害
    for (int i = 0; i < ENEMY_NUM2; i++)
    {
        m_enemys[i].setBulletDamage(10);  // 敌机普通子弹伤害为10
    }
}

void Mainsence2::playGame()
{


    //启动定时器
    m_Timer.start();
    //监听定时器发送信号
    connect(&m_Timer , &QTimer::timeout,[=]()
            {
                //敌机出场
                enemyToScene();
                //更新游戏中元素坐标
                updatePosition();
                //绘制到屏幕中
                update();
                //碰撞检测
                collisionDetection();
            });
}

void Mainsence2::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();

    //发射子弹
    m_hero.shoot();

    //计算所有非空闲子弹的当前坐标
    for(int i = 0; i < BULLET_NUM; i++)
    {
        //如果非空闲，计算发射位置
        if(m_hero.m_bullets[i].m_Free == false)
        {
            m_hero.m_bullets[i].updatePosition();
        }
    }

    //敌机出场
    for(int i = 0; i < ENEMY_NUM2; i++)
    {
        if(m_enemys[i].m_Free == false)
        {
            m_enemys[i].updatePosition();
            m_enemys[i].shoot();

            //更新敌机子弹位置
            for (int j = 0; j < ENEMY_BULLET_NUM; j++)
            {
                if (!m_enemys[i].m_bullets[j].m_Free)
                {
                    m_enemys[i].m_bullets[j].updatePosition();
                }
            }
        }
    }

    //计算爆炸的播放的图片
    for(int i = 0; i < BOMB_NUM; i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            m_bombs[i].updateInfo();
        }
    }

}

void Mainsence2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);

    //绘制飞机
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);



    //绘制我方子弹
    for(int i = 0; i < BULLET_NUM; i++)
    {
        //如果非空闲，绘制
        if(m_hero.m_bullets[i].m_Free == false)
        {
            painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet);
        }
    }

    //绘制敌机
    for(int i = 0; i < ENEMY_NUM2; i++)
    {
        if(m_enemys[i].m_Free == false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy2);

            //绘制敌机子弹
            for (int j = 0; j < ENEMY_BULLET_NUM; j++)
            {
                if (m_enemys[i].m_bullets[j].m_Free == false)
                {
                    painter.drawPixmap(m_enemys[i].m_bullets[j].m_Xe,
                                       m_enemys[i].m_bullets[j].m_Ye,
                                       m_enemys[i].m_bullets[j].m_Bullet);
                }
            }
        }
    }

    //绘制爆炸
    for(int i = 0; i < BOMB_NUM; i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }
}

void Mainsence2::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = event->position();
    qreal x = pos.x() - m_hero.m_Rect.width()*0.5;
    qreal y = pos.y() - m_hero.m_Rect.height()*0.5;

    //边界检测
    if(x <= 0)
    {
        x = 0;
    }
    if(x >= GAME_WIDTH - m_hero.m_Rect.width())
    {
        x = GAME_WIDTH - m_hero.m_Rect.width();
    }
    if(y <= 0)
    {
        y = 0;
    }
    if(y >= GAME_HEIGHT - m_hero.m_Rect.height())
    {
        y = GAME_HEIGHT - m_hero.m_Rect.height();
    }

    m_hero.setPosition(x,y);
}

void Mainsence2::enemyToScene()
{
    m_recorder++;
    //未达到出场间隔 直接return
    if(m_recorder < ENEMY_INTERVAL2)
    {
        return;
    }
    m_recorder = 0;

    for(int i = 0; i < ENEMY_NUM2; i++)
    {
        //如果是空闲敌机 出场
        if(m_enemys[i].m_Free)
        {
            m_enemys[i].m_Free = false;

            //坐标
            m_enemys[i].m_X = rand()%(GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = - m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void Mainsence2::collisionDetection()
{
    // 我方子弹与敌机碰撞检测
    for (int i = 0; i < ENEMY_NUM2; i++)
    {
        if (m_enemys[i].m_Free || !m_enemys[i].isAlive()) continue;

        for (int j = 0; j < BULLET_NUM; j++)
        {
            if (m_hero.m_bullets[j].m_Free) continue;

            if (m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
            {
                // 使用子弹的伤害值减少敌机血量
                m_enemys[i].reduceHealth(m_hero.m_bullets[j].getDamage());

                // 子弹消失
                m_hero.m_bullets[j].m_Free = true;

                // 如果敌机被击落
                if (!m_enemys[i].isAlive())
                {
                    // 播放爆炸效果
                    for (int k = 0; k < BOMB_NUM; k++)
                    {
                        if (m_bombs[k].m_Free)
                        {
                            m_bombs[k].m_Free = false;
                            m_bombs[k].m_X = m_enemys[i].m_X;
                            m_bombs[k].m_Y = m_enemys[i].m_Y;
                            break;
                        }
                    }
                }
            }
        }
    }

    // 敌机子弹与我方飞机碰撞检测
    for (int i = 0; i < ENEMY_NUM2; i++)
    {
        if (m_enemys[i].m_Free || !m_enemys[i].isAlive()) continue;

        for (int j = 0; j < ENEMY_BULLET_NUM; j++)
        {
            if (m_enemys[i].m_bullets[j].m_Free) continue;

            if (m_hero.m_Rect.intersects(m_enemys[i].m_bullets[j].m_Rect))
            {
                // 使用敌机子弹的伤害值减少我方飞机血量
                m_hero.reduceHealth(m_enemys[i].m_bullets[j].getDamage());

                // 子弹消失
                m_enemys[i].m_bullets[j].m_Free = true;

                // 播放小型爆炸效果
                for (int k = 0; k < BOMB_NUM; k++)
                {
                    if (m_bombs[k].m_Free)
                    {
                        m_bombs[k].m_Free = false;
                        m_bombs[k].m_X = m_enemys[i].m_X;
                        m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }
    }
    //遍历所以非空闲敌机
    for(int i = 0; i< ENEMY_NUM2; i++)
    {
        //如果是空闲的飞机，执行下一次循环
        if(m_enemys[i].m_Free)
        {
            continue;
        }

        //遍历所有非空闲的子弹
        for(int j = 0; j < BULLET_NUM; j++)
        {
            //空闲子弹执行下一次循环
            if(m_hero.m_bullets[j].m_Free)
            {
                continue;
            }

            //如果子弹和飞机相交，发生碰撞，同时将飞机和子弹空闲状态设置为真
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
            {
                m_enemys[i].m_Free = true;
                m_hero.m_bullets[j].m_Free = true;

                //播放爆炸的效果
                for(int k = 0; k < BOMB_NUM; k++)
                {
                    if(m_bombs[k].m_Free)
                    {
                        //空闲的爆炸，可以播放爆炸了
                        m_bombs[k].m_Free = false;
                        //更新爆炸坐标
                        m_bombs[k].m_X = m_enemys[i].m_X;
                        m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }

    }
}
