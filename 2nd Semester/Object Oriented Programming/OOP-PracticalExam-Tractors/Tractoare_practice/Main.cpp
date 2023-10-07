#include "Tractoare_practice.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");

    Tests tests;
    tests.runAllTests();

    Repository tractorRepo{ "tractors.txt" };
    Validator tractorValidator;
    Service tractorService{ tractorRepo, tractorValidator };
    GUI guiTractors{ tractorService };

   /* Tractoare_practice w;
    w.show();*/

    guiTractors.show();
    return app.exec();
}
