#ifndef NURBS_H
#define NURBS_H

const float infinity = 11111;

#include <QVector3D>
#include <QVector>
#include <QList>
#include <QtMath>
/*
 * how to use class Nurbs:
 *                      1. set degree - setDegree(int degree)
 *                      2. set control points - addControlPoints(QVector3D point)
 *                      3. compute knots - either computeUniformKnots() or ...
 *                      4. compute final points - computePoints()
*/
class Nurbs
{
public:
    Nurbs();
    ~Nurbs();
    void test();
    QVector3D coxDeBoorSpline(double u);
    QVector3D coxDeBoorSplineDerivative(double u);
    void addControlPoint(QVector3D point);
    void addKnot(float i);
    void computeUniformKnots();
    int returnIndexfromKnot(double u,QList<float>& l);
    void computePoints();
    void computeDerivativeControlPoints();
    void computeDerivativeKnots();
    QVector3D computeNormal();
    QVector3D computeDerivative();
    QVector3D derivate(double t);

    QVector<QVector3D>* controlPoints = new QVector<QVector3D>();
    QList<float> *knots = new QList<float>();
    QList<float> *knotsDer = new QList<float>();

    void setRefine(int value);
    void setDegree(int degree);

    void setControlPoints(QVector<QVector3D> *value);

    QVector<QVector3D> getPoints() const;
    int getDegree() const {return m_degree;}
    QVector<QVector3D> *getControlPoints() const {return controlPoints;}
    QList<float>* getKnots() const;


    QVector<QVector3D> getNormals() const;
    QVector<QVector3D> getDerivative() const;

    QVector<QVector3D> getDerivativeControlPoints() const;

private:
    bool m_readyForDerivation = false;
    int m_refine = 3;
    int m_degree = -1;
    int m_degreeDer = -1;
    QVector<QVector3D> points;
    QVector<QVector3D> normals;
    QVector<QVector3D> derivative;
    QVector<QVector3D> derivativeControlPoints;


    inline bool isEqual(double x, double y){
        const double epsilon = 1e-6;
        return std::abs(x-y)<=epsilon;
    }
};

#endif // NURBS_H
