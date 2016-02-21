#include <QApplication>
#include "gameApp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameApp *game = new GameApp(367, 582);
    game->show();

    return a.exec();
}
