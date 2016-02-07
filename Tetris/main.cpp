#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game *game = new Game(800, 600);
    game->show();

    return a.exec();
}
