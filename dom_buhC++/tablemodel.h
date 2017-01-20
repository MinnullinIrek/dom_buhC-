#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QTableView>
#include "CSqlite.h"

class TableModel : public QTableView
{
	Q_OBJECT

public:
	TableModel(QString& table, QWidget *parent);
	~TableModel();

private:
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	
	QString table;
	CSqlite *sql;
};

#endif // TABLEMODEL_H
