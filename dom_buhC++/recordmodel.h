#ifndef RECORDMODEL_H
#define RECORDMODEL_H

#include <QObject>
#include "tablemodel.h"


class RecordModel : public TableModel
{
	Q_OBJECT

public:
	RecordModel(QString &table);
	~RecordModel();

	void init(QString &acc);
private:
	QString table;
	QString acc;

	bool setData(const QModelIndex& index, const QVariant& value, int nRole);
	Qt::ItemFlags flags(const QModelIndex & /*index*/) const;
	QVariant data(const QModelIndex &index, int role) const;

};

#endif // RECORDMODEL_H
