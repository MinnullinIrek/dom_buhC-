#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "CSqlite.h"

class TableModel : public QAbstractTableModel
{
	Q_OBJECT
private:
	int                          m_nRows;
	int                          m_nColumns;
	QHash<QModelIndex, QVariant> m_hash;
public:
	TableModel(QString& script, int rows);
	~TableModel();

private:
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex& index, const QVariant&    value, int                nRole);
	Qt::ItemFlags flags(const QModelIndex & /*index*/) const;
	QString script;
	CSqlite *sql;
};

#endif // TABLEMODEL_H
