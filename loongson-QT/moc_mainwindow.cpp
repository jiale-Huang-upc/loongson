/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "startWork"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "handleTimeout"
QT_MOC_LITERAL(4, 36, 11), // "dialChanged"
QT_MOC_LITERAL(5, 48, 5), // "value"
QT_MOC_LITERAL(6, 54, 12), // "dial2Changed"
QT_MOC_LITERAL(7, 67, 12), // "dial3Changed"
QT_MOC_LITERAL(8, 80, 12), // "dial4Changed"
QT_MOC_LITERAL(9, 93, 9), // "runorstop"
QT_MOC_LITERAL(10, 103, 4), // "save"
QT_MOC_LITERAL(11, 108, 4), // "open"
QT_MOC_LITERAL(12, 113, 5), // "reset"
QT_MOC_LITERAL(13, 119, 14), // "voltageClicked"
QT_MOC_LITERAL(14, 134, 1), // "m"
QT_MOC_LITERAL(15, 136, 11), // "timeClicked"
QT_MOC_LITERAL(16, 148, 16), // "updateData_sigle"
QT_MOC_LITERAL(17, 165, 4), // "maxy"
QT_MOC_LITERAL(18, 170, 8), // "FFT_WAVE"
QT_MOC_LITERAL(19, 179, 6), // "cursor"
QT_MOC_LITERAL(20, 186, 14), // "set_triger_fun"
QT_MOC_LITERAL(21, 201, 11), // "measure_fun"
QT_MOC_LITERAL(22, 213, 6) // "single"

    },
    "MainWindow\0startWork\0\0handleTimeout\0"
    "dialChanged\0value\0dial2Changed\0"
    "dial3Changed\0dial4Changed\0runorstop\0"
    "save\0open\0reset\0voltageClicked\0m\0"
    "timeClicked\0updateData_sigle\0maxy\0"
    "FFT_WAVE\0cursor\0set_triger_fun\0"
    "measure_fun\0single"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  107,    2, 0x0a /* Public */,
       4,    1,  108,    2, 0x0a /* Public */,
       6,    1,  111,    2, 0x0a /* Public */,
       7,    1,  114,    2, 0x0a /* Public */,
       8,    1,  117,    2, 0x0a /* Public */,
       9,    0,  120,    2, 0x0a /* Public */,
      10,    0,  121,    2, 0x0a /* Public */,
      11,    0,  122,    2, 0x0a /* Public */,
      12,    0,  123,    2, 0x0a /* Public */,
      13,    1,  124,    2, 0x0a /* Public */,
      15,    1,  127,    2, 0x0a /* Public */,
      16,    2,  130,    2, 0x0a /* Public */,
      18,    0,  135,    2, 0x0a /* Public */,
      19,    0,  136,    2, 0x0a /* Public */,
      20,    0,  137,    2, 0x0a /* Public */,
      21,    0,  138,    2, 0x0a /* Public */,
      22,    0,  139,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startWork((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->handleTimeout(); break;
        case 2: _t->dialChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->dial2Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->dial3Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->dial4Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->runorstop(); break;
        case 7: _t->save(); break;
        case 8: _t->open(); break;
        case 9: _t->reset(); break;
        case 10: _t->voltageClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->timeClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->updateData_sigle((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->FFT_WAVE(); break;
        case 14: _t->cursor(); break;
        case 15: _t->set_triger_fun(); break;
        case 16: _t->measure_fun(); break;
        case 17: _t->single(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::startWork)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::startWork(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_Worker_t {
    QByteArrayData data[6];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Worker"
QT_MOC_LITERAL(1, 7, 11), // "resultReady"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 6), // "result"
QT_MOC_LITERAL(4, 27, 7), // "doWork1"
QT_MOC_LITERAL(5, 35, 9) // "parameter"

    },
    "Worker\0resultReady\0\0result\0doWork1\0"
    "parameter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->doWork1((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Worker::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::resultReady)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Worker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Worker.data,
    qt_meta_data_Worker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Worker::resultReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
