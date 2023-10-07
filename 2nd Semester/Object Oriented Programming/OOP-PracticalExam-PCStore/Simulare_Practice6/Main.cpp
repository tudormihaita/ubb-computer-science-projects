#include "Simulare_Practice6.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
#include "PCStoreGUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");

    Tests tests;
    tests.runAllTests();

    Repository repoPC{ "cpu.txt", "mobo.txt" };
    Service servPC{ repoPC };
    PCStoreGUI guiPC{ servPC };

    /*Simulare_Practice6 w;
    w.show();*/

    guiPC.show();
    return app.exec();
}
