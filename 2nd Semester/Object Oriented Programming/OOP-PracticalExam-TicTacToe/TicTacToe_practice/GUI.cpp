#pragma once
#include "GUI.h"

void GUI::initializeGUI() {
	mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	leftSide = new QWidget;
	leftLayout = new QFormLayout;
	leftSide->setLayout(leftLayout);

	leftLayout->addRow(lblId, editId);
	leftLayout->addRow(lblDim, editDim);
	leftLayout->addRow(lblTable, editTable);
	leftLayout->addRow(lblNext, editNext);
	leftLayout->addRow(lblState, editState);

	btnAdd = new QPushButton("Adauga joc");
	btnUpdate = new QPushButton("Modifica joc");

	leftLayout->addWidget(btnAdd);
	leftLayout->addWidget(btnUpdate);

	tableSide = new QWidget;
	QVBoxLayout* tableLayout = new QVBoxLayout;
	tableSide->setLayout(tableLayout);

	leftLayout->addWidget(tableSide);

	mainLayout->addWidget(leftSide);

	rightSide = new QWidget;
	rightLayout = new QVBoxLayout;
	rightSide->setLayout(rightLayout);

	tblGames = new QTableView();
	modelGames = new TableViewModel{ gameServ };
	tblGames->setModel(modelGames);
	tblGames->setSelectionMode(QAbstractItemView::SingleSelection);
	tblGames->setSelectionBehavior(QAbstractItemView::SelectRows);
	tblGames->setSizeAdjustPolicy(QAbstractItemView::AdjustToContents);
	tblGames->setFixedSize(500, 500);

	rightLayout->addWidget(tblGames);
	mainLayout->addWidget(rightSide);

	this->setWindowTitle("TicTacToe");
}

void GUI::connectSignalsSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, [&]() {
		int id = editId->text().toInt();
		int dim = editDim->text().toInt();
		string table = editTable->text().toStdString();
		string next = editNext->text().toStdString();
		string state = "Neinceput";

		try {
			gameServ.addGame(id, dim, table, next, state);
			reloadGames();
		}
		catch (ValidationException& ve) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
		}
		catch (RepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
		}
	});

	QObject::connect(btnUpdate, &QPushButton::clicked, this, [&]() {
		int id = editId->text().toInt();
		int dim = editDim->text().toInt();
		string table = editTable->text().toStdString();
		string next = editNext->text().toStdString();
		string state = editState->text().toStdString();

		try {
			gameServ.updateGame(id, dim, table, next, state);
			reloadGames();
		}
		catch (ValidationException& ve) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
		}
		catch (RepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
		}

	});

	QObject::connect(tblGames->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
		if (!tblGames->selectionModel()->selectedIndexes().isEmpty()) {
			reloadCurrentTable();
		}
	});


}

void GUI::reloadGames() {
	modelGames->reloadGames();
}

void GUI::reloadCurrentTable() {
	if (!tblGames->selectionModel()->selectedIndexes().isEmpty()) {
		int selectedRow = tblGames->selectionModel()->selectedIndexes().at(0).row();
		auto idIndex = tblGames->model()->index(selectedRow, 0);


		int selectedId = tblGames->model()->data(idIndex, Qt::DisplayRole).toInt();
		qDebug() << selectedId;
		auto selectedGame = gameServ.findGame(selectedId);


		QVBoxLayout* tableLayout = new QVBoxLayout;
		qDeleteAll(tableSide->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));
		delete tableSide->layout();
		tableSide->setLayout(tableLayout);

		int dim = selectedGame.getDim();
		vector<QPushButton*> btnsGame(dim*dim);

		int currentChr = 0;
		for (int i = 0; i < dim; i++) {
			QHBoxLayout* btnLayout = new QHBoxLayout;
			tableLayout->addLayout(btnLayout);

			for (int j = 0; j < dim; j++) {
				btnsGame[currentChr] = new QPushButton(QString::fromStdString(string(1,selectedGame.getTable().at(currentChr))));

				QObject::connect(btnsGame[currentChr], &QPushButton::clicked, this, [=]() {
					auto selected = gameServ.findGame(selectedId);
					if (btnsGame[currentChr]->text().toStdString() == "-" && selected.getState() != "Terminat") {
						auto newChr = selected.getNextPlayer();
						auto table = selected.getTable();
						table.at(currentChr) = newChr.at(0);
						btnsGame[currentChr]->setText(QString::fromStdString(newChr));

						string next;
						if (newChr == "X")
							next = "O";
						else if (newChr == "O")
							next = "X";

						auto newState = selected.getState();
						if (newState == "Neinceput")
							newState = "In derulare";
						if (gameServ.checkGameState(selected.getDim(), table, 'X') == true || gameServ.checkGameState(selected.getDim(), table, 'O') == true)
							newState = "Terminat";
						gameServ.updateGame(selected.getId(), selected.getDim(), table, next, newState);
						reloadGames();
					}
				});



				btnLayout->addWidget(btnsGame[currentChr]);
				currentChr++;
			}
		}

		/*for (int i = 0; i < dim*dim; i++) {
			QObject::connect(btnsGame[i], &QPushButton::clicked, this, [=]() {
				if (btnsGame[i]->text().toStdString() == "-" && selectedGame.getState() != "Terminat") {
					auto newChr = selectedGame.getNextPlayer();
					auto table = selectedGame.getTable();
					table.at(i) = newChr.at(0);
					btnsGame[i]->setText(QString::fromStdString(newChr));

					string next;
					if (newChr == "X")
						next = "O";
					else if(newChr == "O")
						next = "X";

					auto newState = selectedGame.getState();
					if (newState == "Neinceput")
							newState = "In derulare";
					if (gameServ.checkGameState(selectedGame,'X') == true || gameServ.checkGameState(selectedGame,'O') == true)
							newState = "Terminat";
					gameServ.updateGame(selectedGame.getId(), selectedGame.getDim(), table, next, newState);
					reloadGames();
				}
			});
		}*/

		leftLayout->addWidget(tableSide);

	}


}