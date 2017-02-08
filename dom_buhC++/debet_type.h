#ifndef DEBET_TYPE_H
#define DEBET_TYPE_H

#include "tablemodel.h"

class Debet_type : public TableModel
{
	Q_OBJECT

public:
	Debet_type(QString &main_table, QString & c_name);
	~Debet_type();
	void init(QString &c_name);
private:
	 
	QString table;
	QString category_name;
	bool setData(const QModelIndex& index, const QVariant& value, int nRole);
	Qt::ItemFlags flags(const QModelIndex & /*index*/) const;
	QVariant data(const QModelIndex &index, int role) const;
	mutable QVariant oldValue;
};

#endif // DEBET_TYPE_H
