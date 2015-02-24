/****************************************************************************
** Meta object code from reading C++ file 'w_screenshoterror.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../w_screenshoterror.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_screenshoterror.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_w_screenshoterror[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      31,   18,   18,   18, 0x08,
      46,   18,   18,   18, 0x08,
      60,   18,   18,   18, 0x08,
      68,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_w_screenshoterror[] = {
    "w_screenshoterror\0\0saveError()\0"
    "clearPainter()\0setPenColor()\0close()\0"
    "enableCustom(int)\0"
};

void w_screenshoterror::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        w_screenshoterror *_t = static_cast<w_screenshoterror *>(_o);
        switch (_id) {
        case 0: _t->saveError(); break;
        case 1: _t->clearPainter(); break;
        case 2: _t->setPenColor(); break;
        case 3: _t->close(); break;
        case 4: _t->enableCustom((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData w_screenshoterror::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject w_screenshoterror::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_w_screenshoterror,
      qt_meta_data_w_screenshoterror, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &w_screenshoterror::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *w_screenshoterror::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *w_screenshoterror::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_w_screenshoterror))
        return static_cast<void*>(const_cast< w_screenshoterror*>(this));
    return QWidget::qt_metacast(_clname);
}

int w_screenshoterror::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
