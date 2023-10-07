#include "Service.h"
#include <QAbstractTableModel>
#include <QModelIndex>

class TableViewModel : public QAbstractTableModel {
private:
	Service& gameServ;
public:
	TableViewModel(Service& srv) : gameServ{ srv } {};

	int rowCount(const QModelIndex&) const override;

	int columnCount(const QModelIndex&) const override;

	QVariant data(const QModelIndex&, int role) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	Qt::ItemFlags flags(const QModelIndex&) const override {
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}

	void reloadGames();
};