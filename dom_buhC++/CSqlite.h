#pragma once
#include <QString>
#include "sqlite3.h"
class CSqlite
{
public:
	CSqlite();
	void dostring(QString &s);
	int rowCount(const QString &table);
	~CSqlite();
	sqlite3 *db = NULL;
public:
	int field_num;
	char **fields;
	char **field_names;
};

