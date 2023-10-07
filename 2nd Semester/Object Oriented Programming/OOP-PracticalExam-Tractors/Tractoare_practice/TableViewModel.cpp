#pragma once
#include "TableViewModel.h"

int TableViewModel::rowCount(const QModelIndex&) const {
	return serv.getSize();
}

int TableViewModel::columnCount(const QModelIndex&) const {
	return 5;
}

QVariant TableViewModel::data(const QModelIndex& parent, int role) const {
	auto row = parent.row();
	auto column = parent.column();

	if (role == Qt::DisplayRole) {
		auto tractor = serv.sortTractors().at(row);
		if (column == 0) {
			return QString::number(tractor.getId());
		}
		else if (column == 1) {
			return QString::fromStdString(tractor.getModel());
		}
		else if (column == 2) {
			return QString::fromStdString(tractor.getType());
		}
		else if (column == 3) {
			return QString::number(tractor.getNrWheels());
		}
		else if (column == 4) {
			return QString::number(serv.filterByType(tractor.getType()).size());
		}
	}
	else if (role == Qt::BackgroundRole) {
		auto tractor = serv.sortTractors().at(row);
		if (tractor.getType() == selectedType) {
			return QBrush{ Qt::red };
		}
	}

	return QVariant{};
}

QVariant TableViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0) {
				return tr("ID");
			}
			else if (section == 1) {
				return tr("Denumire");
			}
			else if (section == 2) {
				return tr("Tip");
			}
			else if (section == 3) {
				return tr("Numar roti");
			}
			else if (section == 4) {
				return tr("Nr acelasi tip");
			}
			else {
				return QString("");
			}
		}
	}

	return QVariant{};
}

void TableViewModel::reloadTractors() {
	emit layoutChanged();
}

void TableViewModel::reloadSelectedType(string newType) {
	selectedType = newType;
	emit layoutChanged();
}