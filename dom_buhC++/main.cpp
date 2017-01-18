#include "myclass.h"
#include <QtWidgets/QApplication>
#include "CSqlite.h"
#include "sqlite3.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyClass w;
	w.show();
	QString str = "lite";
	sqlite3 *db = NULL;
	sqlite3_open(str.toUtf8().data(), &db);
	return a.exec();
}
