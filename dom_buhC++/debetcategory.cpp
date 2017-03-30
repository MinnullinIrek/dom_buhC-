#include "debetcategory.hpp"

DebetCategory::DebetCategory(QString& main_table) : TableModel(1), table(main_table) {
	headerNames[0] = "debet category";
	QString script = QString("select * from %1").arg(table);
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

DebetCategory::~DebetCategory() {
	
}


QVariant DebetCategory::data(const QModelIndex &index, int role) const
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

bool DebetCategory::setData(const QModelIndex& index,
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
			QVariant v =this->data(index, Qt::DisplayRole);

			script = QString("Update %1 set name = \"%2\" where name = \"%3\";").arg(table).arg(value.toString()).arg(oldValue.toString());
			//else if (index.column() == 2)
				//script = "Update debet_category set comment = ? where id = ?;";

			if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
				throw(sqlite3_errmsg(db));

			if (sqlite3_step(st) != SQLITE_DONE)
				throw(sqlite3_errmsg(sqlite3_db_handle(st)));

			QString type_tbl = QString(table).remove(QRegExp("_category$"));

			script = QString("Update %1_type set category_name = \"%2\" where category_name = \"%3\";").arg(type_tbl).arg(value.toString()).arg(oldValue.toString());

			if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
				throw(sqlite3_errmsg(db));

		}
		else {

			script = QString("insert into %1 (name) values(?);").arg(table);
			//else if (index.column() == 2)
				//script = "insert into accounts (id, comment) values(?, ?);";


			if (SQLITE_OK != sqlite3_prepare_v2(db, script.toUtf8().data(), script.length(), &st, NULL))
				throw(sqlite3_errmsg(db));

			//if (SQLITE_OK != sqlite3_bind_int(st, 1, index.row() + 1))
			//	throw(sqlite3_errmsg(sqlite3_db_handle(st)));

			char d[256]; sprintf(d, "%s", value.toString().toUtf8().data());

			if (SQLITE_OK != sqlite3_bind_text(st, 1, d, strlen(d), SQLITE_STATIC))
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

//bool DebetCategory::insertRow(int row, const QModelIndex & parent)
//{
//	beginInsertRows(parent, row, row);
//	endInsertRows();
//	return true;
//}


Qt::ItemFlags DebetCategory::flags(const QModelIndex & /*index*/) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

