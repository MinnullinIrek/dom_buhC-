#include "debet_type.h"
#include <qmessagebox.h>
Debet_type::Debet_type(QString &main_table, QString & c_name)
	: TableModel(1),
	table(main_table)
{

	//QString category = "debet_category";
	//if (table == "debet_type")
	//	category = "credit_ctegory";
	init(c_name);
	
}

void Debet_type::init(QString &c_id)
{
	headerNames[0] = "debet type";
	m_hash.clear();

	if (m_nRows > 0)
		removeRows(0, m_nRows, QModelIndex());

	m_nRows = 0;
	category_name = c_id;
	

	QString script = QString("select name from %1 where category_name = \"%2\"; ").arg(table).arg(category_name);
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
			insertRow(m_nRows + 1, QModelIndex());

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
		oldValue.setValue(m_hash[index]);
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

	if (index.isValid() && category_name != "")
	{
		m_hash[index] = value;
		sqlite3_stmt *st;
		QString script;

		if (index.row() < m_nRows) {

			
			script = QString("Update %1 set name = \"%2\" where name = \"%3\";").arg(table).arg(value.toString()).arg(oldValue.toString());
			//else if (index.column() == 2)
			//script = "Update debet_category set comment = ? where id = ?;";

			if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
				throw(sqlite3_errmsg(db));
		}
		else {
			try
			{
				
				script = QString("insert into %1 (category_name, name) values(\"%2\", \"%3\");").arg(table).arg(category_name).arg(value.toString());

				if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
					throw(sqlite3_errmsg(db));

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

