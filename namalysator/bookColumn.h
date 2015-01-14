#ifndef _BOOKCOLUMN_H_
#define _BOOKCOLUMN_H_

 #include <QHeaderView>

//* in case of cutomisation of behaviour of header 
//

class bookColumn: public QHeaderView {
public:
	bookColumn(Qt::Orientation orientation,QWidget * parent = 0);
	virtual ~bookColumn();


};

#endif