#ifndef GEOMETRYDIALOG_H
#define GEOMETRYDIALOG_H

#include "source.h"

#include <QDialog>
#include <QVector>
#include <QVector3D>
#include <QKeyEvent>

namespace Ui {
class GeometryDialog;
}

class GeometryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeometryDialog(QWidget *parent = nullptr);
    virtual ~GeometryDialog() override;

    void keyPressEvent(QKeyEvent *) override;    

    void setSource(Source *source);

signals:
    /*
     * signal pointsRead() - emitted when points are succesfully read from txtEdit
     * */
    void pointsRead(QVector<QVector3D>&);
    void pointAndSourceRead(QVector3D&, QVector<QVector3D>&, Source*);
    void spreadPointsRead(QVector<QVector3D>&);

private slots:
    /*
     * void on_btn_OK_clicked() - reads points from dialog window and stores tem to *m_points
     * */
    void on_btn_OK_clicked();

    void on_btn_setSource_clicked();

private:
    Ui::GeometryDialog *ui;

    QVector3D m_startPoint;
    //calculates coordinates of point given by spread, based on previous point
    QVector<QVector3D> m_spreadPoints;
    QVector<QVector3D> m_points;

    Source *m_source;
    bool sourceIsSet = false;
};

#endif // GEOMETRYDIALOG_H
