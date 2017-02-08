#include <qmessagebox.h>
#include "recordmodel.h"

RecordModel::RecordModel(QString &table)
	: TableModel(),
	table(table)
{


}

void RecordModel::init(QString &accn)
{
	m_hash.clear();

	if (m_nRows > 0)
		removeRows(0, m_nRows, QModelIndex());

	m_nRows = 0;

	acc = accn;
	sqlite3_stmt *st;
	QString script = QString("select * from %1 where account_name = \"%2\";").arg(table).arg(acc);

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

RecordModel::~RecordModel()
{

}


QVariant RecordModel::data(const QModelIndex &index, int role) const
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

bool RecordModel::setData(const QModelIndex& index,
	const QVariant&    value,
	int                nRole
)
{

	if (index.isValid() && acc != "")
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

				script = QString("insert into %1 (account_name, name) values(\"%2\", \"%3\");").arg(table).arg(table).arg(value.toString());

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


Qt::ItemFlags RecordModel::flags(const QModelIndex & /*index*/) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}


