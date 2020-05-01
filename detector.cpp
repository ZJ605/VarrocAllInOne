#include "detector.h"
#include "ui_detector.h"
#include <QPen>

using namespace cv;

Detector::Detector(Tracer *t, QWidget *parent) : QWidget(parent), ui(new Ui::Detector), tracer(t), step(0.05),horCoord1(-20), horCoord2(20), vertCoord1(-15), vertCoord2(15)
{
    ui->setupUi(this);

    prepareDetector();
    connect(tracer,&Tracer::raysTraced,this,&Detector::geometryTraced);

    ui->grfVw->setScene(new QGraphicsScene(this));
    ui->grfVw->scene()->addItem(&pixmap);
    //drawPlot();
}

Detector::~Detector()
{
    delete ui;

}

void Detector::on_pshBtn_setAngle_clicked()
{

}

void Detector::drawPlot()
{
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }

}

void Detector::geometryTraced()
{
    float u0 = -10;
    float u1 = 10;
    float step = 0.1;
    double max = 0;
    int count = (u1-u0)/step + 1;
    QVector<double> x(count),y(count);
    for (int i = 0;i<count;i++) {
        x[i] = double(u0 + i*step);
        y[i] = double(0);
    }

    for (int i = 0;i<tracer->getReflectedRays().count();i++) {
        float degree = qAcos(tracer->getReflectedRays().at(i).getDirection().x())*180.0/3.141592653;
        if (u0<=degree&&degree<=u1){
            int index = qFloor(10.0*(degree - u0));
            y[index]+=tracer->getReflectedRays().at(i).getWeight();
            if (max<y[index])
                max = y[index];

        }
    }

    ui->wdgt_tracedPlot->addGraph();
    ui->wdgt_tracedPlot->graph(0)->setData(x, y);
    ui->wdgt_tracedPlot->graph(0)->setPen(QPen(Qt::green));
    ui->wdgt_tracedPlot->xAxis->setLabel("x");
    ui->wdgt_tracedPlot->yAxis->setLabel("y");
    ui->wdgt_tracedPlot->xAxis->setRange(u0, u1);
    ui->wdgt_tracedPlot->yAxis->setRange(0, max+1);
    ui->wdgt_tracedPlot->replot();
}

void Detector::projectRaysOnDetector(QVector<Ray>& rs)
{
    foreach (Ray r, rs) {
        double angleY = 180/M_PI*QVector3D::dotProduct(QVector3D(0,1,0), r.getDirection()); //projekce do z - horizontalni souradnice
        double angleZ = 180/M_PI*QVector3D::dotProduct(QVector3D(0,0,1), r.getDirection());//projekce do y - vertikalni souradnice
        //qDebug()<<"angle z rad"<<QVector3D::dotProduct(QVector3D(0,0,1), r.getDirection());
        //qDebug()<<"angle y rad"<<QVector3D::dotProduct(QVector3D(0,1,0), r.getDirection());
        //qDebug()<<"angle z"<<angleZ;
        //qDebug()<<"angle y"<<angleY;
        int col = binarySearch(hor,angleZ);
        int row = binarySearch(ver,angleY);
        //qDebug()<<"row"<<row<<"col"<<col;
        if (col<0 || row < 0){
            //qDebug()<<"out of map";
            continue;
        }
        detectorV[row][col] += r.getWeight();
        if (detectorV[row][col]>max)
            max = detectorV[row][col];
    }
    if (detectorV.count()==0)
        return;
    if (detectorV[0].count()==0)
        return;
    for (int i = 0;i<detectorV.count();i++) {
        for (int j = 0;j<detectorV[0].count();j++) {
            detector.at<uchar>(i,j) = (detectorV[i][j]*255/max);

            /*
            if (detectorV[i][j]*255/max!=0){
                qDebug()<<"i"<<i;
                qDebug()<<"j"<<j;
            }
            */
        }
    }
    /*
    for (int i = 0;i<detectorV[0].count();i++) {
        qDebug()<<detector.at<uchar>(100,i);
        //qDebug()<<qFloor(detectorV[30][i]*255/max);
    }
    */
    if (detector.empty())
        qDebug()<<"empty";

    pixmap.setPixmap(QPixmap::fromImage(putImage(detector)));
    //ui->gV->fitInView(&pixmap,Qt::KeepAspectRatio);
    this->update();
    //emit detectorUpdated(detector);
}

