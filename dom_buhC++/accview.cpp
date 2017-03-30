#include <qgridlayout.h>
#include <qheaderview.h>
#include "accview.h"

AccView::AccView(QWidget *parent)
	: QWidget(parent)
{
	acc = new AccTableModel();
	acc->setHeaderData(0, Qt::Horizontal, "qqqq");
	acc->setHeaderData(1, Qt::Horizontal, "qqqq1");
	accView = new QTableView();
	QHeaderView *header = new QHeaderView(Qt::Orientation::Horizontal);
	
	
	
	//accView->setHorizontalHeader(header);
	accView->setModel(acc);
	QGridLayout *layout = new QGridLayout(this);

	layout->addWidget(accView, 1, 1);
	
}

AccView::~AccView()
{

}
