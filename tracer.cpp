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

void Tracer::projectSource(BasicObject &obj, Source &s)
{
    //qDebug()<<"in tracer"<<obj.getPoints().count();
    QVector3D sourceNormal = QVector3D(0,-1,0);
    QVector<QVector3D> sourceCorners;
    sourceCorners.append(QVector3D(s.getChipSizeX()/2,0,s.getChipSizeZ()/2));
    sourceCorners.append(QVector3D(s.getChipSizeX()/2,0,-s.getChipSizeZ()/2));
    sourceCorners.append(QVector3D(-s.getChipSizeX()/2,0,s.getChipSizeZ()/2));
    sourceCorners.append(QVector3D(-s.getChipSizeX()/2,0,-s.getChipSizeZ()/2));

    //qDebug()<<"points"<<obj.getPoints().count();
    //qDebug()<<"normalss"<<obj.getPointsNormals2().count();

    for (int i = 0; i < (obj.getPoints().count());i++) {
        foreach (QVector3D r, sourceCorners){
            QVector3D incident = obj.getPoints().at(i) - r;
            incident = incident.normalized();
            QVector3D normal = obj.getPointsNormals2()[i];
            normal = normal.normalized();
            QVector3D reflected = incident - 2*(QVector3D::dotProduct(incident, normal))*normal;
            reflected = reflected.normalized();
            Ray ry(obj.getPoints().at(i),reflected);
            float angle = qAbs(QVector3D::dotProduct(QVector3D(0,0,1),incident));
            //qDebug()<<"angle"<<angle;
            ry.setWeight(angle);
            rays.append(ry);
            qDebug()<<"ray pos"<<ry.getPosition()<<"ray dir"<<ry.getDirection()<<"i"<<i;
        }
    }
    normalizeFlux();
}

void Tracer::emptyRays()
{
    auto it = rays.begin();
    while (it!=rays.end()){
        rays.erase(it);
        ++it;
    }
}

void Tracer::normalizeFlux()
{
    float sum = 0;
    foreach(Ray r,rays){
        sum += r.getWeight();
    }
    for (int i =0;i<rays.count();i++){
        float p = rays[i].getWeight();
        rays[i].setWeight(p/sum);
    }
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

