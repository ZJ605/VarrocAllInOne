#include "geometrydialog.h"
#include "geometrymodel.h"
#include <QDebug>

GeometryModel::GeometryModel(QObject *parent):QObject(parent)
{
    //create2degSpline();

}
void GeometryModel::create2degSpline()
{
    Nurbs *nurb = new Nurbs();

    nurb->setDegree(3);

    nurb->addControlPoint(QVector3D(0,0,0));
    nurb->addControlPoint(QVector3D(10,20,0));
    nurb->addControlPoint(QVector3D(12,50,0));
    nurb->addControlPoint(QVector3D(16,70,0));
    nurb->addControlPoint(QVector3D(18,60,0));
    nurb->addControlPoint(QVector3D(20,40,0));
    nurb->addControlPoint(QVector3D(25,10,0));
    //nurb->computeUniformKnots();
    //m_nurb.coxDeBoorSpline(0.2f);
    //m_nurb.coxDeBoorSpline(0.6f);
    //m_nurb.coxDeBoorSpline(0.8f);
    //m_nurb.coxDeBoorSpline(0.99f);
    //emit geometryChanged();
/*
    for (int i =0; i<newObject->count();i++){
        qDebug()<<"NO: "<<newObject->at(i);
    }
*/
    /*
    for (int i=0;i<geometryObjects.count();i++){
        qDebug()<<geometryObjects.at(i);
    }
    */
}

void GeometryModel::showDialog()
{
    GeometryDialog *gd = new GeometryDialog();
    connect(gd,&GeometryDialog::pointAndSourceRead,this,&GeometryModel::readPointsAndSourceFromDialog);
    gd->show();
}

void GeometryModel::readPointsFromDialog(QVector<QVector3D> &points)
{
    /*
    QVector<QVector3D> m_points = points;
    BasicObject *object = new BasicObject(m_points);
    object->computePoints();
    //object->createVecFromCtrlPts();
    //object->createArrayFromPoints();
    objects.append(object);

    emit geometryChanged(*object);
    */
}

void GeometryModel::readPointsAndSourceFromDialog(QVector3D &sp, QVector<QVector3D> &p, Source *s)
{
    //qDebug()<<"ctr points read"<<p;
    //BasicObject *object = new BasicObject(sp, p,s);
    //objects.append(object);
    //emit geometryChanged(*object);

}

void GeometryModel::createParaboloid()
{
    BasicObject *bo = new BasicObject();
    bo->createParaboloidControlPoints();

    bo->computePoints2D();
    objects.append(bo);
    //qDebug()<<"count in model"<<bo->getPointsFloatVector2D().count();
    emit geometryChanged(*bo);
}

void GeometryModel::fromListToVec()
{

}

