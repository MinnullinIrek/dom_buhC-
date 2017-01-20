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
	
	return a.exec();
}
