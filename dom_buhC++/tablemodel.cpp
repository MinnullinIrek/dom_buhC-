#include <qcolor.h>
#include <qfont.h>
#include <qsize.h>

#include "tablemodel.h"


AccTableModel::AccTableModel(QString& script)
	: QAbstractTableModel(),
	m_nRows(0),
	script(script)
{
	
	sqlite3_open("lite", &db);
	sqlite3_stmt *st;

	if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
		throw(sqlite3_errmsg(db));

	//sqlite3_reset(st);
	//sqlite3_clear_bindings(st);
	 m_nColumns = sqlite3_column_count(st);



	while (SQLITE_ROW ==  sqlite3_step(st)) {
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
				throw( "unknown type");
			}

			QModelIndex index = this->index(m_nRows-1, col);
			m_hash[index] = var;

			
		}
	}	 
}

void AccTableModel::init()
{


}

AccTableModel::~AccTableModel()
{

}

int AccTableModel::rowCount(const QModelIndex &parent) const
{
	return this->m_nRows+1;
}

int AccTableModel::columnCount(const QModelIndex &parent) const
{
	return this->m_nColumns;
}

QVariant AccTableModel::data(const QModelIndex &index, int role) const
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

	//switch (role) {

	//case Qt::DisplayRole: // Данные для отображения
	//case Qt::EditRole:    // Данные для редактирования
		//return value;

	//case Qt::TextColorRole: // Цвет текста
	//	if (index.column() == 1)
	//		return qVariantFromValue(QColor(Qt::blue));
	//	else
	//		return value;

	//case Qt::TextAlignmentRole: // Выравнивание
	//	if (index.column() == 3)
	//		return int(Qt::AlignRight | Qt::AlignVCenter);
	//	else if (index.column() == 2 || index.column() == 4)
	//		return int(Qt::AlignHCenter | Qt::AlignVCenter);
	//	else
	//		return int(Qt::AlignLeft | Qt::AlignVCenter);


	//case Qt::FontRole: // Шрифт
	//	if (index.column() == 1) {
	//		QFont font = QFont("Helvetica", 10, QFont::Bold);
	//		return qVariantFromValue(font);
	//	}
	//	else
	//		return value;


	//case Qt::BackgroundColorRole: {  // Цвет фона
	//	int a = (index.row() % 2) ? 14 : 0;
	//	if (index.column() == 0)
	//		return qVariantFromValue(QColor(220, 240 - a, 230 - a));
	//	else if (index.column() == 4)
	//		return qVariantFromValue(QColor(200, 220 - a, 255 - a));
	//	else
	//		return value;
	//}

	//case Qt::CheckStateRole:  // Галочка
	//	if (index.column() == 4)
	//		return (value.toInt() != 0) ?
	//		Qt::Checked : Qt::Unchecked;
	//	else
	//		return value;

	//case Qt::SizeHintRole:  // Размер ячейки
	//	if (index.column() == 0)
	//		return QSize(70, 10);
	//	if (index.column() == 4)
	//		return QSize(60, 10);
	//	else
	//		return QSize(110, 10);

	//}
	return value;


}

bool AccTableModel::setData(const QModelIndex& index,
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
			
			if (index.column() == 1 )
				script = "Update accounts set name = ? where id = ?;";
			else if (index.column() == 2)
				script = "Update accounts set comment = ? where id = ?;";

			if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
				throw(sqlite3_errmsg(db));

			char d[256]; sprintf(d, "%s", value.toString().toUtf8().data());

			if (SQLITE_OK != sqlite3_bind_text(st, 1, d, strlen(d), SQLITE_STATIC))
				throw(sqlite3_errmsg(sqlite3_db_handle(st)));

			if (SQLITE_OK != sqlite3_bind_int(st, 2, index.row() + 1))
				throw(sqlite3_errmsg(sqlite3_db_handle(st)));


		}
		else{

			

			if (index.column() == 1)
				script = "insert into accounts (id, name) values(?, ?);";
			else if (index.column() == 2)
				script = "insert into accounts (id, comment) values(?, ?);";
			
			
			if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
				throw(sqlite3_errmsg(db));

			if (SQLITE_OK != sqlite3_bind_int(st, 1, index.row() + 1))
				throw(sqlite3_errmsg(sqlite3_db_handle(st)));

			char d[256]; sprintf(d, "%s", value.toString().toUtf8().data());

			if (SQLITE_OK != sqlite3_bind_text(st, 2, d, strlen(d), SQLITE_STATIC))
				throw(sqlite3_errmsg(sqlite3_db_handle(st)));

			m_nRows++;
			insertRow(m_nRows + 1, QModelIndex());

		}

		if (sqlite3_step(st) != SQLITE_DONE)
			throw(sqlite3_errmsg(sqlite3_db_handle(st)));

		emit dataChanged(index, index);
		return true;
	}



	return false;
}

bool AccTableModel::insertRow(int row, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row);
	endInsertRows();
	return true;
}


Qt::ItemFlags AccTableModel::flags(const QModelIndex & /*index*/) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void AccTableModel::doubleClicked(const QModelIndex &index)
{
	emit selected(m_hash[index]);
}