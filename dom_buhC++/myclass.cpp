#include "myclass.h"

MyClass::MyClass(QWidget *parent)
	: QMainWindow(parent)
{
	QTableView* w = new QTableView(this);
	//ui.setupUi(this);
}

MyClass::~MyClass()
{

}
