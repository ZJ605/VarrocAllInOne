#ifndef RAY_H
#define RAY_H
#include <QVector3D>
#include <QDebug>

class Ray
{
public:
    Ray();
    Ray(QVector3D pos,QVector3D dir);
    Ray(const Ray& p);

    Ray& operator = (const Ray&);

    QVector3D getPosition() const;
    void setPosition(const QVector3D &value);

    QVector3D getDirection() const;
    void setDirection(const QVector3D &value);

    float getWeight() const;
    void setWeight(float weight);

private:
    QVector3D position;
    QVector3D direction;
    float m_weight = -1;
};

#endif // RAY_H
