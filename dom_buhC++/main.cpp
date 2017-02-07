
#include <QtWidgets/QApplication>
#include <qtableview.h>

#include "CSqlite.h"

#include "sqlite3.h"
#include "tablemodel.h"
#include "debetcategory.hpp"
#include "debet_type.h"
#include "CTDTable.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//MyClass w;

	QString s = "select* from accounts;";
	//AccTableModel model(s);
	//Debet_type model(QString("debet_type"), 1);

	//QTableView* w = new QTableView();
	//w->setModel(&model);
	//QObject::connect(w, &QTableView::doubleClicked, &model, &AccTableModel::doubleClicked);

	//w->show();
	QString str = "lite";
	CTDTable *t = new CTDTable(QString("debet"), nullptr);
	t->show();
	
	return a.exec();
}