void Detector::projectChipOnDetector(QVector<Ray> &rs)
{
    if (rs.count()%4 != 0){
        qDebug()<<"parpsky nedelitelne 4";
        return;
    }
    float sum = 0;
    qDebug()<<"pocet parsku"<<rs.count();
    for (int i = 4; i<rs.count(); i = i+4){
        double angleY1 = 180/M_PI*QVector3D::dotProduct(QVector3D(0,1,0), rs.at(i).getDirection()); //projekce do z - horizontalni souradnice
        double angleZ1 = 180/M_PI*QVector3D::dotProduct(QVector3D(0,0,1), rs.at(i).getDirection());//projekce do y - vertikalni souradnice
        double angleY2 = 180/M_PI*QVector3D::dotProduct(QVector3D(0,1,0), rs.at(i+1).getDirection()); //projekce do z - horizontalni souradnice
        double angleZ2 = 180/M_PI*QVector3D::dotProduct(QVector3D(0,0,1), rs.at(i+1).getDirection());//projekce do y - vertikalni souradnice
        double angleY3 = 180/M_PI*QVector3D::dotProduct(QVector3D(0,1,0), rs.at(i+2).getDirection()); //projekce do z - horizontalni souradnice
        double angleZ3 = 180/M_PI*QVector3D::dotProduct(QVector3D(0,0,1), rs.at(i+2).getDirection());//projekce do y - vertikalni souradnice
        double angleY4 = 180/M_PI*QVector3D::dotProduct(QVector3D(0,1,0), rs.at(i+3).getDirection()); //projekce do z - horizontalni souradnice
        double angleZ4 = 180/M_PI*QVector3D::dotProduct(QVector3D(0,0,1), rs.at(i+3).getDirection());//projekce do y - vertikalni souradnice
        QVector<detectorPoint> points;

        points.append(detectorPoint(binarySearch(hor,angleZ1),binarySearch(ver,angleY1),rs.at(i).getWeight()));
        points.append(detectorPoint(binarySearch(hor,angleZ2),binarySearch(ver,angleY2),rs.at(i+1).getWeight()));
        points.append(detectorPoint(binarySearch(hor,angleZ3),binarySearch(ver,angleY3),rs.at(i+2).getWeight()));
        points.append(detectorPoint(binarySearch(hor,angleZ4),binarySearch(ver,angleY4),rs.at(i+3).getWeight()));
        //qDebug()<<"pred"<<points.at(0).h<<" "<<points.at(0).v<<" "<<points.at(1).h<<" "<<points.at(1).v<<" "<<points.at(2).h<<points.at(2).v<<" "<<" "<<points.at(3).h<<points.at(3).v<<" ";

        if (points.at(0).h<0||points.at(0).v<0||points.at(1).h<0||points.at(1).v<0||points.at(2).h<0||points.at(2).v<0||points.at(3).h<0||points.at(3).v<0){
            qDebug()<<"not in map -detector/project chip on detector";
            qDebug()<<"rays out of map"<<points[0].h<<points[0].v<<"/"<<points[1].h<<points[1].v<<"/"<<points[2].h<<points[2].v<<"/"<<points[3].h<<points[3].v;
            continue;
        }
        reorderProjectedPoints(points);
        float INF = 1000000;
        float hmin = INF, hmax = -INF, vmin = INF, vmax = -INF;
        for (int i = 0; i<4; i++){
            if (points[i].h<hmin)
                hmin = points[i].h;
            if (points[i].h>hmax)
                hmax = points[i].h;
            if (points[i].v<vmin)
                vmin = points[i].v;
            if (points[i].v>vmax)
                vmax = points[i].v;
        }
        detectorPoint pom;

        for (int i = qFloor(hmin); i<=qFloor(hmax); i++){
            for (int j = vmin;j<=vmax;j++) {
                pom.h = i;
                pom.v = j;
                bool a = pointInPolygon2(pom,points);
                if (a){
                    detectorV[j][i] += rayWeightInPolygon(pom,points);
                    sum +=1;
                }
                else {
                    qDebug()<<"point not in polygon"<<i<<" "<<j;
                }
            }
        }
    }

    if (detectorV.count()==0)
        return;
    if (detectorV[0].count()==0)
        return;

    float max = 0;
    for (int i = 0;i<detectorV.count();i++) {
        for (int j = 0;j<detectorV[0].count();j++) {
            //detector.at<uchar>(i,j) = qFloor((detectorV[i][j]));
            if (detectorV[i][j]>max)
                max = detectorV[i][j];
        }
    }
    max*=1000/max;
    for (int i = 0;i<detectorV.count();i++) {
        for (int j = 0;j<detectorV[0].count();j++) {
            detectorV[i][j] = detectorV[i][j]*max;
            detector.at<uchar>(i,j) = qFloor((detectorV[i][j]));
        }
    }
    if (detector.empty())
        qDebug()<<"empty";

    pixmap.setPixmap(QPixmap::fromImage(putImage(detector)));
    ui->grfVw->fitInView(&pixmap,Qt::KeepAspectRatio);
    this->update();
}

