#include "TicTacToe_practice.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");

    Tests tests;
    tests.runAllTests();

    Repository gameRepo{ "games.txt" };
    Validator gameValidator;
    Service gameServ{ gameRepo, gameValidator };
    GUI guiGame{ gameServ };

   /* TicTacToe_practice w;
    w.show();*/

    guiGame.show();
    return app.exec();
}
