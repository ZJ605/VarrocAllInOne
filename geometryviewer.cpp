#ifndef GEOMETRYVIEWER_H
#define GEOMETRYVIEWER_H

#include "geometryscene.h"
#include "geometryviewer.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QSizePolicy>

class GeometryViewer;

GeometryViewer::GeometryViewer(QWidget* parent):QWidget (parent)
{
    geomModel = new GeometryModel(this);
    geomScene = new GeometryScene();
    tracer = new Tracer();
    source = new Source();
    createLayout();

    connect(this, &GeometryViewer::geometryLoaded,geomScene,&GeometryScene::updateGeometry);
    connect(this, &GeometryViewer::sGeometryTransfromXYView,geomScene,&GeometryScene::geometryTransformXYView);
    //connect(this, &GeometryViewer::sGeometryChanged, geomModel, &GeometryModel::showDialog);
    connect(this, &GeometryViewer::sCreateParaboloid, geomModel, &GeometryModel::createParaboloid);
    connect(geomModel,&GeometryModel::geometryChanged,geomScene,&GeometryScene::geometryChanged2D);
    connect(source,&Source::sourceChanged,geomScene,&GeometryScene::sourceUpdated);
    connect(tracer,&Tracer::raysTraced,geomScene,&GeometryScene::geometryTraced);
}

GeometryViewer::~GeometryViewer()
{
    delete geomScene;
    delete geomModel;
    delete tracer;
    delete source;
}

Tracer* GeometryViewer::getTracer() const
{
    return tracer;
}

