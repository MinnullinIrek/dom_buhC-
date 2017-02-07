#include <qtableview.h>
#include <qgridlayout.h>
#include <qitemselectionmodel.h>

#include "ctdtable.h"
#include "debet_type.h"
#include "debetcategory.hpp"


CTDTable::CTDTable(QString &table, QWidget *parent)
	: QWidget(parent)
{
	model = new Debet_type(QString("%1_type").arg(table), 1);
	
	w = new QTableView();
	w->setModel(model);
	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(w, 1, 2);
	
	cat_model = new DebetCategory(QString("%1_category").arg(table));
	cat_w = new QTableView();
	cat_w->setModel(cat_model);
	layout->addWidget(cat_w, 1, 1);

	
	connect(cat_w->selectionModel(), &QItemSelectionModel::selectionChanged, this, &CTDTable::selectionChangedSlot);

}

void CTDTable::selectionChangedSlot(const QItemSelection & selected, const QItemSelection & deselected)
{
	const QItemSelection *o = &selected;
}

CTDTable::~CTDTable()
{

}
