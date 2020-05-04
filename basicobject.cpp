#include "basicobject.h"

BasicObject::BasicObject(QVector3D sp, QVector<QVector3D> &spreadPts,Source* s)
{
    m_startPoint = sp;
    spreadPoints = spreadPts;
    m_source = s;

    setSourceBoundary();

    computeCtrlPtsFromSpread();
    computePoints();
    computeBoundingRect();
}

BasicObject::BasicObject()
{
}

void BasicObject::computePoints()
{
    Nurbs nurb;
    nurb.setControlPoints(&controlPoints);
    nurb.setDegree(3);
    nurb.setRefine(10);
    nurb.computeUniformKnots();
    nurb.computePoints();
    points = nurb.getPoints();
    derivativePoints = nurb.getDerivative();
    //qDebug()<<"derivative"<<nurb.getDerivative();
    derivativeControlPoints = nurb.getDerivativeControlPoints();
    createVectorFromPoints(controlPoints,controlPointsFloatVector);
    createVectorFromPoints(points,pointsFloatVector);
    createVectorFromPoints(derivativeControlPoints,derivativeControlPointsFloatVector);
    createVectorFromPoints(derivativePoints,derivativePointsFloatVector);
}

void BasicObject::computePoints2D()
{
    Nurbs2D nurbs2d;
    nurbs2d.setDegree(3,3);
    nurbs2d.setRefine(10,10);
    nurbs2d.setControlPoints(controlPoints2D);
    nurbs2d.computeKnots();
    nurbs2d.computePoints();
    points2D = nurbs2d.getPoints();
    normals2D = nurbs2d.getNormals();
    vector2d2vector(points2D, points);
    vector2d2vector(normals2D, pointsNormals2);
    //qDebug()<<"points bo"<<points.first();
    //qDebug()<<"normals bo"<<pointsNormals2.first();
    //creation of triangles and normals for geometry display
    pointsTriangle = nurbs2d.getPointsVectorTriangles();
    computeNormalsFromTriangles();
    createVectorFromPoints(pointsTriangle,pointsFloatVector2D);
    createVectorFromPoints(pointsNormals, pointsNormalsFloatVector2D);
    CombinePointsAndNormals();
    computeBoundingRect();
}

void BasicObject::createAnalyticalParaboloid()
{
    auto paraboloid = [](double y, double z)->double{return (y*y+z*z)/(4*15)-15;};
    auto derivativeParaboloid = [](double yz)->double{return (yz/(2*15));};
    int countU = 11;
    int countV = 21;
    double stepU = 1;
    double stepV = 2;
    double zstart = -2;
    double ystart = -50;
    for (int i = 0; i < countV; i++){
        QVector<QVector3D>* coordU = new QVector<QVector3D>();
        for (int j = 0; j < countU; j++){
            double y = ystart + i*stepV;
            double z = zstart + j*stepU;
            coordU->append(QVector3D(paraboloid(y,z),y,z));
            QVector3D v1(derivativeParaboloid(y),1,0);
            QVector3D v2(derivativeParaboloid(z),0,1);
            QVector3D normal = QVector3D::crossProduct(v1,v2);
            pointsNormals2.append(normal);
        }
        points2D.append(*coordU);
    }
    //qDebug()<<"points"<<points.count();
    //qDebug()<<"normals"<<pointsNormals2.count();
    vector2d2vector(points2D, points);
    int h = points2D[0].count();
    int v = points2D.count();

    for (int i = 0; i<points2D.count()-1;i++){
        for (int j = 0; j<points2D[0].count()-1;j++){
            pointsTriangle.append(points2D[i][j]);
            pointsTriangle.append(points2D[i][j+1]);
            pointsTriangle.append(points2D[i+1][j]);
            pointsTriangle.append(points2D[i+1][j]);
            pointsTriangle.append(points2D[i][j+1]);
            pointsTriangle.append(points2D[i+1][j+1]);
        }
    }
    computeNormalsFromTriangles();
    createVectorFromPoints(pointsTriangle,pointsFloatVector2D);
    createVectorFromPoints(pointsNormals, pointsNormalsFloatVector2D);
    CombinePointsAndNormals();
    computeBoundingRect();
    type = 2;
    //qDebug()<<"points"<<points.count();
    //qDebug()<<"normals"<<pointsNormals2.count();
}

void BasicObject::printControlPoints()
{
    for (int i = 0; i < controlPoints2D.count(); i++){
        for (int j = 0; j< controlPoints2D[0].count(); j++){
                    qDebug()<<controlPoints2D[i][j];
        }
        qDebug()<<"dalsi radek";
    }
}


