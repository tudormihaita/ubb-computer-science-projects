#include "PCStoreGUI.h"

void PCStoreGUI::initializeGUI() {
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	QWidget* viewCPU = new QWidget;
	QVBoxLayout* viewCPULayout = new QVBoxLayout;
	viewCPU->setLayout(viewCPULayout);

	lstCPU = new QListWidget;
	lstCPU->setSelectionMode(QAbstractItemView::SingleSelection);
	lstCPU->setSelectionBehavior(QAbstractItemView::SelectRows);
	lstCPU->setSizeAdjustPolicy(QAbstractItemView::AdjustToContents);

	viewCPULayout->addWidget(lstCPU);

	mainLayout->addWidget(viewCPU);

	QWidget* viewMOBO = new QWidget;
	QVBoxLayout* viewMOBOLayout = new QVBoxLayout;
	viewMOBO->setLayout(viewMOBOLayout);

	lstMOBO = new QListWidget;
	lstMOBO->setSelectionMode(QAbstractItemView::SingleSelection);
	lstMOBO->setSelectionBehavior(QAbstractItemView::SelectRows);
	lstMOBO->setSizeAdjustPolicy(QAbstractItemView::AdjustToContents);

	viewMOBOLayout->addWidget(lstMOBO);

	mainLayout->addWidget(viewMOBO);

	QWidget* commands = new QWidget;
	QFormLayout* commandsLayout = new QFormLayout;
	commands->setLayout(commandsLayout);

	editName = new QLineEdit;
	editSocket = new QLineEdit;
	editPrice = new QLineEdit;

	btnAddMOBO = new QPushButton("Adauga placa de baza");

	commandsLayout->addRow(lblName, editName);
	commandsLayout->addRow(lblSocket, editSocket);
	commandsLayout->addRow(lblPrice, editPrice);
	commandsLayout->addWidget(btnAddMOBO);

	mainLayout->addWidget(commands);
}

void PCStoreGUI::reloadCPU(vector<CPU> CPUs) {
	lstCPU->clear();

	int lineNumber = 0;
	for (auto& cpu : CPUs) {
		lstCPU->insertItem(lineNumber, QString::fromStdString(cpu.getName() + " - " + to_string(cpu.getThreads())));

		auto currentCPU = lstCPU->item(lineNumber);
		currentCPU->setData(Qt::UserRole, cpu.getID());

		lineNumber++;
	}

	lstCPU->setSizeAdjustPolicy(QAbstractItemView::AdjustToContents);
}

void PCStoreGUI::reloadMOBO(vector<MOBO> MOBOs) {
	lstMOBO->clear();

	int lineNumber = 0;
	for (auto& mobo : MOBOs) {
		lstMOBO->insertItem(lineNumber, QString::fromStdString(mobo.getName()));

		auto currentMOBO = lstMOBO->item(lineNumber);
		currentMOBO->setData(Qt::UserRole, mobo.getId());

		lineNumber++;
	}

	lstMOBO->setSizeAdjustPolicy(QAbstractItemView::AdjustToContents);
}

void PCStoreGUI::connectSignalsSlots() {
	QObject::connect(btnAddMOBO, &QPushButton::clicked, this, [&]() {
		if (!editName->text().isEmpty() && !editPrice->text().isEmpty() && !editSocket->text().isEmpty()) {
			string name = editName->text().toStdString();
			string socket = editSocket->text().toStdString();
			double price = editPrice->text().toDouble();

			try {
				servPC.addMOBO(name, socket, price);
				reloadMOBO(servPC.getAllMOBOs());
			}
			catch (RepoException& re) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
			}
		}
		else {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Introduceti date pentru adaugarea unei placi de baza!"));
		}

	});

	QObject::connect(lstCPU, &QListWidget::itemSelectionChanged, this, [&]() {
		auto selected = lstCPU->selectedItems();

		if (!selected.isEmpty()) {
			auto cpu = selected.at(0);
			int id = cpu->data(Qt::UserRole).toInt();

			string socket = servPC.findCPU(id).getSocket();

			reloadMOBO(servPC.filterBySocket(socket));
		}
		else {
			reloadMOBO(servPC.getAllMOBOs());
		}
	});

	QObject::connect(lstMOBO, &QListWidget::itemSelectionChanged, this, [&]() {
		auto selectedMOBO = lstMOBO->selectedItems();
		auto selectedCPU = lstCPU->selectedItems();

		if (!selectedMOBO.isEmpty() && !selectedCPU.isEmpty()) {
			auto cpu = selectedCPU.at(0);
			auto mobo = selectedMOBO.at(0);

			int cpuID = cpu->data(Qt::UserRole).toInt();
			int moboID = mobo->data(Qt::UserRole).toInt();

			double priceCPU = servPC.findCPU(cpuID).getPrice();
			double priceMOBO = servPC.findMOBO(moboID).getPrice();

			double price = priceCPU + priceMOBO;

			QMessageBox::information(this, "Info", QString::fromStdString("Pretul total: " + to_string(price)));
		}


	});

}