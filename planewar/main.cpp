<<<<<<< HEAD
=======
#include "Mainsence1.h"
<<<<<<< HEAD
#include "Mainsence2.h"
#include "BOSSMainsence.h"
=======
>>>>>>> a8bb9635c82d0e3b992904b4a550a601c4f9fa07
#include "config.h"
#include <QResource>
>>>>>>> a3360dcda2f7081c1d5798175957bfbb12eb66ce
#include <QApplication>
#include "Startwidget.h"
#include "Mainsence1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD

    // 创建开始界面和游戏界面
    Startwidget Startwidget;
    Mainsence gameWidget;

    // 连接信号和槽
    QObject::connect(&Startwidget, &Startwidget::startGame, [&]() {
        Startwidget.hide();       // 隐藏开始界面
        gameWidget.show();        // 显示游戏界面
        gameWidget.playGame();    // 开始游戏
    });

    QObject::connect(&Startwidget, &Startwidget::exitGame, [&]() {
        Startwidget.close();      // 关闭开始界面，退出游戏
    });

    QObject::connect(&gameWidget, &Mainsence::gameOver, [&]() {
        gameWidget.hide();        // 隐藏游戏界面
        Startwidget.show();       // 显示开始界面
    });

    // 显示开始界面
    Startwidget.show();

=======
    //注册资源使用文件
    QResource::registerResource(GAME_RES_PATH);
<<<<<<< HEAD
    //Mainsence1 f;
    //f.show();
    Mainsence2 s;
    s.show();
    //BOSSMainsence t;
    //t.show();
=======
    Mainsence w;
    w.show();
>>>>>>> a8bb9635c82d0e3b992904b4a550a601c4f9fa07
>>>>>>> a3360dcda2f7081c1d5798175957bfbb12eb66ce
    return a.exec();
}
