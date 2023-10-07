#pragma once
#include "Service.h"
#include "TableViewModel.h"
#include <QWidget>
#include <QFormLayout>
#include <QLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

/*class WheelsGUI : public QWidget {
private:
	Service& tractorServ;
	int nrWheels = 0;
	int id = 0;

	int radius = 10;
	int left = this->width() - 150;
	int right = left;
	int center = this->height() - 100;

	QVBoxLayout* wheelsLayout;

	void initializeGUI() {
		wheelsLayout = new QVBoxLayout;
		this->setLayout(wheelsLayout);
		this->setFixedSize(200, 200);
	}

	void paintEvent(QPaintEvent*) override {
		QPainter painter{ this };
		if (id != 0 && nrWheels != 0) {
			radius = 10;
			left = this->width() - 150;
			right = left;
			center = this->height() - 100;

			for (int i = 1; i <= nrWheels; i++) {
				painter.drawEllipse(QPointF(right, center), radius, radius);
				right += 2 * radius;
			}
		}
	}

	void mousePressEvent(QMouseEvent* e) override {
		if (e->pos().y() >= center - radius && e->pos().y() <= center + radius && e->pos().x() >= left && e->pos().x() <= right) {
			try {
				tractorServ.updateTractor(id, nrWheels - 2);
			}
			catch (ValidationException& ve) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
			}
		}
	}

public:
	WheelsGUI(Service& srv) : tractorServ{ srv } {
		initializeGUI();
		reloadSelectedTractor(id, nrWheels);
	}

	void reloadSelectedTractor(int newId, int newNrWheels) {
		id = newId;
		nrWheels = newNrWheels;
		this->repaint();
	}
};*/


class GUI : public QWidget {
private:
	Service& tractorServ;

	QLabel* lblId = new QLabel("Id tractor: ");
	QLabel* lblModel = new QLabel("Denumire tractor: ");
	QLabel* lblType = new QLabel("Tip tractor: ");
	QLabel* lblWheels = new QLabel("Numar roti tractor: ");

	QLineEdit* editId = new QLineEdit;
	QLineEdit* editModel = new QLineEdit;
	QLineEdit* editType = new QLineEdit;
	QLineEdit* editWheels = new QLineEdit;

	QPushButton* btnAdd;

	QComboBox* cbxTypes;

	QTableView* tblTractors;
	TableViewModel* modelTractors;

	QWidget* drawWheels = new QWidget;
	QGraphicsView* view;
	QGraphicsScene* scene;


	int radius = 10;
	int left = this->width() - 500;
	int right = left;
	int center = this->height() - 100;

	void initializeGUI();
	void connectSignalsSlots();
	void reloadTractorList();
	void reloadTractorTypes();


	void paintEvent(QPaintEvent*) override {
		radius = 10;
		left = this->width() - 500;
		right = left;
		center = this->height() - 100;

		delete drawWheels->layout();

		if (!tblTractors->selectionModel()->selectedIndexes().isEmpty()) {
			auto selectedRow = tblTractors->selectionModel()->selectedIndexes().at(0).row();
			auto cellIndex1 = tblTractors->model()->index(selectedRow, 3);

			int nrWheels = tblTractors->model()->data(cellIndex1, Qt::DisplayRole).toInt();

			view = new QGraphicsView;
			scene = new QGraphicsScene;
			view->setScene(scene);
			view->setFixedSize(400, 300);

			for (int i = 1; i <= nrWheels; i++) {
				qreal x = right;
				qreal y = center;
				qreal r = radius * 2;
				QGraphicsEllipseItem* wheel = new QGraphicsEllipseItem{ x, y, r, r };
				wheel->setBrush(QBrush(Qt::white));
				scene->addItem(wheel);
				right += 2 * radius;
			}

			QLayout* wheelLayout = new QVBoxLayout;
			drawWheels->setLayout(wheelLayout);
			wheelLayout->addWidget(view);

			/*for (int i = 1; i <= nrWheels; i++) {
				painter.drawEllipse(QPointF(right, center), radius, radius);
				right += 2 * radius;
			}*/
		}
	}

	void mousePressEvent(QMouseEvent*) override {
		if (!tblTractors->selectionModel()->selectedIndexes().isEmpty()) {
			auto selectedRow = tblTractors->selectionModel()->selectedIndexes().at(0).row();
			auto cellIndex1 = tblTractors->model()->index(selectedRow, 3);
			auto cellIndex2 = tblTractors->model()->index(selectedRow, 0);

			int id = tblTractors->model()->data(cellIndex2, Qt::DisplayRole).toInt();
			int nrWheels = tblTractors->model()->data(cellIndex1, Qt::DisplayRole).toInt();

			foreach(QGraphicsItem * wheel, scene->items()) {
				if (wheel->isUnderMouse()) {
					try {
						tractorServ.updateTractor(id, nrWheels - 2);
						reloadTractorList();
						this->repaint();
					}
					catch (ValidationException& ve) {
						QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
					}
				}
			}
		}


		/*	if (e->pos().y() >= center - radius && e->pos().y() <= center + radius && e->pos().x() >= left && e->pos().x() <= right) {
				if (!tblTractors->selectionModel()->selectedIndexes().isEmpty()) {
					auto selectedRow = tblTractors->selectionModel()->selectedIndexes().at(0).row();
					auto cellIndex1 = tblTractors->model()->index(selectedRow, 3);
					auto cellIndex2 = tblTractors->model()->index(selectedRow, 0);

					int id = tblTractors->model()->data(cellIndex2, Qt::DisplayRole).toInt();
					int nrWheels = tblTractors->model()->data(cellIndex1, Qt::DisplayRole).toInt();

					try {
						tractorServ.updateTractor(id, nrWheels - 2);
						reloadTractorList();
						this->repaint();
					}
					catch (ValidationException& ve) {
						QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMsg()));
					}
				}
			}*/
	}

public:
	GUI(Service& srv) : tractorServ{ srv } {
		initializeGUI();
		connectSignalsSlots();
		reloadTractorList();
		reloadTractorTypes();
		this->repaint();
	}

	~GUI() = default;
};