void Detector::prepareDetector()
{
    int hcount = (horCoord2 - horCoord1)/step+1;
    for (int i = 0; i< hcount; ++i){
        hor.append(horCoord1 +i*step);
    }
    int vcount = (vertCoord2 - vertCoord1)/step+1;
    for (int i = 0; i < vcount; ++i){
        ver.append(vertCoord1 +i*step);
    }

    for (int i = 0; i<vcount; i++){
        detectorV.append(QVector<float>());
        for (int j = 0;j<hcount;j++) {
            detectorV[i].append(0);
        }
    }

    detector = Mat::ones(vcount,hcount,CV_8UC1)*0;
}

int Detector::binarySearch(QVector<double> &v, double value)
{
    int L = 0;
    int R = v.count()-1;
    if (value < v[0])
        return -3;
    if (value > v.last())
        return -2;
    int middle = -1;
    while(L<=R){
        middle = qFloor((L+R)/2);
        if (isEqual(v[middle],value))
            return middle;
        else if (value>v[middle]){
            L = middle + 1;
        }
        else if (value < v[middle])
            R = middle - 1;

    }
    return middle;
}

int Detector::binarySearch(QVector<double> &h, double h1, double h2, QVector<double> &v, double v1, double v2)
{

}

QImage Detector::putImage(const Mat &m)
{
    if (m.type()==CV_8UC1){
        QVector<QRgb> coltable;
        for (int i = 0;i<256;i++)
            coltable.append(qRgb(i,i,i));
        const uchar *qimagebuffer = (const uchar*)m.data;
        QImage img(qimagebuffer,m.cols,m.rows,m.step, QImage::Format_Indexed8);
        img.setColorTable(coltable);

        return img;
    }
    else
        return QImage();
}

bool Detector::reorderProjectedPoints(QVector<Detector::detectorPoint> &pole)
{
    if (pole.count()<3){
        qDebug()<<"short vector - Detector::reorderProjectedPoints";
        return false;
    }
    detectorPoint pom;
    int ref = 1; //ordering clockwise
    QVector<Detector::detectorPoint> result;
    result.append(pole[0]);
    for (int i = 0;i<pole.count()-2;i++) {
        for (int k = i+1;k<pole.count();k++) {
            int counter = 0;
            for (int l = i+1; l<pole.count(); l++){
                int ol = orientation2(result[i],pole[k],pole[l]);
                if (ol != ref){
                    continue;
                }
                else {
                    ++counter;
                }
                if (counter==(pole.count()-result.count()-1)){
                    result.append(pole[k]);
                    pom = pole[result.count()-1];
                    pole[result.count()-1] = pole[k];
                    pole[k] = pom;
                    counter = 0;
                }
            }
        }
    }
    result.append(pole[pole.count()-1]);
    for (int i = 0; i<pole.count();i++)
        pole[i]=result[i];
    return true;
}

