#include "Simulare_Practice1.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
#include "ApartmentsGUI.h"

int main(int argc, char *argv[])
{

    Tests tests;
    tests.runAllTests();

    QApplication app(argc, argv);
    Repository apartmentRepository{ "apartments.txt" };
    Service apartmentService{ apartmentRepository };
    ApartmentsGUI guiApartments{ apartmentService };

   // Simulare_Practice1 w;
    //w.show();

    //app.setStyle("fusion");

    //guiApartments.show();
    //return app.exec();
}
