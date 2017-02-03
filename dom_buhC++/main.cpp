
#include <QtWidgets/QApplication>
#include <qtableview.h>

#include "CSqlite.h"

#include "sqlite3.h"
#include "tablemodel.h"
#include "debetcategory.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//MyClass w;

	QString s = "select* from accounts;";
	//AccTableModel model(s);
	DebetCategory model(QString("debet_category"));

	QTableView* w = new QTableView();
	w->setModel(&model);
	//QObject::connect(w, &QTableView::doubleClicked, &model, &AccTableModel::doubleClicked);

	w->show();
	QString str = "lite";
	
	return a.exec();
}