bool Detector::pointInPolygon(Detector::detectorPoint q, QVector<detectorPoint> &pole)
{
    detectorPoint extreme(10000000, q.v,0);
    int count = 0, i = 0;
    do {
        int next = (i+1)%4;
        if (doIntersect(pole[i],pole[next],q,extreme)){
            count++;
        }
        i = next;
    }
    while (i!=0);
    return (bool)count%2;
}

bool Detector::pointInPolygon2(Detector::detectorPoint q, QVector<Detector::detectorPoint> &pole)
{
    int pocet = pole.count();
    if (pocet < 3){
        qDebug()<<"not enough points in pole - Detector::pointInPolygon2";
        return false;
    }
    int i = 1;
    int o1 = orientation2(pole[0],pole[1],q);
    int o2 = orientation2(pole[1],pole[2],q);
    int o3 = orientation2(pole[2],pole[3],q);
    int o4 = orientation2(pole[3],pole[0],q);

    if (o1==o2&&o2==o3&&o3==o4)
        return true;
    else return false;

    return true;
}

bool Detector::doIntersect(Detector::detectorPoint p1, Detector::detectorPoint p2, Detector::detectorPoint q1, Detector::detectorPoint q2)
{
    int o1 = orientation(p1,q1,p2);
    int o2 = orientation(p1,q1,q2);
    int o3 = orientation(p2,q2,p1);
    int o4 = orientation(p2,q2,q1);
    if (o1 != o2 && o3 != o4)
        return true;
    else {
        return false;
    }
}

bool Detector::onSegment(Detector::detectorPoint p, Detector::detectorPoint q, Detector::detectorPoint r)
{
    auto ma = [](int x, int y)->int{return x>y?x:y;};
    auto min = [](int x, int y)->int{return x<y?x:y;};
    if ((q.h <= ma(p.h,r.h))&&(q.h>=min(p.h,q.h))&&(q.v<=ma(p.v,p.v))&&(q.v)>=min(p.v,r.v))
        return true;
    return  false;
}

int Detector::orientation(Detector::detectorPoint p, Detector::detectorPoint q, Detector::detectorPoint r)
{
    int val = qAbs((q.v - p.v)*(r.h - q.h)) - qAbs((q.h - p.h)*(r.v - q.v));
    if (val == 0)
        return 0;
    return (val>0)?1:2;
}

int Detector::orientation2(Detector::detectorPoint p, Detector::detectorPoint q, Detector::detectorPoint r)
{
    QVector2D v1(q.h-p.h,q.v-p.v); //q-p
    QVector2D v2(r.h-p.h,r.v-p.v); //r-p
    QVector2D v1y(-v1.y(),v1.x()); //orotovany vektor v1 o 90deg - nova baze
    float projekce2 = QVector2D::dotProduct(v1y,v2);
    if (projekce2 > 0)
        return 2;
    else if (projekce2 < 0)
        return 1;
    else
        return 0;
}

float Detector::rayWeightInPolygon(Detector::detectorPoint q, QVector<Detector::detectorPoint> &pole)
{
    float sum = 0;
    auto distance = [](const detectorPoint &p1,const detectorPoint &roh)->float{return qSqrt(((p1.h - roh.h)*(p1.h - roh.h) + (p1.v - roh.v)*(p1.v - roh.v)));};
    float d0 = distance(q,pole[0]);
    float d1 = distance(q,pole[1]);
    float d2 = distance(q,pole[2]);
    float d3 = distance(q,pole[3]);
    if (isEqual(d0,0))
        return pole[0].intensity;
    else if (isEqual(d1,0))
        return pole[1].intensity;
    else if (isEqual(d2,0))
        return pole[2].intensity;
    else if (isEqual(d3,0))
        return pole[3].intensity;
    else {
        float a0 = 1/d0;
        float a1 = 1/d1;
        float a2 = 1/d2;
        float a3 = 1/d3;
        sum = a0 + a1 + a2 + a3;
        float a = 1/sum;
        return pole[0].intensity*a0*a+ pole[1].intensity*a1*a+ pole[2].intensity*a2*a+ pole[3].intensity*a3*a;
    }
}
