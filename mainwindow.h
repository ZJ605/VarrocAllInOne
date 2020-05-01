#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "geometryviewer.h"
#include "detector.h"
#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:    
    void setupLayout();
    void setupMenuBar();
    void setupToolbars();
    void setupStatusBar();
    GeometryViewer *geomViewer;
    Detector* detector;

};

#endif // MAINWINDOW_H
