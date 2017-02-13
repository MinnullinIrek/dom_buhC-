#include "mainmenu.h"
#include "recordmodel.h"
#include <qgridlayout.h>

MainMenu::MainMenu(QWidget *parent)
	: QWidget(parent)
{
	acc = new AccView();	
	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(acc, 1, 1);

	debet_types = new CTDTable(QString("debet"));
	
	layout->addWidget(debet_types, 2, 1);

	credit_types = new CTDTable(QString("credit"));
	layout->addWidget(credit_types, 2, 2);


	QTableView *v = new QTableView();
	RecordModel *r = new RecordModel(QString("debet"));
	v->setModel(r);

	layout->addWidget(v, 1, 2);

}

MainMenu::~MainMenu()
{

}
