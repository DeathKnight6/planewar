#ifndef CONFIG_H
#define CONFIG_H

//游戏配置数据
#define GAME_WIDTH   441          //宽度
#define GAME_HEIGHT  662          //高度
#define GAME_TITLE "飞机大战 v1.0" //标题
#define GAME_RES_PATH "./rec.qrc" //设置路径
#define GAME_ICON ":/beijing/baozha.png"//图标设置
#define GAME_RATE 10              //定时器刷新间隔

//地图配置数据
#define  MAP_PATH1 ":/beijing/beijing02.jpg" //地图配置
#define  MAP_SCROLL_SPEED 2 //地图滚动速度

//飞机配置
#define HERO_PATH ":/beijing/tubiao01.2.0.png" //飞机照片

//子弹配置
#define BULLET_PATH ":/beijing/zidan.png"//子弹图片
#define BULLET_SPEED 5 //子弹移动速度
#define BULLET_NUM 30 //弹匣中子弹总数
#define BULLET_TNTERVAL 30 //发射子弹时间间隔

//敌机子弹配置
#define ENEMYBullet_PATH ":/beijing/zidan.png"//子弹图片
#define ENEMYBullet_BULLET_SPEED 4 //子弹移动速度
#define ENEMY_BULLET_NUM 10 //弹匣中子弹总数
#define ENEMY_SHOOT_INTERVAL 60 //发射子弹时间间隔

//敌机配置
//第一关
#define ENEMY_PATH ":/beijing/xiaobing02.png"//敌机资源图片
#define ENEMY_SPEED 3 //敌机移动速度
#define ENEMY_NUM1 20 //敌机总数量
#define ENEMY_INTERVAL1 100 //敌机出场时间间隔
//第二关
#define ENEMY_PATH ":/beijing/xiaobing02.png"//敌机资源图片
#define ENEMY_SPEED 3 //敌机移动速度
#define ENEMY_NUM2 50 //敌机总数量
#define ENEMY_INTERVAL2 70 //敌机出场时间间隔

//爆炸配置
#define BOMB_PATH ":/beijing/bomb1.10.png"//爆炸资源图片
#define BOMB_NUM 20 //爆炸数量
#define BOMB_MAX 4 //爆炸图片最大索引
#define BOMB_INTERVAL 20 //爆炸切图时间间隔

//音效设置
#define SOUND_BACKGROUND ":/beijing/bgm001.wav"
#define SOUND_BOMB ":/beijing/baozhayinxiao01.wav"

#endif // CONFIG_H
