#include "Mainsence1.h"
#include "Mainsence2.h"
#include "BOSSMainsence.h"
#include "config.h"
#include <QResource>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //注册资源使用文件
    QResource::registerResource(GAME_RES_PATH);
    //Mainsence1 f;
    //f.show();
    Mainsence2 s;
    s.show();
    //BOSSMainsence t;
    //t.show();
    return a.exec();
}
