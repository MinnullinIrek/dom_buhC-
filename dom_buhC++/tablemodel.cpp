#include "tablemodel.h"

TableModel::TableModel(QString& table, QWidget *parent)
	: QTableView(parent),
	sql(new CSqlite),
	table(table)
{
	 
}

TableModel::~TableModel()
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{


	return sql->rowCount(table); 
}
int TableModel::columnCount(const QModelIndex &parent) const
{
	return 5;
}


QVariant TableModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole) {
		QString unswer = QString("row = ") + QString::number(index.row()) + "  col = " + QString::number(index.column());
		// строкой выше мы формируем ответ. QString::number преобразует число в текст
		return QVariant(unswer);
	}
	return QVariant();
}
