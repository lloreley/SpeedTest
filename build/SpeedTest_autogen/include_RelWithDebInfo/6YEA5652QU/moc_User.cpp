/****************************************************************************
** Meta object code from reading C++ file 'User.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/User.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'User.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ServerClient_t {
    QByteArrayData data[12];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerClient_t qt_meta_stringdata_ServerClient = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ServerClient"
QT_MOC_LITERAL(1, 13, 15), // "messageReceived"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "message"
QT_MOC_LITERAL(4, 38, 14), // "connectionLost"
QT_MOC_LITERAL(5, 53, 12), // "disconnected"
QT_MOC_LITERAL(6, 66, 12), // "sendToServer"
QT_MOC_LITERAL(7, 79, 3), // "str"
QT_MOC_LITERAL(8, 83, 14), // "processMessage"
QT_MOC_LITERAL(9, 98, 18), // "tryConnectToServer"
QT_MOC_LITERAL(10, 117, 15), // "checkConnection"
QT_MOC_LITERAL(11, 133, 4) // "read"

    },
    "ServerClient\0messageReceived\0\0message\0"
    "connectionLost\0disconnected\0sendToServer\0"
    "str\0processMessage\0tryConnectToServer\0"
    "checkConnection\0read"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   59,    2, 0x0a /* Public */,
       8,    1,   62,    2, 0x09 /* Protected */,
       9,    0,   65,    2, 0x08 /* Private */,
      10,    0,   66,    2, 0x08 /* Private */,
      11,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ServerClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ServerClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->messageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->connectionLost(); break;
        case 2: _t->disconnected(); break;
        case 3: _t->sendToServer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->processMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->tryConnectToServer(); break;
        case 6: _t->checkConnection(); break;
        case 7: _t->read(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ServerClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerClient::messageReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ServerClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerClient::connectionLost)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ServerClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerClient::disconnected)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ServerClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ServerClient.data,
    qt_meta_data_ServerClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ServerClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ServerClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ServerClient::messageReceived(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerClient::connectionLost()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ServerClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
struct qt_meta_stringdata_BaseUser_t {
    QByteArrayData data[7];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BaseUser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BaseUser_t qt_meta_stringdata_BaseUser = {
    {
QT_MOC_LITERAL(0, 0, 8), // "BaseUser"
QT_MOC_LITERAL(1, 9, 14), // "accountCreated"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 17), // "accountNotCreated"
QT_MOC_LITERAL(4, 43, 12), // "userNotFound"
QT_MOC_LITERAL(5, 56, 17), // "passwordIncorrect"
QT_MOC_LITERAL(6, 74, 15) // "loginSuccessful"

    },
    "BaseUser\0accountCreated\0\0accountNotCreated\0"
    "userNotFound\0passwordIncorrect\0"
    "loginSuccessful"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BaseUser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,
       6,    0,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BaseUser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BaseUser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accountCreated(); break;
        case 1: _t->accountNotCreated(); break;
        case 2: _t->userNotFound(); break;
        case 3: _t->passwordIncorrect(); break;
        case 4: _t->loginSuccessful(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BaseUser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseUser::accountCreated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BaseUser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseUser::accountNotCreated)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BaseUser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseUser::userNotFound)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BaseUser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseUser::passwordIncorrect)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BaseUser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseUser::loginSuccessful)) {
                *result = 4;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject BaseUser::staticMetaObject = { {
    QMetaObject::SuperData::link<ServerClient::staticMetaObject>(),
    qt_meta_stringdata_BaseUser.data,
    qt_meta_data_BaseUser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BaseUser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseUser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BaseUser.stringdata0))
        return static_cast<void*>(this);
    return ServerClient::qt_metacast(_clname);
}

int BaseUser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ServerClient::qt_metacall(_c, _id, _a);
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
void BaseUser::accountCreated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BaseUser::accountNotCreated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BaseUser::userNotFound()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void BaseUser::passwordIncorrect()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BaseUser::loginSuccessful()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
struct qt_meta_stringdata_UnauthorizedUser_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UnauthorizedUser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UnauthorizedUser_t qt_meta_stringdata_UnauthorizedUser = {
    {
QT_MOC_LITERAL(0, 0, 16) // "UnauthorizedUser"

    },
    "UnauthorizedUser"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UnauthorizedUser[] = {

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

void UnauthorizedUser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject UnauthorizedUser::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseUser::staticMetaObject>(),
    qt_meta_stringdata_UnauthorizedUser.data,
    qt_meta_data_UnauthorizedUser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UnauthorizedUser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UnauthorizedUser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UnauthorizedUser.stringdata0))
        return static_cast<void*>(this);
    return BaseUser::qt_metacast(_clname);
}

int UnauthorizedUser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseUser::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_User_t {
    QByteArrayData data[1];
    char stringdata0[5];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_User_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_User_t qt_meta_stringdata_User = {
    {
QT_MOC_LITERAL(0, 0, 4) // "User"

    },
    "User"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_User[] = {

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

void User::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject User::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseUser::staticMetaObject>(),
    qt_meta_stringdata_User.data,
    qt_meta_data_User,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *User::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *User::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_User.stringdata0))
        return static_cast<void*>(this);
    return BaseUser::qt_metacast(_clname);
}

int User::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseUser::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