const QVector<QVector3D> BasicObject::getControlPoints() const
{
    return this->controlPoints;
}

void BasicObject::addControlPoint(const QVector3D &v)
{
    controlPoints.append(v);
}

void BasicObject::createVectorFromPoints(QVector<QVector3D>& v, QVector<float>& f)
{
    foreach (QVector3D var, v) {
        f.append(var.x());
        f.append(var.y());
        f.append(var.z());
    }
}

const QVector<float> &BasicObject::getControlPointsFloatVector() const
{
    return controlPointsFloatVector;
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
    if (getType()==1){
        foreach(QVector3D var,controlPoints){
            if (var.x()<left)
                left = var.x();
            if (var.y()>up)
                up = var.y();
            if (var.x()>right)
                right = var.x();
            if (var.y()<bottom)
                bottom = var.y();
        }
    }
    else if (getType() == 2){
        for (int i = 0; i < controlPoints2D.count();i++)
            for (int j = 0; j< controlPoints2D[0].count(); j++){
                if (controlPoints2D[i][j].x()<left)
                    left = controlPoints2D[i][j].x();
                if (controlPoints2D[i][j].y()>up)
                    up = controlPoints2D[i][j].y();
                if (controlPoints2D[i][j].x()>right)
                    right = controlPoints2D[i][j].x();
                if (controlPoints2D[i][j].y()<bottom)
                    bottom = controlPoints2D[i][j].y();
            }
    }
    boundingRect.append(left);
    boundingRect.append(up);
    boundingRect.append(right);
    boundingRect.append(bottom);
    /*
    qDebug()<<"bounding rect computed left"<<boundingRect[0];
    qDebug()<<"bounding rect computed up"<<boundingRect[1];
    qDebug()<<"bounding rect computed right"<<boundingRect[2];
    qDebug()<<"bounding rect computed down"<<boundingRect[3];
    */
}

void BasicObject::computeCtrlPtsFromSpread()
{
    controlPoints.append(m_startPoint);
    derivativeSpreadPoints.append(computeDerivative(m_startPoint,spreadPoints.first().y()));
    for (int i=0;i<spreadPoints.count();i++){
        controlPoints.append(computeDerivative(controlPoints.last(),spreadPoints.at(i).y()));
    }
}

void BasicObject::computeNormalsFromTriangles()
{
    //qDebug()<<"points triangle count"<<pointsTriangle.count();
    for (int i = 0; i < pointsTriangle.count(); i= i + 3){
        QVector3D v1 = pointsTriangle[i+1] - pointsTriangle[i];
        QVector3D v2 = pointsTriangle[i+2] - pointsTriangle[i];
        QVector3D cross = QVector3D::crossProduct(v2,v1);
        cross = cross.normalized();
        pointsNormals.append(cross);
        pointsNormals.append(cross);
        pointsNormals.append(cross);
        //pointsNormals2.append(cross);
        //qDebug()<<"normal"<<cross;
    }
    //qDebug()<<"ros triagnels count"<<pointsNormals.count();
}

void BasicObject::CombinePointsAndNormals()
{
    for (int i = 0; i < pointsFloatVector2D.count()-2;i=i+3){
        pointsAndNormalsFloatVector2D.append(pointsFloatVector2D[i]);
        pointsAndNormalsFloatVector2D.append(pointsFloatVector2D[i+1]);
        pointsAndNormalsFloatVector2D.append(pointsFloatVector2D[i+2]);
        pointsAndNormalsFloatVector2D.append(pointsNormalsFloatVector2D[i]);
        pointsAndNormalsFloatVector2D.append(pointsNormalsFloatVector2D[i+1]);
        pointsAndNormalsFloatVector2D.append(pointsNormalsFloatVector2D[i+2]);
    }
    //qDebug()<<"points count"<<pointsFloatVector2D.count();
    //qDebug()<<"points and normal count"<<pointsAndNormalsFloatVector2D.count();
}

void BasicObject::vector2d2vector(const QVector<QVector<QVector3D> >& array, QVector<QVector3D>& vec)
{
    for (int i = 0; i<array.count(); i++)
        for (int j = 0; j < array[0].count(); j++){
            vec.append(array[i][j]);
        }
}

QVector3D BasicObject::computeDerivative(QVector3D p, float angle)
{
    //QVector3D v1 =  (m_source->getSourcePosition()-p).normalized();

}

