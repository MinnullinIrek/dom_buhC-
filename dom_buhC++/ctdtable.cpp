#include <qtableview.h>
#include <qgridlayout.h>


#include "ctdtable.h"
#include "debet_type.h"
#include "debetcategory.hpp"


CTDTable::CTDTable(QString &table, QWidget *parent)
	: QWidget(parent)
{
	
	QGridLayout *layout = new QGridLayout(this);

	cat_model = new DebetCategory(QString("%1_category").arg(table));
	cat_w = new QTableView();
	cat_w->setModel(cat_model);
	layout->addWidget(cat_w, 1, 1);

	model = new Debet_type(QString("%1_type").arg(table), QString(""));
	
	w = new QTableView();
	w->setModel(model);
	
	layout->addWidget(w, 1, 2);
	
	connect(cat_w->selectionModel(), &QItemSelectionModel::selectionChanged, this, &CTDTable::selectionChangedSlot);
	connect(cat_model, &DebetCategory::dataChanged, this, &CTDTable::dataChangeChangedSlot);
}

void CTDTable::selectionChangedSlot(const QItemSelection & selected, const QItemSelection & deselected)
{
	const QItemSelection *o = &selected;
	QModelIndexList i = selected.indexes();
	QModelIndex index = i.at(0);

	QVariant data = cat_model->data(index, Qt::DisplayRole);
	model->init(data.toString());
	
}

void CTDTable::dataChangeChangedSlot(const QModelIndex & topL, const QModelIndex & topR, const QVector<int>& roles)
{
	QVariant data = cat_model->data(topL, Qt::DisplayRole);
	model->init(data.toString());

}

CTDTable::~CTDTable()
{

}
