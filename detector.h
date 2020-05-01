#ifndef DETECTOR_H
#define DETECTOR_H

#include <QWidget>
#include <QtMath>
#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QtMath>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QRgb>
#include <QWidget>
#include "ray.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "tracer.h"
#include "ray.h"

namespace Ui {
class Detector;
}

class Detector : public QWidget
{
    Q_OBJECT

public:
    explicit Detector(Tracer* t, QWidget *parent = nullptr);
    ~Detector();

    struct detectorPoint {
        int h = -1;
        int v = -1;
        float intensity = -1;
        detectorPoint(){}
        detectorPoint(int H, int V, float inten){h = H; v = V; intensity = inten;}
    };
    void projectRaysOnDetector(QVector<Ray>& r);
    void projectChipOnDetector(QVector<Ray>& r);
    QVector<Ray*> rays;

    cv::Mat detector;
    QVector<QVector<float> > detectorV;
    //QVector<QVector<>>
    float max = 0;

signals:
    void detectorUpdated(cv::Mat m);

private:
    Ui::Detector *ui;
    Tracer* tracer;
    //friend class DetectorTests;


    QGraphicsPixmapItem pixmap;

    QVector<double> hor;
    QVector<double> ver;
    bool raysAreSet = false;
    double step;
    double horCoord1;
    double horCoord2;
    double vertCoord1;
    double vertCoord2;

    void prepareDetector();
    //void prepareDetector(Mat& m);
    int binarySearch(QVector<double>& v, double value);
    int binarySearch(QVector<double>& h, double h1, double h2, QVector<double>& v, double v1, double v2);
    inline bool isEqual(double a, double b){return qAbs(a-b)<0.001 ? true:false;}

    QImage putImage(const cv::Mat& m);
private slots:
    //!
    //! \brief reorderProjectedPoints - reorders 4 points so points are ordered countersclockwise
    //! \param p
    //!
    bool reorderProjectedPoints(QVector<detectorPoint>& p);
    //!
    //! \brief pointInPolygon returns true if point q is inside polygon, else false
    //! \param q
    //! \param p0
    //! \param p1
    //! \param p2
    //! \param p3
    //! \return
    //!
    bool pointInPolygon(detectorPoint q, QVector<detectorPoint> &pole);
    bool pointInPolygon2(detectorPoint q, QVector<detectorPoint> &pole);
    //!
    //! \brief doIntersect checks if 2 lines consturcted from p1, p2 and q1 q2 intersect
    //! \param p1
    //! \param p2
    //! \param q1
    //! \param q2
    //! \return
    //!
    bool doIntersect(detectorPoint p1, detectorPoint q1, detectorPoint p2, detectorPoint q2);
    //!
    //! \brief onSegment checks if point q lies on line segment by points p and r
    //! \param p
    //! \param q
    //! \param r
    //! \return
    //!
    bool onSegment(detectorPoint p, detectorPoint q, detectorPoint r);
    //!
    //! \brief orientation returns 0 if points are colinear, 1 if oriented clockwise, 2 if oriented counterclockwise
    //! \param p
    //! \param q
    //! \param r
    //! \return
    //!
    int orientation(detectorPoint p,detectorPoint q, detectorPoint r);
    int orientation2(detectorPoint p,detectorPoint q, detectorPoint r);
    float rayWeightInPolygon(detectorPoint q, QVector<detectorPoint> &pole);
    void on_pshBtn_setAngle_clicked();
    void drawPlot();
    void geometryTraced();

};

#endif // DETECTOR_H
