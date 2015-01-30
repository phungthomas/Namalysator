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
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      29,   13,   13,   13, 0x08,
      46,   13,   13,   13, 0x08,
      61,   13,   13,   13, 0x08,
      89,   13,   13,   13, 0x08,
     100,   13,   13,   13, 0x08,
     107,   13,   13,   13, 0x08,
     121,   13,   13,   13, 0x08,
     130,   13,   13,   13, 0x08,
     140,   13,   13,   13, 0x08,
     150,   13,   13,   13, 0x08,
     162,   13,   13,   13, 0x08,
     188,  177,   13,   13, 0x08,
     232,   13,   13,   13, 0x08,
     250,   13,   13,   13, 0x08,
     269,   13,   13,   13, 0x08,
     284,   13,   13,   13, 0x08,
     295,   13,   13,   13, 0x08,
     305,   13,   13,   13, 0x08,
     312,   13,   13,   13, 0x08,
     323,   13,   13,   13, 0x08,
     338,   13,   13,   13, 0x08,
     361,   13,   13,   13, 0x08,
     384,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_w_structview[] = {
    "w_structview\0\0getDate(QDate)\0"
    "getIdMetsII(int)\0showThumb(int)\0"
    "getIdMets(QListWidgetItem*)\0previous()\0"
    "next()\0showPage(int)\0zoomIn()\0zoomOut()\0"
    "zoomNon()\0structure()\0clearPainter()\0"
    "item,item2\0drawRect(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "openErrorScreen()\0showListSampling()\0"
    "viewCalendar()\0viewList()\0checked()\0"
    "undo()\0viewHtml()\0viewMetsFile()\0"
    "rbhelperCalendar(bool)\0rbhelperSampling(bool)\0"
    "rbhelperList(bool)\0"
};

void w_structview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        w_structview *_t = static_cast<w_structview *>(_o);
        switch (_id) {
        case 0: _t->getDate((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 1: _t->getIdMetsII((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->showThumb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->getIdMets((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->previous(); break;
        case 5: _t->next(); break;
        case 6: _t->showPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->zoomIn(); break;
        case 8: _t->zoomOut(); break;
        case 9: _t->zoomNon(); break;
        case 10: _t->structure(); break;
        case 11: _t->clearPainter(); break;
        case 12: _t->drawRect((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 13: _t->openErrorScreen(); break;
        case 14: _t->showListSampling(); break;
        case 15: _t->viewCalendar(); break;
        case 16: _t->viewList(); break;
        case 17: _t->checked(); break;
        case 18: _t->undo(); break;
        case 19: _t->viewHtml(); break;
        case 20: _t->viewMetsFile(); break;
        case 21: _t->rbhelperCalendar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->rbhelperSampling((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->rbhelperList((*reinterpret_cast< bool(*)>(_a[1]))); break;
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
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
