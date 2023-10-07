#pragma once
#include "Service.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QGroupBox>
#include <QHeaderView>
#include <QBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

class ApartmentsGUI : public QWidget {
private:
	Service& apartmentService;

	QGroupBox* commandsBox = new QGroupBox(tr("Comenzi"));
	QGroupBox* filterSurfaceBox = new QGroupBox(tr("Filtrare dupa suprafata"));
	QGroupBox* filterPriceBox = new QGroupBox(tr("Filtrare dupa pret"));

	QGroupBox* viewBox = new QGroupBox(tr("Vizualizare apartamente"));


	QPushButton* btnRemoveApartment;

	QLabel* lblMinSurface = new QLabel{ "Suprafata minima:" };
	QLabel* lblMaxSurface = new QLabel{ "Suprafata maxima:" };

	QLabel* lblMinPrice = new QLabel{ "Pret minim:" };
	QLabel* lblMaxPrice = new QLabel{ "Pret maxim:" };

	QLineEdit* editMinSurface;
	QLineEdit* editMaxSurface;
	QLineEdit* editMinPrice;
	QLineEdit* editMaxPrice;

	QPushButton* btnFilterBySurface;
	QPushButton* btnFilterByPrice;

	QPushButton* btnReloadList;

	QListWidget* lstApartments;

	void initializeGUI();

	void connectSignalsSlots();

	void reloadApartmentList(vector<Apartment> apartments);

public:
	ApartmentsGUI(Service& srv) : apartmentService{ srv } {
		initializeGUI();
		connectSignalsSlots();
		reloadApartmentList(apartmentService.getAllApartments());
	}

	~ApartmentsGUI() = default;
};

