#ifndef MAINSENCE2_H
#define MAINSENCE2_H

#include "Map2.h"
#include <QWidget>
#include <QTimer>
#include "Heroplane.h"
#include <QMouseEvent>
#include "bullet.h"
#include "Enemyplane.h"
#include "Bomb.h"


class Mainsence2 : public QWidget
{
    Q_OBJECT

public:
    Mainsence2(QWidget *parent = nullptr);
    ~Mainsence2();

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
    Map2 m_map;

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
    EnemyPlane m_enemys[ENEMY_NUM2];

    //敌机出场间隔记录
    int m_recorder;


};
#endif // MAINSENCE2_H
