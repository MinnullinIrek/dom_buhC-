#pragma once
#ifndef DEBETCATEGORY_HPP
#define DEBETCATEGORY_HPP
#include "TableModel.h"

class DebetCategory : public TableModel {
	Q_OBJECT

public:
	DebetCategory(QString & parent);
	~DebetCategory();

private:
	bool setData(const QModelIndex& index, const QVariant& value, int nRole);
	Qt::ItemFlags flags(const QModelIndex & /*index*/) const;
	QVariant data(const QModelIndex &index, int role) const;
	QString table;
};

#endif // DEBETCATEGORY_HPP