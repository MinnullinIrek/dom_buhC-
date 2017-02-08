
#include <QtWidgets/QApplication>
#include <qtableview.h>

#include "CSqlite.h"

#include "sqlite3.h"
#include "tablemodel.h"
#include "debetcategory.hpp"
#include "debet_type.h"
#include "CTDTable.h"
#include "mainmenu.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//MyClass w;

	//QString s = "select* from accounts;";
	//AccTableModel model(s);
	////Debet_type model(QString("debet_type"), 1);

	//QTableView* w = new QTableView();
	//w->setModel(&model);
	////QObject::connect(w, &QTableView::doubleClicked, &model, &AccTableModel::doubleClicked);

	//w->show();
	//QString str = "lite";
	//CTDTable *t_debet = new CTDTable(QString("debet"), nullptr);
	//t_debet->show();
	//
	//CTDTable *t_credit = new CTDTable(QString("credit"), nullptr);
	//t_credit->show();

	MainMenu m;
	m.show();

	return a.exec();
}
