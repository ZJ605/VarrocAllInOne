#ifndef NURBS2D_H
#define NURBS2D_H

#include "Nurbs2D_global.h"
#include <QVector3D>
#include <QVector>
#include <QList>
#include <QtMath>
#include <QDebug>

class NURBS2D_EXPORT Nurbs2D
{
public:
    Nurbs2D();
    void computeKnots();
    int computePoints(); //given degrees, control points and knots, computePoints evaluates urb via cox de boor
    int computeDerivativeControlPoints();
    int computeDerivativePoints();
    int computeNormals();


    void setRefine(int u, int v);
    void setDegree(int u, int v);
    void setControlPoints(const QVector<QVector<QVector3D> > &value);

    QVector<QVector<QVector3D> > getControlPoints() const;

    QVector<QVector<QVector3D> > getPoints() const;

    QVector<QVector3D> getPointsVectorTriangles() const;

    QVector<QVector<QVector3D> > getDerivativePoints() const;

    QVector<QVector<QVector3D> > getDerivativeControlPoints() const;


private:
    int refine[2]; //number of points in which nurb is evaluated in horizontal/vertical direction [u,v]
    bool refineSet = false;
    int degree[2]; //degree of spline in horizontal/vertical direction [u,v]
    bool degreeSet = false;

    QVector<QVector<QVector3D> > controlPoints;
    QVector<QVector<QVector3D> > derivativeControlPoints;
    QVector<QVector<QVector3D> > derivativeControlPointsU;
    QVector<QVector<QVector3D> > derivativeControlPointsV;
    QVector<QVector<QVector3D> > normals;
    bool controlPointsSet = false;
    bool derivativeControlPointsSet = false;

    QVector<double> knotsU;
    QVector<double> knotsV;
    bool m_knotsSet = false;

    QVector<QVector<QVector3D> > points;
    QVector<QVector<QVector3D> > derivativePoints;

    QVector<QVector3D> pointsVectorTriangles; //converted points to triangles for render
    QVector<float> pointsFloatVector;

    void computeUniformKnots(int ctrlPointsCount, QVector<double>& resultv, int deg);
    int binarySearch(QVector<double>&, double value);
    int linearSearch(const QVector<double>& vec, int deg, double value);
    QVector3D coxDeBoor2D(double u, double v);
    QVector3D coxDeBoor(const QVector<QVector3D> &ctrlpts,const QVector<double> &kn, int deg, double value);
    QVector3D coxDeBoorSpline(const QVector<QVector3D> &ctrlpts,const QVector<double> &kn, int knindex, int deg, double value);
    int Vector2D2VectorTriangles(const QVector<QVector<QVector3D> >& vec, QVector<QVector3D>& triangelVec);

    bool isEqual(double a, double b){return qAbs(a-b)<0.000001 ? true : false;}
};

#endif // NURBS2D_H
