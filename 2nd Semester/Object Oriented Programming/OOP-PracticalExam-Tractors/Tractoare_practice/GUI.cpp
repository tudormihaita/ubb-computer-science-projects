#pragma once
#include "GUI.h"

void GUI::initializeGUI() {
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	QWidget* leftSide = new QWidget;
	QFormLayout* leftLayout = new QFormLayout;
	leftSide->setLayout(leftLayout);

	leftLayout->addRow(lblId, editId);
	leftLayout->addRow(lblModel, editModel);
	leftLayout->addRow(lblType, editType);
	leftLayout->addRow(lblWheels, editWheels);

	btnAdd = new QPushButton("Adauga tractor");

	leftLayout->addWidget(btnAdd);

	cbxTypes = new QComboBox;

	leftLayout->addWidget(cbxTypes);
	mainLayout->addWidget(leftSide);

	QWidget* rightSide = new QWidget;
	QVBoxLayout* rightLayout = new QVBoxLayout;
	rightSide->setLayout(rightLayout);

	tblTractors = new QTableView();
	modelTractors = new TableViewModel{ tractorServ };
	tblTractors->setModel(modelTractors);
	tblTractors->setSelectionBehavior(QAbstractItemView::SelectRows);
	tblTractors->setSelectionMode(QAbstractItemView::SingleSelection);
	tblTractors->setSizeAdjustPolicy(QAbstractItemView::AdjustToContents);

	drawWheels->setFixedSize(400, 300);

	rightLayout->addWidget(tblTractors);
	rightLayout->addWidget(drawWheels);
	mainLayout->addWidget(rightSide);

	this->setWindowTitle("Tractoare");
}

void GUI::connectSignalsSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, [&]() {
		if (!editId->text().isEmpty() && !editWheels->text().isEmpty()) {
			int id = editId->text().toInt();
			string model = editModel->text().toStdString();
			string type = editType->text().toStdString();
			int nrWheels = editWheels->text().toInt();

			try {
				tractorServ.addTractor(id, model, type, nrWheels);
				reloadTractorList();
				reloadTractorTypes();
			}
			catch (ValidationException& ve) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
			}
			catch (RepoException& re) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
			}
		}
		else {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Introduceti date pentru adaugare!"));
		}
		});

	QObject::connect(cbxTypes, &QComboBox::currentIndexChanged, this, [&]() {
		string selectedType = cbxTypes->currentText().toStdString();
		qDebug() << selectedType;
		modelTractors->reloadSelectedType(selectedType);
		});

	QObject::connect(tblTractors->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
		if (!tblTractors->selectionModel()->selectedIndexes().isEmpty()) {
			this->repaint();
		}
		});
}

void GUI::reloadTractorList() {
	modelTractors->reloadTractors();
}

void GUI::reloadTractorTypes() {
	auto newTypes = tractorServ.groupByType();

	cbxTypes->clear();
	cbxTypes->setPlaceholderText("Tip tractor selectat");
	for (auto& type : newTypes) {
		cbxTypes->addItem(QString::fromStdString(type.first));
	}
}
