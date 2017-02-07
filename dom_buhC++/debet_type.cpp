#include "debet_type.h"
#include <qmessagebox.h>
Debet_type::Debet_type(QString main_table, int cat_id)
	: TableModel(),
	table(main_table),
	cat_id(cat_id)
{

	//QString category = "debet_category";
	//if (table == "debet_type")
	//	category = "credit_ctegory";

	QString script = QString("select * from %1 where category_id = %3 ").arg(table).arg(cat_id);
	sqlite3_stmt *st;

	if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
		throw(sqlite3_errmsg(db));

	m_nColumns = sqlite3_column_count(st);



	while (SQLITE_ROW == sqlite3_step(st)) {
		m_nRows++;

		for (int col = 0; col < m_nColumns; col++) {
			QVariant var;

			int type = sqlite3_column_type(st, col);
			switch (type) {
			case SQLITE_NULL: {

				//var.setValue(nullptr);
				break;
			}
			case SQLITE_INTEGER: {
				var.setValue((int)sqlite3_column_int64(st, col));
				break;
			}
			case SQLITE_FLOAT: {
				var.setValue((double)sqlite3_column_double(st, col));
				break;
			}
			case SQLITE3_TEXT: {
				var.setValue(QString((const char*)sqlite3_column_text(st, col)));
				break;
			}
			case SQLITE_BLOB: {
				throw("SQLITE_BLOB");
				break;
			}
			default:
				throw("unknown type");
			}

			QModelIndex index = this->index(m_nRows - 1, col);
			m_hash[index] = var;


		}
	}

}

Debet_type::~Debet_type()
{

}


QVariant Debet_type::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	QVariant value;
	value.setValue(m_hash[index]);

	switch (role) {
	case Qt::DisplayRole:

		return value;
		break;
	case Qt::EditRole:

		return value;
		break;
	}
	return QVariant();

	return value;
}

bool Debet_type::setData(const QModelIndex& index,
	const QVariant&    value,
	int                nRole
)
{
	if (index.isValid())
	{
		m_hash[index] = value;
		sqlite3_stmt *st;
		QString script;

		if (index.row() < m_nRows) {

			if (index.column() == 1)
				script = QString("Update %1 set name = ? where id = ?;").arg(table);
			//else if (index.column() == 2)
			//script = "Update debet_category set comment = ? where id = ?;";

			if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
				throw(sqlite3_errmsg(db));

			char d[256]; sprintf(d, "%s", value.toString().toUtf8().data());

			if (SQLITE_OK != sqlite3_bind_text(st, 1, d, strlen(d), SQLITE_STATIC))
				throw(sqlite3_errmsg(sqlite3_db_handle(st)));


			if (SQLITE_OK != sqlite3_bind_int(st, 2, index.row() + 1))
				throw(sqlite3_errmsg(sqlite3_db_handle(st)));


		}
		else {
			try
			{
				if (index.column() == 2)
					script = QString("insert into %1 (category_id, name) values(%2, ?);").arg(table).arg(cat_id);
				//else if (index.column() == 2)
				//script = "insert into accounts (id, comment) values(?, ?);";


				if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
					throw(sqlite3_errmsg(db));

				//if (SQLITE_OK != sqlite3_bind_int(st, 1, index.row() + 1))
				//	throw(sqlite3_errmsg(sqlite3_db_handle(st)));

				char d[256];
				sprintf(d, "%s", value.toString().toUtf8().data());

				if (SQLITE_OK != sqlite3_bind_text(st, 1, d, strlen(d), SQLITE_STATIC))
					throw(sqlite3_errmsg(sqlite3_db_handle(st)));

				m_nRows++;
				insertRow(m_nRows + 1, QModelIndex());
			}
			catch (const std::exception&)
			{

			}
			catch (QString &str)
			{
				QMessageBox msg;
				msg.setText(str);
				msg.show();
			}
		}

		if (sqlite3_step(st) != SQLITE_DONE)
			throw(sqlite3_errmsg(sqlite3_db_handle(st)));

		emit dataChanged(index, index);
		return true;
	}



	return false;
}


Qt::ItemFlags Debet_type::flags(const QModelIndex & /*index*/) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

