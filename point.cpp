#include "point.h"

Point::Point()
{

}

Point::Point(const Point &p)
{
    point = p.getPoint();
}

Point::Point(const QVector3D p)
{
    point = p;
}

QVector3D Point::getPoint() const
{
    return point;
}

void Point::setPoint(const QVector3D &value)
{
    point = value;
}
