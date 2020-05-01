#include "ray.h"

Ray::Ray()
{

}

Ray::Ray(QVector3D pos, QVector3D dir):position(pos),direction(dir)
{

}

Ray::Ray(const Ray &p)
{
    position = p.getPosition();
    direction = p.getDirection();
    m_weight = p.getWeight();
}

Ray &Ray::operator =(const Ray &a){
    m_weight = a.getWeight();
    position = a.getPosition();
    direction = a.getDirection();
    return *this;
}

QVector3D Ray::getPosition() const
{
    return position;
}

void Ray::setPosition(const QVector3D &value)
{
    position = value;
}

QVector3D Ray::getDirection() const
{
    return direction;
}

void Ray::setDirection(const QVector3D &value)
{
    direction = value;
}

float Ray::getWeight() const
{
    return m_weight;
}

void Ray::setWeight(float weight)
{
    m_weight = weight;
    //qDebug()<<"m_W"<<m_weight;
    //qDebug()<<"W"<<weight;
}
