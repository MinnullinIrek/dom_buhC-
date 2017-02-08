#ifndef ACCVIEW_H
#define ACCVIEW_H

#include <QObject>
#include <qtableview.h>
#include "tablemodel.h"
class AccView : public QWidget
{
	Q_OBJECT

public:
	AccView(QWidget *parent = nullptr);
	~AccView();

private:
	AccTableModel *acc;
	QTableView *accView;
};

#endif // ACCVIEW_H
