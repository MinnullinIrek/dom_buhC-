#include <qgridlayout.h>

#include "accview.h"

AccView::AccView(QWidget *parent)
	: QWidget(parent)
{
	acc = new AccTableModel();
	accView = new QTableView();
	accView->setModel(acc);
	QGridLayout *layout = new QGridLayout(this);

	layout->addWidget(accView, 1, 1);
}

AccView::~AccView()
{

}
