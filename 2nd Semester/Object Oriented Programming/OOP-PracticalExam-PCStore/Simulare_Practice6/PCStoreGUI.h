#pragma once
#include "Service.h"
#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QLayout>
#include <QFormLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>

using std::to_string;

class PCStoreGUI : public QWidget {
private:
	Service& servPC;

	QListWidget* lstCPU;
	QListWidget* lstMOBO;

	QLabel* lblName = new QLabel(QString::fromStdString("Nume placa de baza:"));
	QLabel* lblSocket = new QLabel(QString::fromStdString("Soclu procesor:"));
	QLabel* lblPrice = new QLabel(QString::fromStdString("Pret placa de baza:"));

	QLineEdit* editName;
	QLineEdit* editSocket;
	QLineEdit* editPrice;

	QPushButton* btnAddMOBO;

	void initializeGUI();
	void connectSignalsSlots();
	void reloadCPU(vector<CPU> CPUs);
	void reloadMOBO(vector<MOBO> MOBOs);

public:
	PCStoreGUI(Service& srv) : servPC{ srv } {
		initializeGUI();
		connectSignalsSlots();
		reloadCPU(servPC.getAllCPUs());
		reloadMOBO(servPC.getAllMOBOs());
	}

	~PCStoreGUI() = default;
};
