#include "tracer.h"
#include "ui_tracer.h"

Tracer::Tracer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tracer)
{
    ui->setupUi(this);
}

Tracer::~Tracer()
{
    delete ui;
}

void Tracer::test()
{
    qDebug()<<"OK tracer show";
}

void Tracer::trace(BasicObject &o, Source &s)
{
    if (s.getIsSet()){
        QVector3D sourceNormal = s.getSourceNormal();
        for (int i = 1;i<(o.getPoints().count()-1);i++) {
            //QVector3D normalPom = o.getPoints().at(i+1)-o.getPoints().at(i-1);
            QVector3D normalPom = o.getDerivativePoints().at(i);
            QVector3D normal;
            normal.setX(-normalPom.y());
            normal.setY(normalPom.x());
            normal.setZ(0.0);
            normal = normal.normalized();
            Ray r = getReflectedRay(o.getPoints().at(i),normal,s);
            reflectedRays.append(r);
        }
    }
    emit raysTraced(getIncidentRaysVector(),getReflectedRaysVector());
}

Ray& Tracer::getReflectedRay(QVector3D v, QVector3D n, Source &s)
{
    QVector3D incident = v - s.getSourcePosition().getPoint();
    incident = incident.normalized();
    incidentRaysVector.append(s.getSourcePosition().getPoint().x());
    incidentRaysVector.append(s.getSourcePosition().getPoint().y());
    incidentRaysVector.append(s.getSourcePosition().getPoint().z());
    incidentRaysVector.append(v.x()+s.getSourcePosition().getPoint().x());
    incidentRaysVector.append(v.y()+s.getSourcePosition().getPoint().y());
    incidentRaysVector.append(v.z()+s.getSourcePosition().getPoint().z());
    Ray newIncidentRay(s.getSourcePosition().getPoint(),incident);
    newIncidentRay.getDirection().normalize();
    incidentRays.append(newIncidentRay);

    QVector3D reflected = incident - 2*(QVector3D::dotProduct(incident,n))*n;
    reflected = reflected.normalized();
    //QVector3D reflected = n;
    //qDebug()<<"dot"<<2*(QVector3D::dotProduct(incident,n));
    reflectedRaysVector.append(v.x());
    reflectedRaysVector.append(v.y());
    reflectedRaysVector.append(v.z());

    reflectedRaysVector.append(reflected.x()+v.x());
    reflectedRaysVector.append(reflected.y()+v.y());
    reflectedRaysVector.append(reflected.z()+v.z());
    Ray* newRay = new Ray(v,reflected);
    newRay->setWeight(QVector3D::crossProduct(s.getSourceNormal(),incident).length());

    return *newRay;
}

QVector<Ray> Tracer::getReflectedRays() const
{
    return reflectedRays;
}

QVector<float> Tracer::getIncidentRaysVector() const
{
    return incidentRaysVector;
}

void Tracer::setIncidentRaysVector(const QVector<float> &value)
{
    incidentRaysVector = value;
}

QVector<float> Tracer::getReflectedRaysVector() const
{
    return reflectedRaysVector;
}

