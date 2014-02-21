/****************************************************************************
** Meta object code from reading C++ file 'w_disk.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../w_disk.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_disk.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_w_disk[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      25,    7,    7,    7, 0x08,
      47,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_w_disk[] = {
    "w_disk\0\0clickDate(QDate)\0openPath(QModelIndex)\0"
    "getIdMets(QListWidgetItem*)\0"
};

void w_disk::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        w_disk *_t = static_cast<w_disk *>(_o);
        switch (_id) {
        case 0: _t->clickDate((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 1: _t->openPath((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->getIdMets((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData w_disk::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject w_disk::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_w_disk,
      qt_meta_data_w_disk, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &w_disk::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *w_disk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *w_disk::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_w_disk))
        return static_cast<void*>(const_cast< w_disk*>(this));
    return QWidget::qt_metacast(_clname);
}

int w_disk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
