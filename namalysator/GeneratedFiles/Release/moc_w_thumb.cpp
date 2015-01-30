/****************************************************************************
** Meta object code from reading C++ file 'w_thumb.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../w_thumb.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_thumb.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InternalQPushButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   21,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InternalQPushButton[] = {
    "InternalQPushButton\0\0i\0clickedPageNb(int)\0"
    "onclick()\0"
};

void InternalQPushButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InternalQPushButton *_t = static_cast<InternalQPushButton *>(_o);
        switch (_id) {
        case 0: _t->clickedPageNb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onclick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InternalQPushButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InternalQPushButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_InternalQPushButton,
      qt_meta_data_InternalQPushButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InternalQPushButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InternalQPushButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InternalQPushButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InternalQPushButton))
        return static_cast<void*>(const_cast< InternalQPushButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int InternalQPushButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void InternalQPushButton::clickedPageNb(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_w_thumb[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      28,   26,    8,    8, 0x05,
      43,   26,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      59,    8,    8,    8, 0x0a,
      68,    8,    8,    8, 0x0a,
      78,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_w_thumb[] = {
    "w_thumb\0\0newText(QString)\0i\0nextValue(int)\0"
    "selectPage(int)\0cancel()\0perform()\0"
    "onPage(int)\0"
};

void w_thumb::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        w_thumb *_t = static_cast<w_thumb *>(_o);
        switch (_id) {
        case 0: _t->newText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->nextValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->selectPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->cancel(); break;
        case 4: _t->perform(); break;
        case 5: _t->onPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData w_thumb::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject w_thumb::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_w_thumb,
      qt_meta_data_w_thumb, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &w_thumb::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *w_thumb::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *w_thumb::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_w_thumb))
        return static_cast<void*>(const_cast< w_thumb*>(this));
    return QWidget::qt_metacast(_clname);
}

int w_thumb::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void w_thumb::newText(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void w_thumb::nextValue(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void w_thumb::selectPage(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
