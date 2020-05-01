#ifndef GEOMETRYMODEL_H
#define GEOMETRYMODEL_H

#include <QObject>
#include <QVector3D>
#include <QVector>
#include "nurbs2d.h"
#include "nurbs.h"
#include "basicobject.h"
#include "source.h"

class GeometryModel:public QObject
{
    Q_OBJECT
public:
    GeometryModel(QObject *parent);
    void create2degSpline();    

    QList<QVector<QVector3D>*> geometry3DObjects;
    QList<QVector<QVector2D>*> geometry2DObjects;

    QList<BasicObject*> objects;

signals:
    void geometryChanged(BasicObject&);

public slots:
    /*
     * void create() displays window, where control points are set, knots are set, degree is set and geometry object is created and added to list
    */
    void showDialog();
    /*
     * void readPointsFromDialog() - reads points from dialog, creates new object and appends it to objects list
     * */
    void readPointsFromDialog(QVector<QVector3D>&);
    void readPointsAndSourceFromDialog(QVector3D &sp, QVector<QVector3D> &p,Source* s);
    void createParaboloid();
private:
    void fromListToVec();
};

#endif // GEOMETRYMODEL_H
