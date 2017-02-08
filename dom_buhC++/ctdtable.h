#ifndef CTDTABLE_H
#define CTDTABLE_H

#include <QWidget>
#include <qitemselectionmodel.h>
class Debet_type;
class QTableView;
class DebetCategory;

class CTDTable : public QWidget
{
	Q_OBJECT

public:
	CTDTable(QString &table, QWidget *parent);
	~CTDTable();
public slots:
	void selectionChangedSlot(const QItemSelection & selected, const QItemSelection & deselected);
	void dataChangeChangedSlot(const QModelIndex & topL, const QModelIndex & topR, const QVector<int>& roles = QVector<int>());
private:
	QString table;
	Debet_type *model;
	QTableView* w;
	QTableView* cat_w;
	DebetCategory *cat_model;


};

#endif // CTDTABLE_H
