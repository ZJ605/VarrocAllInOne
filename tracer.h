#ifndef TRACER_H
#define TRACER_H

#include <QDialog>
#include <QDebug>
#include <QVector>
#include <QVector3D>
#include "detector.h"
#include "basicobject.h"
#include "source.h"
#include "ray.h"
namespace Ui {
class Tracer;
}

class Tracer : public QDialog
{
    Q_OBJECT

public:
    explicit Tracer(QWidget *parent = nullptr);
    ~Tracer();

    void traceZX(QVector<QVector3D>& pts, QVector<QVector3D>& derPts, Source& s, Detector& d);
    void traceYX(QVector<QVector3D>& pts, QVector<QVector3D>& derPts, Source& s, Detector& d);
    void trace(BasicObject& obj, Source& s, Detector& d);
    //void trace(BasicObject& obj, Source& s);
    void projectSource(BasicObject& obj, Source& s);

    bool isSet;
    QVector<float> getReflectedRaysVector() const;
    QVector<float> getIncidentRaysVector() const;
    void setIncidentRaysVector(const QVector<float> &value);
    QVector<Ray> getReflectedRays() const;

    QVector<Ray> rays;

signals:
    void raysTraced(QVector<float> v,QVector<float> r);
public slots:
    void test();
    void trace(BasicObject& o,Source& s);

private:
    Ui::Tracer *ui;

    void emptyRays();
    void normalizeFlux();
    void createSourceRaysRND(Source& s);
    void createSourceRays(Source& s, QVector<QVector3D>& r);
    void epmtyRays();

    Ray& getReflectedRay(QVector3D v, QVector3D n, Source &s);

    QVector<Ray> reflectedRays;
    QVector<float> reflectedRaysVector;

    QVector<Ray> incidentRays;
    QVector<float> incidentRaysVector;
};

#endif // TRACER_H
