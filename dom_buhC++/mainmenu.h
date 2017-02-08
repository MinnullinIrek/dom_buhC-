#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <qtableview.h>
#include "accview.h"
#include "ctdtable.h"

class MainMenu : public QWidget
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = nullptr);
	~MainMenu();

private:
	AccView *acc;
	CTDTable *debet_types;
	CTDTable *credit_types;

};

#endif // MAINMENU_H
