#include "Mainsence1.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include <QCoreApplication>
#include <QAudioOutput>

Mainsence::Mainsence(QWidget *parent)
    : QWidget(parent)
{
    //调用初始化窗口函数
    initSence();

    //启动
    playGame();
}

Mainsence::~Mainsence() {}

void Mainsence::initSence()
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
    m_hero.setBulletDamage(50);  // 我方普通子弹伤害为50

    // 初始化我方飞机生命值
    m_hero.setHealth(1000);

    // 初始化积分
    m_score = 0;

    //关卡数据初始化
    m_currentLevel = LEVEL_ONE;
    m_inTransition = false;
    m_transitionAlpha = 0;

    // 初始化第一关
    initLevel(LEVEL_ONE);

    // 初始化地图
    m_maps[0].m_map1.load(MAP_PATH1);
    m_maps[0].m_map2.load(MAP_PATH1);
    m_maps[1].m_map1.load(MAP_PATH2);
    m_maps[1].m_map2.load(MAP_PATH2);
    m_maps[2].m_map1.load(MAP_PATH3);
    m_maps[2].m_map2.load(MAP_PATH3);

    m_currentMapIndex = 0;
}

void Mainsence::playGame()
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

//---------------------------------------------------------------------

//初始化关卡

void Mainsence::initLevel(Level level)
{
    // 重置游戏状态
    m_hero.setHealth(100);
    m_score = 0;

    // 根据关卡设置敌机属性
    switch(level) {
    case LEVEL_ONE:
        m_currentMapIndex = 0;
        // 第一关敌机属性
        for (int i = 0; i < ENEMY_NUM1; i++) {
            m_enemys[i].setSpeed(5);
            m_enemys[i].setHealth(100);
        }
        break;

    case LEVEL_TWO:
        m_currentMapIndex = 1;
        // 第二关敌机属性增强
        for (int i = 0; i < ENEMY_NUM1; i++) {
            m_enemys[i].setSpeed(6);
            m_enemys[i].setHealth(150);
        }
        break;

    case LEVEL_THREE:
        m_currentMapIndex = 2;
        // 第三关敌机属性增强
        for (int i = 0; i < ENEMY_NUM1; i++) {
            m_enemys[i].setSpeed(7);
            m_enemys[i].setHealth(200);
        }
        break;
    default:
        break;
    }
}

//关卡转化以及数据变化
void Mainsence::checkLevelUp()
{
    if (m_inTransition) return;

    // 关卡升级检测
    if (m_currentLevel == LEVEL_ONE && m_score >= 5000) {
        startLevelTransition(LEVEL_TWO);
    } else if (m_currentLevel == LEVEL_TWO && m_score >= 10000) {
        startLevelTransition(LEVEL_THREE);
    } else if (m_currentLevel == LEVEL_THREE && m_score >= 15000) {
        m_currentLevel = LEVEL_COMPLETED;
        startLevelTransition(LEVEL_COMPLETED);
    }
}

void Mainsence::startLevelTransition(Level nextLevel)
{
    m_inTransition = true;
    m_transitionAlpha = 0;
    m_nextLevel = nextLevel;

    // 停止游戏计时器
    m_Timer.stop();

    // 启动转场计时器
    m_transitionTimer.start(20);
    connect(&m_transitionTimer, &QTimer::timeout, this, &Mainsence::updateTransition);
}

void Mainsence::updateTransition()
{
    m_transitionAlpha += 5;

    if (m_transitionAlpha >= 255) {
        // 转场完成
        m_transitionTimer.stop();

        if (m_nextLevel == LEVEL_COMPLETED) {
            // 游戏完成，返回开始界面
            emit gameOver();
        } else {
            // 进入下一关
            m_currentLevel = m_nextLevel;
            initLevel(m_currentLevel);
            m_transitionAlpha = 255;

            // 延迟后开始游戏
            QTimer::singleShot(1000, this, [this]() {
                m_Timer.start();
                m_transitionAlpha = 0;
                m_inTransition = false;
            });
        }
    }

    update(); // 重绘界面
}

//---------------------------------------------------------------------------------------------

