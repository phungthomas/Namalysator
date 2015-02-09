/****************************************************************************
** Meta object code from reading C++ file 'w_main.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../w_main.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_w_main[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      24,    7,    7,    7, 0x0a,
      43,    7,    7,    7, 0x0a,
      69,    7,    7,    7, 0x0a,
      90,    7,    7,    7, 0x0a,
     103,    7,    7,    7, 0x0a,
     119,    7,    7,    7, 0x0a,
     141,    7,    7,    7, 0x0a,
     164,    7,    7,    7, 0x0a,
     188,    7,    7,    7, 0x0a,
     201,    7,    7,    7, 0x0a,
     224,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_w_main[] = {
    "w_main\0\0createActions()\0newsPaperActions()\0"
    "openSummaryErrorsWindow()\0"
    "openCalendarWindow()\0parseBatch()\0"
    "modeNewsPaper()\0openStructureWindow()\0"
    "openTitleCheckWindow()\0openSelectBatchWindow()\0"
    "openReport()\0openStart(std::string)\0"
    "exit()\0"
};

void w_main::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        w_main *_t = static_cast<w_main *>(_o);
        switch (_id) {
        case 0: _t->createActions(); break;
        case 1: _t->newsPaperActions(); break;
        case 2: _t->openSummaryErrorsWindow(); break;
        case 3: _t->openCalendarWindow(); break;
        case 4: _t->parseBatch(); break;
        case 5: _t->modeNewsPaper(); break;
        case 6: _t->openStructureWindow(); break;
        case 7: _t->openTitleCheckWindow(); break;
        case 8: _t->openSelectBatchWindow(); break;
        case 9: _t->openReport(); break;
        case 10: _t->openStart((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 11: _t->exit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData w_main::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject w_main::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_w_main,
      qt_meta_data_w_main, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &w_main::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *w_main::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *w_main::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_w_main))
        return static_cast<void*>(const_cast< w_main*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int w_main::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
