#include "TableViewModel.h"
#include "Service.h"
#include <QTableView>
#include <QWidget>
#include <QLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

using std::to_string;

class GUI : public QWidget {
private:
	Service& gameServ;

	QHBoxLayout* mainLayout;

	QWidget* leftSide;
	QFormLayout* leftLayout;
	QWidget* rightSide;
	QVBoxLayout* rightLayout;


	QLabel* lblId = new QLabel("Id joc: ");
	QLabel* lblDim = new QLabel("Dimensiune joc: ");
	QLabel* lblTable = new QLabel("Tabela joc: ");
	QLabel* lblNext = new QLabel("Urmatorul jucator: ");
	QLabel* lblState = new QLabel("Stare joc: ");

	QLineEdit* editId = new QLineEdit;
	QLineEdit* editDim = new QLineEdit;
	QLineEdit* editTable = new QLineEdit;
	QLineEdit* editNext = new QLineEdit;
	QLineEdit* editState = new QLineEdit;

	QPushButton* btnAdd;
	QPushButton* btnUpdate;

	QTableView* tblGames;
	TableViewModel* modelGames;

	QWidget* tableSide;

	void initializeGUI();
	void connectSignalsSlots();
	void reloadGames();
	void reloadCurrentTable();

public:
	GUI(Service& srv) : gameServ{ srv } {
		initializeGUI();
		connectSignalsSlots();
		reloadGames();
	}
};