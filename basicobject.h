#ifndef BASICOBJECT_H
#define BASICOBJECT_H

#include <QVector3D>
#include <QVector>
#include <QDebug>
#include "nurbs.h"
#include "nurbs2d.h"
#include "source.h"
#include "ray.h"
#include "point.h"
//!
//! \brief The BasicObject class is responsible for creating control points from given spread, radiuses, paraboloid etc.
//! Controlpoints are then passed to nurbs(2D) class which computes points and derivatives
//!

class BasicObject
{
public:
    BasicObject(QVector3D startPoint, QVector<QVector3D> &ctrPts, Source* s);
    BasicObject();
/*
    enum Type {
        surface,
        curve,
        none
    };
*/
    //!
    //! \brief computePoints - from control points computes the curve (degree and precision are default)
    //!
    void computePoints();
    void computePoints2D();
    void createAnalyticalParaboloid();
    void printControlPoints();

    const QVector<QVector3D> getControlPoints() const;
    void addControlPoint(const QVector3D& v);
    void createVectorFromPoints(QVector<QVector3D>& v,QVector<float>& f);
    const QVector<float>& getControlPointsFloatVector() const;
    const QVector<float>& getPointsFloatVector() const;
    QVector<QVector3D>& getPoints();
    QVector<float> getBoundingRect() const;
    QVector<QVector3D> getDerivativeControlPoints() const;
    QVector<QVector3D> getDerivativePoints() const;
    void setDerivativePoints(const QVector<QVector3D> &value);
    QVector<float> getDerivativeControlPointsFloatVector() const;
    QVector<float> getDerivativePointsFloatVector() const;
    void setDerivativePointsFloatVector(const QVector<float> &value);
    void setSourceBoundary();
    void createTestingObject();
    void createTestingObjectXY2();
    void createTestingObjectXY();
    void createTestingObjectXZ();
    void createTestingPoint();
    void createParaboloidControlPoints();


    QVector<QVector<QVector3D> > getPoints2D() const;

    QVector<float> getControlPointsFloatVector2D() const;

    QVector<float> getPointsFloatVector2D() const;

    int getType() const;

    QVector<float> getPointsNormalsFloatVector2D() const;

    QVector<float> getPointsAndNormalsFloatVector2D() const;

    QVector<QVector3D> getPointsNormals() const;

    QVector<QVector3D> getPointsNormals2() const;

private:
    int type = 0; // 0 - nic, 1 - curve, 2 - surface
    void computeBoundingRect();
    void computeCtrlPtsFromSpread();
    void computeNormalsFromTriangles();
    void CombinePointsAndNormals();
    void points2d2points();
    QVector3D computeDerivative(QVector3D p,float angle);

    Source* m_source;
    QVector3D m_startPoint;

    //source boundary used for calculating vertical spread
    QVector3D m_sourceBoundary;

    QVector<QVector3D> controlPoints;
    QVector<QVector3D> points;
    QVector<QVector3D> derivativeControlPoints;
    QVector<QVector3D> derivativePoints;

    QVector<QVector3D> normalControlPoints;

    QVector<QVector<QVector3D> > controlPoints2D;
    QVector<QVector<QVector3D> > derivativeControlPoints2D;
    QVector<QVector<QVector3D> > points2D;
    QVector<QVector<QVector3D> > derivativePoints2D;
    QVector<QVector3D> pointsTriangle;
    QVector<QVector3D> pointsNormals;
    QVector<QVector3D> pointsNormals2; //normals for tracing - pointsNormals have duplicated points for creation of triangles
    QVector<QVector3D> spreadPoints;
    QVector<QVector3D> derivativeSpreadPoints;

    QVector<float> controlPointsFloatVector;
    QVector<float> pointsFloatVector;
    QVector<float> derivativeControlPointsFloatVector;
    QVector<float> derivativePointsFloatVector;

    QVector<float> controlPointsFloatVector2D;
    QVector<float> pointsFloatVector2D;
    QVector<float> pointsNormalsFloatVector2D;
    QVector<float> derivativeControlPointsFloatVector2D;
    QVector<float> derivativePointsFloatVector2D;
    QVector<float> boundingRect;

    QVector<float> pointsAndNormalsFloatVector2D;
};

#endif // BASICOBJECT_H
