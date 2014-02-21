/****************************************************************************
** Meta object code from reading C++ file 'w_calendar.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../w_calendar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_calendar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_w_calendar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      34,   29,   11,   11, 0x08,
      64,   11,   11,   11, 0x08,
      83,   11,   11,   11, 0x08,
     100,   11,   11,   11, 0x08,
     118,   11,   11,   11, 0x08,
     127,   11,   11,   11, 0x08,
     138,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_w_calendar[] = {
    "w_calendar\0\0clickDate(QDate)\0item\0"
    "clickIdMets(QListWidgetItem*)\0"
    "clickYear(QString)\0validerComment()\0"
    "addComment(QDate)\0cancel()\0viewMets()\0"
    "showMissingIssue()\0"
};

void w_calendar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        w_calendar *_t = static_cast<w_calendar *>(_o);
        switch (_id) {
        case 0: _t->clickDate((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 1: _t->clickIdMets((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->clickYear((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->validerComment(); break;
        case 4: _t->addComment((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 5: _t->cancel(); break;
        case 6: _t->viewMets(); break;
        case 7: _t->showMissingIssue(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData w_calendar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject w_calendar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_w_calendar,
      qt_meta_data_w_calendar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &w_calendar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *w_calendar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *w_calendar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_w_calendar))
        return static_cast<void*>(const_cast< w_calendar*>(this));
    return QWidget::qt_metacast(_clname);
}

int w_calendar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
