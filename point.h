#ifndef POINT_H
#define POINT_H
#include <QVector3D>

class Point
{
public:
    Point();
    Point(const Point& p);
    Point(const QVector3D);
    Point& operator = (const Point&){return *this;}

    QVector3D getPoint() const;
    void setPoint(const QVector3D &value);

private:
    QVector3D point;

};

#endif // POINT_H
