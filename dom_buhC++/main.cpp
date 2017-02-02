#include "myclass.h"
#include <QtWidgets/QApplication>
#include <qtableview.h>

#include "CSqlite.h"

#include "sqlite3.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//MyClass w;

	QString s = "select* from accounts;";
	AccTableModel model(s);

	QTableView* w = new QTableView();
	w->setModel(&model);
	QObject::connect(w, &QTableView::doubleClicked, &model, &AccTableModel::doubleClicked);

	w->show();
	QString str = "lite";
	
	return a.exec();
}
