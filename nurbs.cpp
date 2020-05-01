#include "nurbs.h"
#include <QDebug>
#include <QtMath>
Nurbs::Nurbs()
{
}

Nurbs::~Nurbs()
{
    //qDebug()<<"nurb destructed";
}

void Nurbs::test()
{
    qDebug()<<"nurbs lib loaded ok 18.11. 14:16";
}
/*
 * returns spline value for u parametr, knots, controlpoints and degree must be already set
*/
QVector3D Nurbs::coxDeBoorSpline(double u)
{
    float air; //koeficient s indexy i,r
    int s = 0; //mulitplicity of knot
    //qDebug()<<"u"<<u;
    int uk = returnIndexfromKnot(u,*knots);
    if (isEqual(uk,-1)||isEqual(uk,-2)||isEqual(uk,-3)){
        //qDebug()<<"uk is "<<u;
        return  QVector3D(-1,-1,-1);
    }
    //qDebug()<<"uk: " << uk;
    //qDebug()<<"knots: " <<knots->toStdList();
    //qDebug()<<"cp: " << controlPoints->toStdList();
    //QVector3D pomVector[m_degree+1][m_degree+1];
    if (isEqual(knots->at(uk),u)){
        //qDebug()<<"knot equals";
        for (int i=0;i<m_degree;i++){
            if (isEqual(knots->at(uk),knots->at(uk-i))){
                s++;
            }
        }
        //qDebug()<<"multiplicity is: "<<s;
        return QVector3D(-1000,-1000,-1000);
    }

    QVector3D pomVector[m_degree+1][m_degree+1];
    for (int i = 0; i<=(m_degree-s);i++){
        //qDebug()<<"deg-s:"<<m_degree-s<<"uk:"<<uk<<"ctrl count:"<<controlPoints->count();
        pomVector[i][0] = (controlPoints->at(uk-m_degree +i));
    }
    try {
        for (int r = 1;r<=(m_degree-s);r++){
            for (int i = r;i<=(m_degree-s);i++){
                if (isEqual(knots->at(i+m_degree - r + 1),0.0)){
                    air = 0;
                    //qDebug()<<"air is nula";
                }
                else {
                    air = (u - knots->at(uk-m_degree+i))/(knots->at(uk+i-r+1)-knots->at(uk-m_degree+i));
                    //qDebug()<<"u-knots[uk-m_degree+i]/knots[uk+i-r+1]-knots[uk-m_degree+i]="<<u<<"-"<<knots->at(uk-m_degree+i)<<"/"<<knots->at(uk+i-r+1)<<"-"<<knots->at(uk-m_degree+i)<<"="<<air;
                }

                pomVector[i][r] = (1 - air)*pomVector[i-1][r-1]+air*pomVector[i][r-1];                
                //qDebug()<<"vysledek ve vrstve "<<i<<" a sloupci "<<r<<": "<<pomVector[i][r];
            }
        }
    } catch (...) {
        qDebug()<<"chyba";
    }

    QVector3D result = pomVector[m_degree-s][m_degree-s];
    return result;
}

QVector3D Nurbs::coxDeBoorSplineDerivative(double u)
{
    float air; //koeficient s indexy i,r
    int s = 0; //mulitplicity of knot
    //qDebug()<<"u"<<u;
    int uk = returnIndexfromKnot(u,*knotsDer);
    if (isEqual(uk,-1)||isEqual(uk,-2)||isEqual(uk,-3)){
        //qDebug()<<"uk is "<<u;
        return  QVector3D(-1,-1,-1);
    }
    //qDebug()<<"uk: " << uk;
    //qDebug()<<"knots: " <<knots->toStdList();
    //qDebug()<<"cp: " << controlPoints->toStdList();
    //QVector3D pomVector[m_degree+1][m_degree+1];
    if (isEqual(knotsDer->at(uk),u)){
        //qDebug()<<"knot equals";
        for (int i=0;i<(m_degreeDer-1);i++){
            if (isEqual(knotsDer->at(uk),knotsDer->at(uk-i))){
                s++;
            }
        }
        //qDebug()<<"multiplicity is: "<<s;
        return QVector3D(-1000,-1000,-1000);
    }
    QVector3D pomVector[m_degreeDer+1][m_degreeDer+1];
    for (int i = 0; i<=(m_degreeDer-s);i++){
        //qDebug()<<"deg-s:"<<m_degree-s<<"uk:"<<uk<<"ctrl count:"<<controlPoints->count();
        pomVector[i][0] = (derivativeControlPoints.at(uk-m_degreeDer +i));
    }

    try {
        for (int r = 1;r<=(m_degreeDer-s);r++){
            for (int i = r;i<=(m_degreeDer-s);i++){
                if (isEqual(knotsDer->at(i+m_degreeDer - r +1),0.0)){
                    air = 0;
                    //qDebug()<<"air is nula";
                }
                else {
                    air = (u - knotsDer->at(uk-m_degreeDer+i))/(knotsDer->at(uk+i-r+1)-knotsDer->at(uk-m_degreeDer+i));
                    //qDebug()<<"u-knots[uk-m_degree+i-1]/knots[uk+i-r+1]-knots[uk-m_degree+i-1]="<<u<<"-"<<knotsDer->at(uk-m_degreeDer+i)<<"/"<<knotsDer->at(uk+i-r+1)<<"-"<<knotsDer->at(uk-m_degreeDer+i)<<"="<<air;
                }

                pomVector[i][r] = (1 - air)*pomVector[i-1][r-1]+air*pomVector[i][r-1];
                //qDebug()<<"vysledek ve vrstve "<<i<<" a sloupci "<<r<<": "<<pomVector[i][r];
            }
        }
    } catch (...) {
        qDebug()<<"chyba";
    }

    QVector3D result = pomVector[m_degreeDer-s][m_degreeDer-s];
    return result;
}
/*adds control point to controlPoint list*/
void Nurbs::addControlPoint(QVector3D point)
{
    controlPoints->append(point);
}
/*
 * addKnot adds knot to knots list
*/
void Nurbs::addKnot(float i)
{
    knots->append(i);
}
/*
 * calculates unifrom knots in interval <0,1> adds m_degree points-times 0 and 1 to beginning end end
 */