QVector<QVector3D> BasicObject::getPointsNormals2() const
{
    return pointsNormals2;
}

QVector<QVector3D> BasicObject::getPointsNormals() const
{
    return pointsNormals;
}

QVector<float> BasicObject::getPointsAndNormalsFloatVector2D() const
{
    return pointsAndNormalsFloatVector2D;
}

QVector<float> BasicObject::getPointsNormalsFloatVector2D() const
{
    return pointsNormalsFloatVector2D;
}

QVector<float> BasicObject::getPointsFloatVector2D() const
{
    return pointsFloatVector2D;
}

int BasicObject::getType() const
{
    return type;
}

QVector<float> BasicObject::getControlPointsFloatVector2D() const
{
    return controlPointsFloatVector2D;
}

QVector<QVector<QVector3D> > BasicObject::getPoints2D() const
{
    return points2D;
}

void BasicObject::setSourceBoundary()
{

}

void BasicObject::createTestingObject()
{

}

void BasicObject::createTestingObjectXY2()
{
    float step = -10; //mm
    float focalLength = 15;
    for (int i = 0;i<10;i++){
        float y = i*step;
        //auto par = [](float y)->float{return y*y/(4*15)-15;};
        auto par = [&](float y)->float{return y*y/(4*focalLength)-focalLength;};
        float x = par(y);
        float z = 0;
        QVector3D p = QVector3D(x,y,0);
        controlPoints.append(p);
    }
}

void BasicObject::createTestingObjectXY()
{
    float step = -5; //mm
    for (int i = 0;i<10;i++){
        float y = i*step;
        auto par = [](float y)->float{return y*y/(4*15)-15;};
        float x = par(y);
        float z = 0;
        QVector3D p = QVector3D(x,y,0);
        controlPoints.append(p);
    }
}

void BasicObject::createTestingObjectXZ()
{
    float step = 1; //mm
    for (int i = -5;i<=5;i++){
        float z = i*step;
        auto par = [](float z)->float{return z*z/(4*15)-15;};
        float x = par(z);
        float y = 0;
        QVector3D p = QVector3D(x,y,z);
        controlPoints.append(p);
    }
}

void BasicObject::createTestingPoint()
{
    controlPoints.append(QVector3D(-7.917,-5,20));
    controlPoints.append(QVector3D(-6.667,-10,20));
    controlPoints.append(QVector3D(-4.583,-15,20));
    controlPoints.append(QVector3D(1.667,-20,20));
    controlPoints.append(QVector3D(2.08,-25,20));
    controlPoints.append(QVector3D(6.667,-30,20));
    controlPoints.append(QVector3D(12.08,-35,20));
    controlPoints.append(QVector3D(18.3,-40,20));
    controlPoints.append(QVector3D(25.42,-45,20));
    controlPoints.append(QVector3D(33.33,-50,20));
    controlPoints.append(QVector3D(42.08,-55,20));
}

void BasicObject::createParaboloidControlPoints()
{
    auto paraboloid = [](double y, double z)->double{return (y*y+z*z)/(4*15)-15;};
    int countU = 11;
    int countV = 21;
    double stepU = 1;
    double stepV = 2;
    double zstart = -2;
    double ystart = -50;
    for (int i = 0; i < countV; i++){
        QVector<QVector3D>* coordU = new QVector<QVector3D>();
        for (int j = 0; j < countU; j++){
            double y = ystart + i*stepV;
            double z = zstart + j*stepU;
            coordU->append(QVector3D(paraboloid(y,z),y,z));
        }
        controlPoints2D.append(*coordU);
    }
    //qDebug()<<"par"<<controlPoints2D.count()*controlPoints2D[0].count();
    type = 2;
    //computePoints2D();
}

QVector<float> BasicObject::getDerivativePointsFloatVector() const
{
    return derivativePointsFloatVector;
}

void BasicObject::setDerivativePointsFloatVector(const QVector<float> &value)
{
    derivativePointsFloatVector = value;
}

QVector<float> BasicObject::getDerivativeControlPointsFloatVector() const
{
    return derivativeControlPointsFloatVector;
}

QVector<QVector3D> BasicObject::getDerivativePoints() const
{
    return derivativePoints;
}

void BasicObject::setDerivativePoints(const QVector<QVector3D> &value)
{
    derivativePoints = value;
}

QVector<QVector3D> BasicObject::getDerivativeControlPoints() const
{
    return derivativeControlPoints;
}




