/****************************************************************************
** Meta object code from reading C++ file 'TypingTest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/TypingTest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TypingTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TypingTestEdit_t {
    QByteArrayData data[3];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TypingTestEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TypingTestEdit_t qt_meta_stringdata_TypingTestEdit = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TypingTestEdit"
QT_MOC_LITERAL(1, 15, 14), // "endOfPlainText"
QT_MOC_LITERAL(2, 30, 0) // ""

    },
    "TypingTestEdit\0endOfPlainText\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TypingTestEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void TypingTestEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TypingTestEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->endOfPlainText(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TypingTestEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TypingTestEdit::endOfPlainText)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TypingTestEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QTextEdit::staticMetaObject>(),
    qt_meta_stringdata_TypingTestEdit.data,
    qt_meta_data_TypingTestEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TypingTestEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TypingTestEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TypingTestEdit.stringdata0))
        return static_cast<void*>(this);
    return QTextEdit::qt_metacast(_clname);
}

int TypingTestEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TypingTestEdit::endOfPlainText()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_TypingTest_t {
    QByteArrayData data[9];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TypingTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TypingTest_t qt_meta_stringdata_TypingTest = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TypingTest"
QT_MOC_LITERAL(1, 11, 9), // "newResult"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "repeat"
QT_MOC_LITERAL(4, 29, 9), // "isTimeout"
QT_MOC_LITERAL(5, 39, 10), // "showResult"
QT_MOC_LITERAL(6, 50, 10), // "paintEvent"
QT_MOC_LITERAL(7, 61, 12), // "QPaintEvent*"
QT_MOC_LITERAL(8, 74, 5) // "event"

    },
    "TypingTest\0newResult\0\0repeat\0isTimeout\0"
    "showResult\0paintEvent\0QPaintEvent*\0"
    "event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TypingTest[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   42,    2, 0x09 /* Protected */,
       4,    0,   43,    2, 0x09 /* Protected */,
       5,    0,   44,    2, 0x09 /* Protected */,
       6,    1,   45,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void TypingTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TypingTest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newResult((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->repeat(); break;
        case 2: _t->isTimeout(); break;
        case 3: _t->showResult(); break;
        case 4: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TypingTest::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TypingTest::newResult)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TypingTest::staticMetaObject = { {
    QMetaObject::SuperData::link<Page::staticMetaObject>(),
    qt_meta_stringdata_TypingTest.data,
    qt_meta_data_TypingTest,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TypingTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TypingTest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TypingTest.stringdata0))
        return static_cast<void*>(this);
    return Page::qt_metacast(_clname);
}

int TypingTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Page::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TypingTest::newResult(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_RepeatTypingTest_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RepeatTypingTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RepeatTypingTest_t qt_meta_stringdata_RepeatTypingTest = {
    {
QT_MOC_LITERAL(0, 0, 16) // "RepeatTypingTest"

    },
    "RepeatTypingTest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RepeatTypingTest[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void RepeatTypingTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject RepeatTypingTest::staticMetaObject = { {
    QMetaObject::SuperData::link<TypingTest::staticMetaObject>(),
    qt_meta_stringdata_RepeatTypingTest.data,
    qt_meta_data_RepeatTypingTest,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RepeatTypingTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RepeatTypingTest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RepeatTypingTest.stringdata0))
        return static_cast<void*>(this);
    return TypingTest::qt_metacast(_clname);
}

int RepeatTypingTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TypingTest::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_LessonTypingTest_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LessonTypingTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LessonTypingTest_t qt_meta_stringdata_LessonTypingTest = {
    {
QT_MOC_LITERAL(0, 0, 16) // "LessonTypingTest"

    },
    "LessonTypingTest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LessonTypingTest[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void LessonTypingTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject LessonTypingTest::staticMetaObject = { {
    QMetaObject::SuperData::link<TypingTest::staticMetaObject>(),
    qt_meta_stringdata_LessonTypingTest.data,
    qt_meta_data_LessonTypingTest,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LessonTypingTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LessonTypingTest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LessonTypingTest.stringdata0))
        return static_cast<void*>(this);
    return TypingTest::qt_metacast(_clname);
}

int LessonTypingTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TypingTest::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
