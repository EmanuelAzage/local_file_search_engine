/****************************************************************************
** Meta object code from reading C++ file 'multiwin.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "multiwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multiwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Multiwin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      32,    9,    9,    9, 0x0a,
      52,    9,    9,    9, 0x0a,
      72,    9,    9,    9, 0x0a,
      99,    9,    9,    9, 0x0a,
     118,    9,    9,    9, 0x0a,
     138,    9,    9,    9, 0x0a,
     168,    9,    9,    9, 0x0a,
     194,    9,    9,    9, 0x0a,
     224,    9,    9,    9, 0x0a,
     267,  254,    9,    9, 0x0a,
     319,  313,    9,    9, 0x0a,
     344,    9,    9,    9, 0x0a,
     368,    9,    9,    9, 0x0a,
     396,    9,    9,    9, 0x0a,
     447,  436,  424,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Multiwin[] = {
    "Multiwin\0\0searchButtonClicked()\0"
    "exitButtonClicked()\0quitButtonClicked()\0"
    "singleWordRButtonClicked()\0"
    "orRButtonClicked()\0andRButtonClicked()\0"
    "sortByPageRankButtonClicked()\0"
    "sortByNameButtonClicked()\0"
    "sortByIncomingButtonClicked()\0"
    "sortByOutgoingButtonClicked()\0"
    "filenameItem\0filesnameListItemDblClicked(QListWidgetItem*)\0"
    "event\0closeEvent(QCloseEvent*)\0"
    "sortNameButtonClicked()\0"
    "sortIncomingButtonClicked()\0"
    "sortOutgoingButtonClicked()\0std::string\0"
    "itemString\0get_filename(std::string)\0"
};

void Multiwin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Multiwin *_t = static_cast<Multiwin *>(_o);
        switch (_id) {
        case 0: _t->searchButtonClicked(); break;
        case 1: _t->exitButtonClicked(); break;
        case 2: _t->quitButtonClicked(); break;
        case 3: _t->singleWordRButtonClicked(); break;
        case 4: _t->orRButtonClicked(); break;
        case 5: _t->andRButtonClicked(); break;
        case 6: _t->sortByPageRankButtonClicked(); break;
        case 7: _t->sortByNameButtonClicked(); break;
        case 8: _t->sortByIncomingButtonClicked(); break;
        case 9: _t->sortByOutgoingButtonClicked(); break;
        case 10: _t->filesnameListItemDblClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 11: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 12: _t->sortNameButtonClicked(); break;
        case 13: _t->sortIncomingButtonClicked(); break;
        case 14: _t->sortOutgoingButtonClicked(); break;
        case 15: { std::string _r = _t->get_filename((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Multiwin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Multiwin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Multiwin,
      qt_meta_data_Multiwin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Multiwin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Multiwin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Multiwin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Multiwin))
        return static_cast<void*>(const_cast< Multiwin*>(this));
    return QWidget::qt_metacast(_clname);
}

int Multiwin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
