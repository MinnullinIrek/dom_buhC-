#ifndef DEBET_TYPE_H
#define DEBET_TYPE_H

#include "tablemodel.h"

class Debet_type : public TableModel
{
	Q_OBJECT

public:
	Debet_type(QString main_table, int cat_id);
	~Debet_type();

private:
	int caegory_id;
	QString table;
};

#endif // DEBET_TYPE_H
