#include "geometrymodel.h"
#include "plyreader.h"
#include "tracer.h"
#include "source.h"
#include <QObject>
#include <QOpenGLWidget>
#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QHBoxLayout>
#include <QGroupBox>

class GeometryScene;

class GeometryViewer:public QWidget
{
    Q_OBJECT
public:
    GeometryViewer(QWidget* parent = nullptr);
    virtual ~GeometryViewer();

    GeometryModel *geomModel;
    GeometryScene *geomScene;
    Tracer* tracer;
    Source* source;

    QHBoxLayout *horLayout;
    QVBoxLayout *vertLayout;

    QToolBar *geomToolBar;
    QToolBar *geomTransformToolbar;
    QToolBar *nurbToolbar;
    QToolBar *traceToolBar;
    QToolBar *sourceToolBar;

    QAction *ActLoad;
    QAction *ActSave;
    QAction *ActClose;
    QAction *ActCreate;

    QAction *ActTZView;
    QAction *ActTFitAllIn;

    QAction *ActNurb;

    QAction *ActTracerShow;
    QAction *ActTracerStart;
    QAction *ActTShowRays;

    QAction *ActSShow;

    Tracer *getTracer() const;

signals:
    void geometryLoaded(QVector<PlyReader::ScenePoint>& data);
    void sGeometryTransfromXYView();
    void sGeometryChanged();
    void sCreateParaboloid();


public slots:
    void load();
    void save();
    void close();
    void create();
    void geometryTransfromXYView();
    void tracerShow();
    void sourceShow();
    void tracerStart();
    void showTracedRays();
    void createParaboloid();

private:
    QVector<PlyReader::ScenePoint> m_data;
    //QList<QVector<QVector3D>*> m_Data2D;
    QVector<QVector3D> m_Data2D;

    void createLayout();

};


