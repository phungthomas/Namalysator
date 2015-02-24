/****************************************************************************
** Meta object code from reading C++ file 'w_selectbatch.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../w_selectbatch.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_selectbatch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_w_selectBatch[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      38,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,   47,   14,   14, 0x09,
      73,   14,   14,   14, 0x09,
      97,   14,   14,   14, 0x09,
     123,   14,   14,   14, 0x09,
     133,   14,   14,   14, 0x09,
     146,   14,   14,   14, 0x09,
     157,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_w_selectBatch[] = {
    "w_selectBatch\0\0validated(std::string)\0"
    "exited()\0date\0getListDate(QString)\0"
    "getListSubName(QString)\0"
    "getMets(QListWidgetItem*)\0valider()\0"
    "browsePath()\0browseDb()\0exit()\0"
};

void w_selectBatch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        w_selectBatch *_t = static_cast<w_selectBatch *>(_o);
        switch (_id) {
        case 0: _t->validated((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->exited(); break;
        case 2: _t->getListDate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->getListSubName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->getMets((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->valider(); break;
        case 6: _t->browsePath(); break;
        case 7: _t->browseDb(); break;
        case 8: _t->exit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData w_selectBatch::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject w_selectBatch::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_w_selectBatch,
      qt_meta_data_w_selectBatch, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &w_selectBatch::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *w_selectBatch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *w_selectBatch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_w_selectBatch))
        return static_cast<void*>(const_cast< w_selectBatch*>(this));
    return QWidget::qt_metacast(_clname);
}

int w_selectBatch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void w_selectBatch::validated(std::string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void w_selectBatch::exited()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
