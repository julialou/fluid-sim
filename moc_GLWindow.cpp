/****************************************************************************
** Meta object code from reading C++ file 'GLWindow.h'
**
** Created: Fri Aug 16 03:01:21 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/GLWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      28,    9,    9,    9, 0x0a,
      45,    9,    9,    9, 0x0a,
      66,   63,    9,    9, 0x0a,
      87,   63,    9,    9, 0x0a,
     104,   63,    9,    9, 0x0a,
     126,   63,    9,    9, 0x0a,
     148,   63,    9,    9, 0x0a,
     170,   63,    9,    9, 0x0a,
     190,   63,    9,    9, 0x0a,
     210,   63,    9,    9, 0x0a,
     234,   63,    9,    9, 0x0a,
     256,   63,    9,    9, 0x0a,
     280,   63,    9,    9, 0x0a,
     306,   63,    9,    9, 0x0a,
     329,   63,    9,    9, 0x0a,
     350,   63,    9,    9, 0x0a,
     376,   63,    9,    9, 0x0a,
     397,   63,    9,    9, 0x0a,
     418,   63,    9,    9, 0x0a,
     438,   63,    9,    9, 0x0a,
     458,   63,    9,    9, 0x0a,
     478,   63,    9,    9, 0x0a,
     498,   63,    9,    9, 0x0a,
     519,   63,    9,    9, 0x0a,
     538,   63,    9,    9, 0x0a,
     560,   63,    9,    9, 0x0a,
     581,   63,    9,    9, 0x0a,
     602,   63,    9,    9, 0x0a,
     623,   63,    9,    9, 0x0a,
     649,    9,    9,    9, 0x0a,
     666,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLWindow[] = {
    "GLWindow\0\0startSimulation()\0"
    "stopSimulation()\0resetSimulation()\0"
    "_n\0setNumParticles(int)\0setDrawMode(int)\0"
    "setContainerX(double)\0setContainerY(double)\0"
    "setContainerZ(double)\0setSimScale(double)\0"
    "setTimeStep(double)\0setSmoothRadius(double)\0"
    "setElasticity(double)\0setParticleMass(double)\0"
    "setParticleRadius(double)\0"
    "setRestDensity(double)\0setViscosity(double)\0"
    "setSurfaceTension(double)\0"
    "setStiffness(double)\0setThreshold(double)\0"
    "setGravityX(double)\0setGravityY(double)\0"
    "setGravityZ(double)\0setIsovalue(double)\0"
    "setVoxelSize(double)\0setIsosurface(int)\0"
    "setBlobRadius(double)\0setObstacleX(double)\0"
    "setObstacleY(double)\0setObstacleZ(double)\0"
    "setObstacleRadius(double)\0createObstacle()\0"
    "deleteObstacles()\0"
};

void GLWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GLWindow *_t = static_cast<GLWindow *>(_o);
        switch (_id) {
        case 0: _t->startSimulation(); break;
        case 1: _t->stopSimulation(); break;
        case 2: _t->resetSimulation(); break;
        case 3: _t->setNumParticles((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setDrawMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setContainerX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->setContainerY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->setContainerZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->setSimScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->setTimeStep((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setSmoothRadius((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->setElasticity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->setParticleMass((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->setParticleRadius((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->setRestDensity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->setViscosity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->setSurfaceTension((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->setStiffness((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: _t->setThreshold((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->setGravityX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->setGravityY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: _t->setGravityZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 22: _t->setIsovalue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: _t->setVoxelSize((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 24: _t->setIsosurface((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->setBlobRadius((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: _t->setObstacleX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 27: _t->setObstacleY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 28: _t->setObstacleZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->setObstacleRadius((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: _t->createObstacle(); break;
        case 31: _t->deleteObstacles(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GLWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GLWindow::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWindow,
      qt_meta_data_GLWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLWindow))
        return static_cast<void*>(const_cast< GLWindow*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
