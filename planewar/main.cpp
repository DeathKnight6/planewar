#include <QApplication>
#include "Startwidget.h"
#include "Mainsence1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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

    return a.exec();
}
