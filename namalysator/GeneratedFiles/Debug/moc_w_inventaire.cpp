/****************************************************************************
** Meta object code from reading C++ file 'w_inventaire.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../w_inventaire.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_inventaire.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_w_inventaire[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   14,   13,   13, 0x08,
      65,   13,   13,   13, 0x08,
      77,   13,   13,   13, 0x08,
      94,   13,   13,   13, 0x08,
     113,   13,   13,   13, 0x08,
     128,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_w_inventaire[] = {
    "w_inventaire\0\0,\0"
    "lineChanged(QTableWidgetItem*,QTableWidgetItem*)\0"
    "viewIssue()\0showInventaire()\0"
    "getcbYear(QString)\0exportIssues()\0"
    "showErrors()\0"
};

void w_inventaire::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        w_inventaire *_t = static_cast<w_inventaire *>(_o);
        switch (_id) {
        case 0: _t->lineChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTableWidgetItem*(*)>(_a[2]))); break;
        case 1: _t->viewIssue(); break;
        case 2: _t->showInventaire(); break;
        case 3: _t->getcbYear((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->exportIssues(); break;
        case 5: _t->showErrors(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData w_inventaire::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject w_inventaire::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_w_inventaire,
      qt_meta_data_w_inventaire, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &w_inventaire::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *w_inventaire::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *w_inventaire::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_w_inventaire))
        return static_cast<void*>(const_cast< w_inventaire*>(this));
    return QWidget::qt_metacast(_clname);
}

int w_inventaire::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
