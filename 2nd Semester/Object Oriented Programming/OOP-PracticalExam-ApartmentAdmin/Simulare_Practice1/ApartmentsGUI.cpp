#pragma once
#include "ApartmentsGUI.h"

void ApartmentsGUI::initializeGUI() {
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	QWidget* rightSide = new QWidget;
	QVBoxLayout* rightLayout = new QVBoxLayout;
	rightSide->setLayout(rightLayout);

	QLayout* commandsLayout = new QVBoxLayout;
	commandsBox->setLayout(commandsLayout);

	btnRemoveApartment = new QPushButton("&Sterge apartament");

	commandsLayout->addWidget(btnRemoveApartment);

	QFormLayout* filterSurfaceLayout = new QFormLayout;
	filterSurfaceBox->setLayout(filterSurfaceLayout);

	editMinSurface = new QLineEdit;
	editMaxSurface = new QLineEdit;

	filterSurfaceLayout->addRow(lblMinSurface, editMinSurface);
	filterSurfaceLayout->addRow(lblMaxSurface, editMaxSurface);

	btnFilterBySurface = new QPushButton("Filtreaza dupa suprafata");

	filterSurfaceLayout->addWidget(btnFilterBySurface);

	commandsLayout->addWidget(filterSurfaceBox);

	QFormLayout* filterPriceLayout = new QFormLayout;
	filterPriceBox->setLayout(filterPriceLayout);

	editMinPrice = new QLineEdit;
	editMaxPrice = new QLineEdit;

	filterPriceLayout->addRow(lblMinPrice, editMinPrice);
	filterPriceLayout->addRow(lblMaxPrice, editMaxPrice);

	btnFilterByPrice = new QPushButton("Filtreaza dupa pret");

	filterPriceLayout->addWidget(btnFilterByPrice);

	commandsLayout->addWidget(filterPriceBox);

	btnReloadList = new QPushButton("Refresh lista");

	commandsLayout->addWidget(btnReloadList);

	rightLayout->addWidget(commandsBox);

	QWidget* leftSide = new QWidget;
	QVBoxLayout* leftLayout = new QVBoxLayout;
	leftSide->setLayout(leftLayout);

	QVBoxLayout* viewLayout = new QVBoxLayout;
	viewBox->setLayout(viewLayout);

	lstApartments = new QListWidget;
	lstApartments->setSizeAdjustPolicy(QAbstractItemView::AdjustToContents);
	lstApartments->setSelectionMode(QAbstractItemView::SingleSelection);
	lstApartments->setSelectionBehavior(QAbstractItemView::SelectRows);

	viewLayout->addWidget(lstApartments);

	leftLayout->addWidget(viewBox);

	mainLayout->addWidget(leftSide);
	mainLayout->addWidget(rightSide);

	this->setWindowTitle("Cautare apartamente");
}

void ApartmentsGUI::reloadApartmentList(vector<Apartment> apartments) {
	lstApartments->clear();

	int lineNumber = 0;
	for (auto& ap : apartments) {
		lstApartments->insertItem(lineNumber, QString::fromStdString(ap.getStreet() + " (" + to_string(ap.getSurface()) + "m^2) " +
			to_string(ap.getPrice()) + "euro"));

		QListWidgetItem* currentAp = lstApartments->item(lineNumber);
		currentAp->setData(Qt::UserRole, ap.getId());
	
		lineNumber++;
	}

	lstApartments->setSizeAdjustPolicy(QAbstractItemView::AdjustToContents);
}

void ApartmentsGUI::connectSignalsSlots() {
	//sterge
	QObject::connect(btnRemoveApartment, &QPushButton::clicked, this, [&]() {
		auto selected = lstApartments->selectedItems();

		if (!selected.isEmpty()) {

			auto selectedApartment = selected.at(0);
			int id = selectedApartment->data(Qt::UserRole).toInt();
			this->apartmentService.removeApartment(id);

			QMessageBox::information(this, "Info", QString::fromStdString("Apartament sters cu succes!"));
			reloadApartmentList(apartmentService.getAllApartments());
		}
		else {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Selectati un apartament pentru a putea efectua stergerea!"));
		}
	});

	//filtrari
	QObject::connect(btnFilterBySurface, &QPushButton::clicked, this, [&]() {
		if (!editMinSurface->text().isEmpty() && !editMaxSurface->text().isEmpty()) {
			int minSurface = editMinSurface->text().toInt();
			int maxSurface = editMaxSurface->text().toInt();

			reloadApartmentList(apartmentService.filterBySurface(minSurface, maxSurface));
		}
		else {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Introduceti valori valide pentu suprafata minima si maxima!"));
		}
	});

	QObject::connect(btnFilterByPrice, &QPushButton::clicked, this, [&]() {
		if (!editMinPrice->text().isEmpty() && !editMaxPrice->text().isEmpty()) {
			double minPrice = editMinPrice->text().toDouble();
			double maxPrice = editMaxPrice->text().toDouble();

			reloadApartmentList(apartmentService.filterByPrice(minPrice, maxPrice));

			QMessageBox::information(this, "Info", QString::fromStdString("Filtrare dupa pret efectuata cu succes!"));

			if (!editMinSurface->text().isEmpty() && !editMaxSurface->text().isEmpty()) {
				QMessageBox::information(this, "Info", QString::fromStdString("Se efectueaza filtrare dupa suprafata..."));

				int minSurface = editMinSurface->text().toInt();
				int maxSurface = editMaxSurface->text().toInt();
				reloadApartmentList(apartmentService.filterBySurface(minSurface, maxSurface));
			}

		}
		else {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Introduceti valori valide pentu suprafata minima si maxima!"));
		}

	});

	QObject::connect(btnReloadList, &QPushButton::clicked, this, [&]() {
		reloadApartmentList(apartmentService.getAllApartments());
	});
}