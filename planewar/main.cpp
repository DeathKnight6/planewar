#include "Mainsence1.h"
<<<<<<< HEAD
#include "Mainsence2.h"
#include "BOSSMainsence.h"
=======
>>>>>>> a8bb9635c82d0e3b992904b4a550a601c4f9fa07
#include "config.h"
#include <QResource>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
    return a.exec();
}