void Nurbs::computeUniformKnots()
{

    int pom = controlPoints->count() - m_degree;
    if (controlPoints->count()<(m_degree+2))
        qDebug()<<"not enough control points";
    float spacing = 1.0f/float(pom);

    for (int i =0; i<m_degree;i++){
        addKnot(0.0f);
        //qDebug()<<knots->last();
    }
    for (int i = 0; i<pom;i++){
        addKnot(float(i) * spacing);
        //qDebug()<<knots->last();
    }
    for (int i=0;i<=m_degree;i++){
        addKnot(1.0f);
        //qDebug()<<knots->last();
    }
    foreach (float var, *knots) {
        //qDebug()<<var;
    }
}
/*
 * returnIndexfromKnot(u) returns index of knots lists so that u is interval (knots[index],knots[index+1])
 * if u equals knot, index of this knot is returned
*/
int Nurbs::returnIndexfromKnot(double u,QList<float>& l)
{
    int resultIndex = -1;
    if (u<0){
        qDebug()<<"u<0";
        return resultIndex;}
    //else if (u>=1){
    //    qDebug()<<"u>=0";
    //    return resultIndex;}
    for (int i = m_degree; i<l.count(); ++i) {
        if ((l.at(i)>=u)&&(u<l.at(i+1)))
        {
            //qDebug()<<"index: "<<i-1;
            return i-1;}
        if (i>(l.count()-m_degree))
                return (l.count()-m_degree+1);
    }
    //qDebug()<<"end";
    return -1;
}
/*
 * computePoints calls coxDeBoor m_refine times with parametr u from 0 to 1 with step 1/refine
 * before computing is checked if m = n + p + 1 (tzn knots = controlpoint + degree + 1)
*/
void Nurbs::computePoints()
{
    int a = (controlPoints->count()+m_degree-knots->count()+1);
    if ((a!=0)||(m_degree==-1)){
        qDebug()<<"m != n + p + 1 or m_degree = -1";
        return;
    }
    else {
        computeDerivativeControlPoints();
        computeDerivativeKnots();
        double u = 0;
        double step = 1.0/m_refine;
        for (int i = 0; i < m_refine; ++i) {
            u += step;
            //qDebug()<<"u:" <<u;
            QVector3D v = coxDeBoorSpline(u);
            QVector3D d = coxDeBoorSplineDerivative(u);
            if (!(isEqual(v.x(),-1000) && isEqual(v.y(),-1000) && isEqual(v.z(),-1000)))
                points.append(v);
            if (!(isEqual(d.x(),-1000) && isEqual(d.y(),-1000) && isEqual(d.z(),-1000)))
                derivative.append(d);
        }
        m_readyForDerivation = true;
        computeNormal();
    }
}

void Nurbs::computeDerivativeControlPoints()
{
    for(int i = 0;i<(controlPoints->count()-1);i++){
        double koef = double(m_degree)/(knots->at(i+m_degree+1)-knots->at(i+1));
        derivativeControlPoints.append(koef*(controlPoints->at(i+1)-controlPoints->at(i)));
    }
}

void Nurbs::computeDerivativeKnots()
{
    for (int i = 1;i<knots->count();i++){
        knotsDer->append(knots->at(i));
    }
}

QVector3D Nurbs::computeNormal()
{
    if (m_readyForDerivation){
        normals.append(QVector3D(infinity,infinity,infinity));
        for(int i = 1; i<(points.count()-1);i++){
            QVector3D vec0 = points.at(i+1)-points.at(i-1);
            QVector3D vec1(-vec0.y(),vec0.x(),0.0);
            vec1.normalize();
            normals.append(vec1);
        }
        normals.append(QVector3D(infinity,infinity,infinity));
    }
    return QVector3D(infinity,infinity,infinity);
}

QVector3D Nurbs::computeDerivative()
{
    return QVector3D(infinity,infinity,infinity);
}

QVector3D Nurbs::derivate(double t)
{
    return QVector3D(infinity,infinity,infinity);
}

QVector<QVector3D> Nurbs::getNormals() const
{
    return normals;
}

QVector<QVector3D> Nurbs::getDerivative() const
{
    return derivative;
}

QVector<QVector3D> Nurbs::getDerivativeControlPoints() const
{
    return derivativeControlPoints;
}

QVector<QVector3D> Nurbs::getPoints() const
{
    return points;
}

QList<float> *Nurbs::getKnots() const
{
    return knots;
}

/*
 * setRefine sets the final number of points which are computed and can be used for drawing - default 100
*/
void Nurbs::setRefine(int value)
{
    m_refine = value;
}
/*
 * set degree
*/
void Nurbs::setDegree(int degree)
{
    m_degree = degree;
    m_degreeDer = m_degree -1;
}

void Nurbs::setControlPoints(QVector<QVector3D> *value)
{
    controlPoints = value;
}
