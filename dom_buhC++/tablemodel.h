#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "CSqlite.h"

class TableModel : public QAbstractTableModel
{
	Q_OBJECT

protected:
	int                          m_nRows;
	int                          m_nColumns;
	QHash<QModelIndex, QVariant> m_hash;
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	sqlite3 *db;
	bool insertRow(int row, const QModelIndex & parent);
public:
	TableModel();
	~TableModel();
signals:
	void selected(QVariant var);

private:

};



class AccTableModel : public TableModel
{
	Q_OBJECT

public:
	AccTableModel(QString& script);
	~AccTableModel();
public slots:
	void doubleClicked(const QModelIndex &index);
protected:
	virtual void init();


	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex& index, const QVariant& value, int nRole);
	Qt::ItemFlags flags(const QModelIndex & /*index*/) const;
	QString script;

	
};

#endif // TABLEMODEL_H
