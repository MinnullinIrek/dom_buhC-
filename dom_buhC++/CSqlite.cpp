#include "CSqlite.h"
#include "sqlite3.h"
#include "qhash.h"


int data_callback(void *csqlite, int field_num, char **fields, char **field_names)
{
	for (int i = 0; i < field_num; i++)
	{
		printf("%s = %s, ", field_names[i], fields[i]);
	}

	((CSqlite*)csqlite)->field_num		= field_num;
	((CSqlite*)csqlite)->fields			= fields;
	((CSqlite*)csqlite)->field_names	= field_names;

	printf("\n");
	return 0;
}

CSqlite::CSqlite()
{
	sqlite3_open("lite", &db);
}


CSqlite::~CSqlite()
{
	sqlite3_close(db);
}

void CSqlite::dostring(QString &s)
{

}

int CSqlite::rows(QString &sql)
{
	sqlite3_stmt *st = NULL;
		

	if (SQLITE_OK != sqlite3_prepare_v2(db, sql.toUtf8().data(), sql.length(), &st, NULL))
		throw(sqlite3_errmsg(db));
	return 0;

}



int CSqlite::rowCount(const QString &table)
{
	char* err;
	sqlite3_exec(db, QString("count(SELECT id FROM %1;)").arg(table).toUtf8().data(), data_callback, this, &err);
	QString count = fields[0];
	return count.toInt();
}