#ifndef BASICOBJECT_H
#define BASICOBJECT_H

#include <QVector3D>
#include <QVector>
#include <QDebug>
#include <nurbs.h>
#include "source.h"
#include "ray.h"
#include "point.h"

class BasicObject
{

public:
    BasicObject(QVector3D startPoint, QVector<QVector3D> ctrPts, Source* s);
    BasicObject(QVector3D startPoint, QVector<QVector<QVector3D> >ctrPts, Source* s);
    BasicObject();
    /*
     *void computePoints() - calls nurb.cpp, sets and evaluates final surface/curve
    */
    void computePoints();
    const QVector<QVector3D> getCtrlPoints() const;
    void addCtrlPt(const QVector3D& v);
    void createVectorFromPoints(QVector<QVector3D>& v,QVector<float>& f);
    double intersect(const Point &p,const Ray& r);

    const QVector<float>& getCtrlPointsFloatVector() const;
    const QVector<float>& getPointsFloatVector() const;
    QVector<QVector3D>& getPoints();

    QVector<float> getBoundingRect() const;

    QVector<QVector3D> getDerivativeCtrlPoints() const;

    QVector<QVector3D> getDerivativePoints() const;
    void setDerivativePoints(const QVector<QVector3D> &value);

    QVector<float> getDerivativeCtrlPointsFloatVector() const;

    QVector<float> getDerivativePointsFloatVector() const;
    void setDerivativePointsFloatVector(const QVector<float> &value);

private:
    enum Dimension{
        nothing,
        D1,
        D2
    };

    void computeBoundingRect();
    void computeCtrlPtsFromSpread();
    QVector3D computeDerivative(QVector3D p,float angle);

    Source* m_source;
    QVector3D m_startPoint;

    Dimension dimension = nothing;

    //source boundary used for calculating vertical spread
    QVector3D m_sourceBoundary;

    QVector<QVector3D> ctrlPoints;
    QVector<QVector3D> points;
    QVector<QVector3D> derivativeCtrlPoints;
    QVector<QVector3D> derivativePoints;

    QVector<QVector3D> spreadPoints;
    QVector<QVector3D> derivativeSpreadPoints;

    QVector<float> ctrlPointsFloatVector;
    QVector<float> pointsFloatVector;
    QVector<float> derivativeCtrlPointsFloatVector;
    QVector<float> derivativePointsFloatVector;

    QVector<QVector<QVector3D> > ctrlPoints2D;
    QVector<QVector3D> points2D;
    QVector<QVector3D> derivativeCtrlPoints2D;
    QVector<QVector3D> derivativePoints2D;

    QVector<float> ctrlPointsFloatVector2D;
    QVector<float> pointsFloatVector2D;
    QVector<float> derivativeCtrlPointsFloatVector2D;
    QVector<float> derivativePointsFloatVector2D;

    QVector<float> boundingRect;
};

#endif // BASICOBJECT_H
