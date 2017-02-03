#pragma once
#include <qwidget.h>
class MyDCedet:QWidget
{
	Q_OBJECT
public:
	MyDCedet(QString mainTable, QWidget * parent);
	~MyDCedet();
	QString table;
};

