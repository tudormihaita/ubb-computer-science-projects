#include "TableViewModel.h"

int TableViewModel::rowCount(const QModelIndex&) const {
	return gameServ.getSize();
}

int TableViewModel::columnCount(const QModelIndex&) const {
	return 5;
}

QVariant TableViewModel::data(const QModelIndex& parent, int role) const {
	auto row = parent.row();
	auto column = parent.column();

	if (role == Qt::DisplayRole) {
		auto game = gameServ.getAllGames().at(row);

		if (column == 0) {
			return QString::number(game.getId());
		}
		else if (column == 1) {
			return QString::number(game.getDim());
		}
		else if (column == 2) {
			return QString::fromStdString(game.getTable());
		}
		else if (column == 3) {
			return QString::fromStdString(game.getNextPlayer());
		}
		else if (column == 4) {
			return QString::fromStdString(game.getState());
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
				return tr("Dimensiune");
			}
			else if (section == 2) {
				return tr("Tabela de joc");
			}
			else if (section == 3) {
				return tr("Urmatorul jucator");
			}
			else if (section == 4) {
				return tr("Stare joc");
			}
			else {
				return QString("");
			}
		}
	}

	return QVariant{};
}

void TableViewModel::reloadGames() {
	emit layoutChanged();
}