void GeometryViewer::load()
{
    QFileDialog dialog(this);
    dialog.setDirectory(QString("C:/Users/Ray/Program/C_Cxx/Program/models"));
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("*.ply"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    PlyReader reader(fileNames.first());
    qDebug()<<fileNames.first();
    if(reader.read()) {
            // reconstruct faces
            const QVector<PlyReader::ScenePoint> vertices = reader.vertices();
            const QVector<QVector<int>> faces = reader.faces();
            for(const QVector<int>& face: faces) {
                PlyReader::ScenePoint pt;
                for(int vertexId: face) {
                    const PlyReader::ScenePoint &scenePoint = vertices.at(vertexId);
                    pt.coord = scenePoint.coord;
                    pt.normal = scenePoint.normal;
                    m_data << pt;
                }
            }
        if (!m_data.isEmpty())
            emit geometryLoaded(m_data);
        else {
            qDebug()<<"data array is empty";
        }
    }
    else {
        qDebug()<<"reader didnt read";
    }
}

void GeometryViewer::save()
{
    qDebug()<<"save";
}

void GeometryViewer::close()
{
    //close();
}

void GeometryViewer::create()
{
    emit sGeometryChanged();
}

void GeometryViewer::geometryTransfromXYView()
{
    emit sGeometryTransfromXYView();
}

void GeometryViewer::tracerShow()
{
    tracer->show();
}

void GeometryViewer::sourceShow()
{
    source = new Source();
    source->show();
}

void GeometryViewer::tracerStart()
{
    if (source->getIsSet()){
        //qDebug()<<"if";
        //qDebug()<<geomModel->objects.first()->getPoints().count();
        tracer->trace(*geomModel->objects.first(),*source);

    }
}

void GeometryViewer::showTracedRays()
{

}

void GeometryViewer::createParaboloid()
{
    emit sCreateParaboloid();
}


void GeometryViewer::createLayout()
{
    horLayout = new QHBoxLayout();
    horLayout->setContentsMargins(2,2,2,2);
    horLayout->setSpacing(2);
    vertLayout = new QVBoxLayout();
    geomToolBar = new QToolBar(this);
    geomToolBar->setStyleSheet("QToolBar {border-bottom: 2px solid blue; border-top: 2px solid blue;border-left: 2px solid blue;border-right: 2px solid blue;}");
    geomTransformToolbar = new QToolBar(this);
    geomTransformToolbar->setStyleSheet("QToolBar {border-bottom: 2px solid blue; border-top: 2px solid blue;border-left: 2px solid blue;border-right: 2px solid blue;}");
    nurbToolbar = new QToolBar(this);
    nurbToolbar->setStyleSheet("QToolBar {border-bottom: 2px solid purple; border-top: 2px solid purple;border-left: 2px solid purple;border-right: 2px solid purple;}");
    traceToolBar = new QToolBar(this);
    traceToolBar->setStyleSheet("QToolBar {border-bottom: 2px solid grey; border-top: 2px solid grey;border-left: 2px solid grey;border-right: 2px solid grey;}");
    sourceToolBar = new QToolBar(this);
    sourceToolBar->setStyleSheet("QToolBar {border-bottom: 2px solid yellow; border-top: 2px solid yellow;border-left: 2px solid yellow;border-right: 2px solid yellow;}");
    //SAVE LOAD CLOSE
    {
    ActLoad = new QAction("Load", this);
    ActLoad->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
    ActLoad->setIconText("FFFFF");
    QIcon icon(":/GLoad.PNG");
    ActLoad->setIcon(icon);
    connect(ActLoad,SIGNAL(triggered()),this,SLOT(load()));
    geomToolBar->addAction(ActLoad);

    ActSave = new QAction("Save", this);
    ActSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    ActSave->setIconText("FFFFF");
    QIcon icon2(":/GSave.PNG");
    ActSave->setIcon(icon2);
    connect(ActSave,SIGNAL(triggered()),this,SLOT(save()));
    geomToolBar->addAction(ActSave);

    ActClose = new QAction("close", this);
    ActClose->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    ActClose->setIconText("FFFFF");
    QIcon icon3(":/GClose.PNG");
    ActClose->setIcon(icon3);
    connect(ActClose,SIGNAL(triggered()),this,SLOT(close()));
    geomToolBar->addAction(ActClose);

    ActCreate = new QAction("create", this);
    ActCreate->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    ActCreate->setIconText("FFFFF");
    QIcon iconCreate(":/GCreate.PNG");
    ActCreate->setIcon(iconCreate);
    connect(ActCreate,SIGNAL(triggered()),this,SLOT(createParaboloid()));
    geomToolBar->addAction(ActCreate);

    geomToolBar->setOrientation(Qt::Vertical);

    }
    //geomToolBar setting
    {
        ActTZView = new QAction("Z view", this);
        ActTZView->setIconText("FFFFF");
        QIcon icon(":/GTtransformXY.PNG");
        ActTZView->setIcon(icon);
        connect(ActTZView,SIGNAL(triggered()),this,SLOT(geometryTransfromXYView()));
        geomTransformToolbar->addAction(ActTZView);
/*
        ActTFitAllIn = new QAction("Z view", this);
        ActTFitAllIn->setIconText("FFFFF");
        QIcon icon1(":/GTtransformXY.PNG");
        ActTFitAllIn->setIcon(icon);
        connect(ActTFitAllIn,SIGNAL(triggered()),this,SLOT(geometryTransfromXYView()));
        geomTransformToolbar->addAction(ActTFitAllIn);
*/


        geomTransformToolbar->setOrientation(Qt::Vertical);
        geomTransformToolbar->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    }
    //nurbToolBar setting
    {
        ActNurb = new QAction("Nurb", this);
        ActNurb->setIconText("FFFFF");
        QIcon icon(":/NsetNurb.PNG");
        ActNurb->setIcon(icon);
        //connect(ActNurb,SIGNAL(triggered()),this,SLOT(setNurb()));
        nurbToolbar->addAction(ActNurb);

        nurbToolbar->setOrientation(Qt::Vertical);
    }
    //tracerToolBar setting
    {
        ActTracerShow = new QAction("Tracer", this);
        ActTracerShow->setIconText("Show Tracer");
        ActTracerShow->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT+Qt::Key_T));
        QIcon icon(":/TTracer.PNG");
        ActTracerShow->setIcon(icon);
        connect(ActTracerShow,SIGNAL(triggered()),this,SLOT(tracerShow()));
        traceToolBar->addAction(ActTracerShow);

        ActTracerStart = new QAction("Start tracing", this);
        ActTracerStart->setIconText("Start Tracer");
        ActTracerStart->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT+Qt::Key_S));
        QIcon icon1(":/TStart.PNG");
        ActTracerStart->setIcon(icon1);
        connect(ActTracerStart,SIGNAL(triggered()),this,SLOT(tracerStart()));
        traceToolBar->addAction(ActTracerStart);

        ActTShowRays = new QAction("Show rays", this);
        ActTShowRays->setIconText("Start Tracer");
        ActTShowRays->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT+Qt::Key_R));
        QIcon icon2(":/TRays.PNG");
        ActTShowRays->setIcon(icon2);
        connect(ActTShowRays,SIGNAL(triggered()),this,SLOT(showTracedRays()));
        traceToolBar->addAction(ActTShowRays);

        traceToolBar->setOrientation(Qt::Vertical);
    }
    //sourceToolBar setting
    {
        ActSShow = new QAction("Source", this);
        ActSShow->setIconText("Set source");
        ActSShow->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT+ Qt::Key_S));
        QIcon icon(":/SSource.PNG");
        ActSShow->setIcon(icon);
        connect(ActSShow,SIGNAL(triggered()),this,SLOT(sourceShow()));
        sourceToolBar->addAction(ActSShow);

        sourceToolBar->setOrientation(Qt::Vertical);
    }
    vertLayout->addWidget(geomToolBar,0);
    vertLayout->addWidget(nurbToolbar,0);
    vertLayout->addWidget(geomTransformToolbar,0);
    vertLayout->addWidget(traceToolBar,0);
    vertLayout->addWidget(sourceToolBar,0);
    horLayout->addLayout(vertLayout);
    geomScene->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    horLayout->addWidget(geomScene);
    this->setLayout(horLayout);
}
#endif // GEOMETRYVIEWER_H

