/****************************************************************************
** Meta object code from reading C++ file 'ControllingWidget.h'
**
** Created: Wed Apr 6 13:31:35 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/widgets/ControllingWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ControllingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ControllingWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      58,   18,   18,   18, 0x08,
      93,   18,   18,   18, 0x08,
     109,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ControllingWidget[] = {
    "ControllingWidget\0\0"
    "slot_checkb_mxf1_useImage_toggle(bool)\0"
    "slot_tb_mxf1_browseImage_clicked()\0"
    "slot_mkxml_go()\0slot_mkxml_saveResults()\0"
};

const QMetaObject ControllingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControllingWidget,
      qt_meta_data_ControllingWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ControllingWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ControllingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ControllingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControllingWidget))
        return static_cast<void*>(const_cast< ControllingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ControllingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slot_checkb_mxf1_useImage_toggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: slot_tb_mxf1_browseImage_clicked(); break;
        case 2: slot_mkxml_go(); break;
        case 3: slot_mkxml_saveResults(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
