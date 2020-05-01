#ifndef SOURCE_H
#define SOURCE_H

#include <QDialog>
#include <QDebug>
#include <QtMath>
#include "point.h"
#include "ray.h"

namespace Ui {
class Source;
}

class Source : public QDialog
{
    Q_OBJECT

public:
    explicit Source(QWidget *parent = nullptr);
    ~Source();

    Source(const Source&s);
    Source& operator = (const Source&);

    bool getIsSet() const;
    Point getSourcePosition() const;

    QVector3D getSourceNormal() const;

    void setSourcePosition(const Point &value);

    QVector3D getSourceDirection1() const;
    void setSourceDirection1(const QVector3D &value);

    QVector3D getSourceDirection2() const;
    void setSourceDirection2(const QVector3D &value);

    void setSourceNormal(const QVector3D &value);

    float getSourceSize1() const;

    float getSourceSize2() const;

signals:
    void sourceChanged(QVector<float> v);

private slots:

    void on_btn_OK_clicked();
    void showEvent(QShowEvent *) override;

private:
    Ui::Source *ui;

    void generateRays();

    bool isSet = false;

    Point sourcePosition;

    QVector3D sourceDirection1;
    QVector3D sourceDirection2;    
    QVector3D sourceNormal;
    float sourceSize1 = 0;
    float sourceSize2 = 0;

    QVector<float> sourceFloatVector;
    QVector<Ray> sourceRays;

};

#endif // SOURCE_H
