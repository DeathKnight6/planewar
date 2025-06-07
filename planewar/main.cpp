#include "Mainsence1.h"
#include "config.h"
#include <QResource>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //注册资源使用文件
    QResource::registerResource(GAME_RES_PATH);
    Mainsence w;
    w.show();
    return a.exec();
}
