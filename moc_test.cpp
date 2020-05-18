/****************************************************************************
** Meta object code from reading C++ file 'test.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_test_t {
    QByteArrayData data[20];
    char stringdata0[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_test_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_test_t qt_meta_stringdata_test = {
    {
QT_MOC_LITERAL(0, 0, 4), // "test"
QT_MOC_LITERAL(1, 5, 12), // "showErrorMsg"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 1), // "s"
QT_MOC_LITERAL(4, 21, 25), // "on_addChildButton_clicked"
QT_MOC_LITERAL(5, 47, 11), // "addChildBid"
QT_MOC_LITERAL(6, 59, 3), // "str"
QT_MOC_LITERAL(7, 63, 10), // "addSubTree"
QT_MOC_LITERAL(8, 74, 5), // "Node*"
QT_MOC_LITERAL(9, 80, 11), // "subtreeRoot"
QT_MOC_LITERAL(10, 92, 16), // "onSaveBtnClicked"
QT_MOC_LITERAL(11, 109, 18), // "onModifyBtnClicked"
QT_MOC_LITERAL(12, 128, 15), // "onDelBtnClicked"
QT_MOC_LITERAL(13, 144, 15), // "onBidBtnClicked"
QT_MOC_LITERAL(14, 160, 18), // "onSeqBidBtnClicked"
QT_MOC_LITERAL(15, 179, 19), // "on_LoadFile_clicked"
QT_MOC_LITERAL(16, 199, 19), // "on_SaveFile_clicked"
QT_MOC_LITERAL(17, 219, 15), // "on_root_clicked"
QT_MOC_LITERAL(18, 235, 18), // "on_newFile_clicked"
QT_MOC_LITERAL(19, 254, 21) // "on_addSubTree_clicked"

    },
    "test\0showErrorMsg\0\0s\0on_addChildButton_clicked\0"
    "addChildBid\0str\0addSubTree\0Node*\0"
    "subtreeRoot\0onSaveBtnClicked\0"
    "onModifyBtnClicked\0onDelBtnClicked\0"
    "onBidBtnClicked\0onSeqBidBtnClicked\0"
    "on_LoadFile_clicked\0on_SaveFile_clicked\0"
    "on_root_clicked\0on_newFile_clicked\0"
    "on_addSubTree_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_test[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x0a /* Public */,
       4,    0,   87,    2, 0x08 /* Private */,
       5,    1,   88,    2, 0x08 /* Private */,
       7,    1,   91,    2, 0x08 /* Private */,
      10,    0,   94,    2, 0x08 /* Private */,
      11,    0,   95,    2, 0x08 /* Private */,
      12,    0,   96,    2, 0x08 /* Private */,
      13,    0,   97,    2, 0x08 /* Private */,
      14,    0,   98,    2, 0x08 /* Private */,
      15,    0,   99,    2, 0x08 /* Private */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    0,  101,    2, 0x08 /* Private */,
      18,    0,  102,    2, 0x08 /* Private */,
      19,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<test *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showErrorMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_addChildButton_clicked(); break;
        case 2: _t->addChildBid((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->addSubTree((*reinterpret_cast< Node*(*)>(_a[1]))); break;
        case 4: _t->onSaveBtnClicked(); break;
        case 5: _t->onModifyBtnClicked(); break;
        case 6: _t->onDelBtnClicked(); break;
        case 7: _t->onBidBtnClicked(); break;
        case 8: _t->onSeqBidBtnClicked(); break;
        case 9: _t->on_LoadFile_clicked(); break;
        case 10: _t->on_SaveFile_clicked(); break;
        case 11: _t->on_root_clicked(); break;
        case 12: _t->on_newFile_clicked(); break;
        case 13: _t->on_addSubTree_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject test::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_test.data,
    qt_meta_data_test,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *test::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_test.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
