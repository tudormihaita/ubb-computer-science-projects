#pragma once
#include "Service.h"
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QBrush>

class TableViewModel : public QAbstractTableModel {
private:
	Service& serv;
	string selectedType;
public:
	TableViewModel(Service& srv) : serv{ srv } {};

	int rowCount(const QModelIndex&) const override;

	int columnCount(const QModelIndex&) const override;

	QVariant data(const QModelIndex&, int role) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	Qt::ItemFlags flags(const QModelIndex&) const override {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}

	void reloadTractors();

	void reloadSelectedType(string newType);
};