void Mainsence::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();
    // 更新当前关卡的地图坐标
    m_maps[m_currentMapIndex].mapPosition();

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
    for(int i = 0; i < ENEMY_NUM1; i++)
    {
        if(m_enemys[i].m_Free == false)
        {
            m_enemys[i].updatePosition();
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

void Mainsence::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 绘制当前关卡的地图
    painter.drawPixmap(0, m_maps[m_currentMapIndex].m_map1_posY, m_maps[m_currentMapIndex].m_map1);
    painter.drawPixmap(0, m_maps[m_currentMapIndex].m_map2_posY, m_maps[m_currentMapIndex].m_map2);
    //绘制飞机
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);

    // 绘制我方飞机生命值
    painter.setPen(Qt::red);
    painter.drawText(10, 20, QString("HP: %1").arg(m_hero.getHealth()));

    // 绘制积分
    painter.setPen(Qt::yellow);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(GAME_WIDTH - 120, 20, QString("Score: %1").arg(m_score));

    //绘制敌机
    for(int i = 0; i < ENEMY_NUM1; i++)
    {
        if(m_enemys[i].m_Free == false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
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

    //----------------------------------------------------------------------------------------------------------
    //绘制我方子弹
    for(int i = 0; i < BULLET_NUM; i++)
    {
        //如果非空闲，绘制
        if(m_hero.m_bullets[i].m_Free == false)
        {
            painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet);
        }
    }

    //绘制关卡信息
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(10, 50, QString("Level: %1").arg(m_currentLevel + 1));

    //-------------------------------------------------------------------------------------------------------5.24

    // 绘制转场效果
    if (m_inTransition) {
        QBrush brush(QColor(0, 0, 0, m_transitionAlpha));
        painter.fillRect(0, 0, GAME_WIDTH, GAME_HEIGHT, brush);

        if (m_transitionAlpha >= 200) {
            painter.setPen(Qt::white);
            painter.setFont(QFont("Arial", 36, QFont::Bold));
            if (m_nextLevel == LEVEL_COMPLETED) {
                painter.drawText(GAME_WIDTH/2 - 150, GAME_HEIGHT/2, "游戏胜利!");
            } else {
                painter.drawText(GAME_WIDTH/2 - 100, GAME_HEIGHT/2, QString("第 %1 关").arg(m_nextLevel + 1));
            }
        }
    }

}


void Mainsence::mouseMoveEvent(QMouseEvent *event)
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

void Mainsence::enemyToScene()
{
    m_recorder++;
    //未达到出场间隔 直接return
    if(m_recorder < ENEMY_INTERVAL1)
    {
        return;
    }
    m_recorder = 0;

    for(int i = 0; i < ENEMY_NUM1; i++)
    {
        //如果是空闲敌机 出场
        if(m_enemys[i].m_Free)
        {
            m_enemys[i].m_Free = false;

            //坐标
            m_enemys[i].m_X = rand()%(GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = - m_enemys[i].m_Rect.height();
            m_enemys[i].setHealth(100); // 设置敌机初始生命值
            break;
        }
    }
}

void Mainsence::collisionDetection()
{
    // 检查关卡升级
    checkLevelUp();

    if (m_inTransition) return;

    // 我方子弹与敌机碰撞检测
    for (int i = 0; i < ENEMY_NUM1; i++)
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

                    // 增加积分 (击落敌机获得100分)
                    m_score += 100;

                    m_enemys[i].m_Free = true;
                }
            }
        }
    }

    // 我方飞机与敌机碰撞检测
    for (int i = 0; i < ENEMY_NUM1; i++)
    {
        if (m_enemys[i].m_Free || !m_enemys[i].isAlive()) continue;

        if (m_hero.m_Rect.intersects(m_enemys[i].m_Rect))
        {
            // 我方飞机和敌机相撞，两者都受损
            m_hero.reduceHealth(50);  // 我方飞机损失50点生命值
            m_enemys[i].reduceHealth(100);  // 敌机直接被摧毁

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

            // 增加积分 (与敌机相撞获得50分)
            m_score += 50;

            m_enemys[i].m_Free = true;

            // 检查我方飞机是否被击落
            if (m_hero.getHealth() <= 0) {
                // 游戏结束逻辑
                qDebug() << "Game Over! Final Score: " << m_score;
                m_Timer.stop(); // 停止游戏
                emit gameOver(); // 发射游戏结束信号
            }
        }
    }
}

