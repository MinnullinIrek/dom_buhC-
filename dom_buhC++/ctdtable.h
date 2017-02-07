#ifndef CTDTABLE_H
#define CTDTABLE_H

#include <QWidget>
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
private:
	QString table;
	Debet_type *model;
	QTableView* w;
	QTableView* cat_w;
	DebetCategory *cat_model;


};

#endif // CTDTABLE_H
