/****************************************************************************
** Meta object code from reading C++ file 'w_structview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../w_structview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_structview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_w_structview[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      29,   13,   13,   13, 0x08,
      57,   13,   13,   13, 0x08,
      68,   13,   13,   13, 0x08,
      75,   13,   13,   13, 0x08,
      84,   13,   13,   13, 0x08,
      94,   13,   13,   13, 0x08,
     106,   13,   13,   13, 0x08,
     132,  121,   13,   13, 0x08,
     176,   13,   13,   13, 0x08,
     194,   13,   13,   13, 0x08,
     213,   13,   13,   13, 0x08,
     228,   13,   13,   13, 0x08,
     238,   13,   13,   13, 0x08,
     245,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_w_structview[] = {
    "w_structview\0\0getDate(QDate)\0"
    "getIdMets(QListWidgetItem*)\0previous()\0"
    "next()\0zoomIn()\0zoomOut()\0structure()\0"
    "clearPainter()\0item,item2\0"
    "drawRect(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "openErrorScreen()\0showListSampling()\0"
    "viewCalendar()\0checked()\0undo()\0"
    "viewHtml()\0"
};

void w_structview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        w_structview *_t = static_cast<w_structview *>(_o);
        switch (_id) {
        case 0: _t->getDate((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 1: _t->getIdMets((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->previous(); break;
        case 3: _t->next(); break;
        case 4: _t->zoomIn(); break;
        case 5: _t->zoomOut(); break;
        case 6: _t->structure(); break;
        case 7: _t->clearPainter(); break;
        case 8: _t->drawRect((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 9: _t->openErrorScreen(); break;
        case 10: _t->showListSampling(); break;
        case 11: _t->viewCalendar(); break;
        case 12: _t->checked(); break;
        case 13: _t->undo(); break;
        case 14: _t->viewHtml(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData w_structview::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject w_structview::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_w_structview,
      qt_meta_data_w_structview, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &w_structview::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *w_structview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *w_structview::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_w_structview))
        return static_cast<void*>(const_cast< w_structview*>(this));
    return QWidget::qt_metacast(_clname);
}

int w_structview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
