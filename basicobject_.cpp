#include "basicobject.h"

BasicObject::BasicObject(QVector3D sp, QVector<QVector3D> ctrlPts,Source* s)
{
    m_startPoint = sp;
    ctrlPoints = ctrlPts;
    m_source = s;
    dimension = D1;
    //computeCtrlPtsFromSpread();
    computePoints();
    computeBoundingRect();
}

BasicObject::BasicObject(QVector3D startPoint, QVector<QVector<QVector3D> > ctrPts, Source *s)
{
    m_startPoint = startPoint;
    ctrlPoints2D = ctrPts;
    m_source = s;
}

BasicObject::BasicObject()
{
}

void BasicObject::computePoints()
{
    Nurbs nurb;
    nurb.setControlPoints(&ctrlPoints);
    nurb.setDegree(3);
    nurb.setRefine(50);
    nurb.computeUniformKnots();
    nurb.computePoints();
    points = nurb.getPoints();
    derivativePoints = nurb.getDerivative();
    derivativeCtrlPoints = nurb.getDerivativeControlPoints();    
    createVectorFromPoints(ctrlPoints,ctrlPointsFloatVector);
    createVectorFromPoints(points,pointsFloatVector);
    createVectorFromPoints(derivativeCtrlPoints,derivativeCtrlPointsFloatVector);
    createVectorFromPoints(derivativePoints,derivativePointsFloatVector);
}

const QVector<QVector3D> BasicObject::getCtrlPoints() const
{
    return this->ctrlPoints;
}

void BasicObject::addCtrlPt(const QVector3D &v)
{
    ctrlPoints.append(v);
}

void BasicObject::createVectorFromPoints(QVector<QVector3D>& v, QVector<float>& f)
{
    foreach (QVector3D var, v) {
        f.append(var.x());
        f.append(var.y());
        f.append(var.z());
    }
}

double BasicObject::intersect(const Point &p, const Ray &r)
{
    return 0;
}

const QVector<float> &BasicObject::getCtrlPointsFloatVector() const
{
    return ctrlPointsFloatVector;
}

const QVector<float> &BasicObject::getPointsFloatVector() const
{
    return pointsFloatVector;
}

QVector<QVector3D>& BasicObject::getPoints()
{
    return points;
}

QVector<float> BasicObject::getBoundingRect() const
{
    return boundingRect;
}

void BasicObject::computeBoundingRect()
{
    float left,up,right,bottom;
    left = 0;
    up = 0;
    right = 0;
    bottom = 0;
    foreach(QVector3D var,ctrlPoints){
        if (var.x()<left)
            left = var.x();
        if (var.y()>up)
            up = var.y();
        if (var.x()>right)
            right = var.x();
        if (var.y()<bottom)
            bottom = var.y();
    }
    boundingRect.append(left);
    boundingRect.append(up);
    boundingRect.append(right);
    boundingRect.append(bottom);
    //qDebug()<<"rect in obj"<<boundingRect;
}

void BasicObject::computeCtrlPtsFromSpread()
{
    ctrlPoints.append(m_startPoint);
    derivativeSpreadPoints.append(computeDerivative(m_startPoint,spreadPoints.first().y()));
    for (int i=0;i<spreadPoints.count();i++){
        ctrlPoints.append(computeDerivative(ctrlPoints.last(),spreadPoints.at(i).y()));
    }
}

QVector3D BasicObject::computeDerivative(QVector3D p, float angle)
{
    QVector3D v1 =  (m_source->getSourcePosition().getPoint()-p).normalized();
    //QVector3D v2 =
}

QVector<float> BasicObject::getDerivativePointsFloatVector() const
{
    return derivativePointsFloatVector;
}

void BasicObject::setDerivativePointsFloatVector(const QVector<float> &value)
{
    derivativePointsFloatVector = value;
}

QVector<float> BasicObject::getDerivativeCtrlPointsFloatVector() const
{
    return derivativeCtrlPointsFloatVector;
}

QVector<QVector3D> BasicObject::getDerivativePoints() const
{
    return derivativePoints;
}

void BasicObject::setDerivativePoints(const QVector<QVector3D> &value)
{
    derivativePoints = value;
}

QVector<QVector3D> BasicObject::getDerivativeCtrlPoints() const
{
    return derivativeCtrlPoints;
}




