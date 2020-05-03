#include "mainwindow.h"
#include <QTabWidget>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupLayout();
    setupToolbars();

    connect(geomViewer, &GeometryViewer::geometryTraced, detector, &Detector::projectChipOnDetector);
}

MainWindow::~MainWindow()
{
    delete geomViewer;
}

void MainWindow::setupLayout()
{
    setGeometry(Qt::LeftToRight, Qt::AlignCenter, 800,600);

    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setGeometry(this->rect());

    geomViewer = new GeometryViewer();
    const QString name = "geometry";
    int geomindex = tabWidget->addTab(geomViewer,name);
    this->setCentralWidget(tabWidget);

    detector = new Detector(this);
    const QString name2 = "detector";
    int detindex = tabWidget->addTab(detector, name2);
    tabWidget->setCurrentIndex(detindex);
    //tabWidget->setCurrentIndex(geomindex);
}

void MainWindow::setupMenuBar()
{

}

void MainWindow::setupToolbars()
{

}

void MainWindow::setupStatusBar()
{

}


