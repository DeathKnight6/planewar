#ifndef MAINSENCE1_H
#define MAINSENCE1_H

#include "Map1.h"
#include <QWidget>
#include <QTimer>
#include "Heroplane.h"
#include <QMouseEvent>
#include "bullet.h"
#include "Enemyplane.h"
#include "Bomb.h"
#include <QList>



class Mainsence : public QWidget
{
    Q_OBJECT

public:
    enum Level {
        LEVEL_ONE,
        LEVEL_TWO,
        LEVEL_THREE,
        LEVEL_COMPLETED
    };                 //关卡升级设计

public:
    Mainsence(QWidget *parent = nullptr);
    ~Mainsence();

    //初始化场景
    void initSence();

    //启动游戏
    void playGame();

    //更新所有元素坐标
    void updatePosition();

    //绘制到屏幕中 函数名称不可改
    void paintEvent(QPaintEvent *);

    //重新鼠标移动事件
    void mouseMoveEvent(QMouseEvent *);

    //地图对象
    Map1 m_map;

    //飞机对象
    HeroPlane m_hero;

    //定时器
    QTimer m_Timer;

    //爆炸数组
    Bomb m_bombs[BOMB_NUM];

    //敌机出场
    void enemyToScene();

    //碰撞检测
    void collisionDetection();

    //敌机数组
    EnemyPlane m_enemys[ENEMY_NUM1];

    //敌机出场间隔记录
    int m_recorder;

    //初始化关卡
    void initLevel(Level level);

signals:
    void gameOver();  // 添加游戏结束信号

private:

    //创建积分列表
    int m_score;

    Level m_currentLevel;     // 当前关卡
    QTimer m_transitionTimer; // 转场计时器
    int m_transitionAlpha;    // 转场透明度
    bool m_inTransition;      // 是否在转场中
    Level m_nextLevel;        // 下一关

    // 地图对象数组，每个关卡对应不同的背景
    Map1 m_maps[3];  // 三个关卡对应三个地图
    int m_currentMapIndex;  // 当前使用的地图索引


private slots:
    void checkLevelUp();// 声明关卡转化函数1
    void startLevelTransition(Level nextLevel);//声明关卡转化函数2
    void updateTransition();//声明关卡转变完成函数
};
#endif // MAINSENCE1_H
