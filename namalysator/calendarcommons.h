#include <QtWidgets>
#include "structgui.h"
#include <map>
#include "dbrequest.h"

void initCalendarWidget(QCalendarWidget *widget,const BatchDetail &batch);
void loadYear(QTableWidget *table, const BatchDetail &batch);
void formatCalendar(QCalendarWidget *cal);