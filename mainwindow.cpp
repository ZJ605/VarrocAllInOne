#include "mainwindow.h"
#include <QTabWidget>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupLayout();
    setupToolbars();

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
    tabWidget->addTab(geomViewer,name);
    this->setCentralWidget(tabWidget);

    detector = new Detector(geomViewer->getTracer());
    const QString name2 = "detector";
    tabWidget->addTab(detector, name2);
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


