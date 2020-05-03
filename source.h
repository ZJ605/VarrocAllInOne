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
    Source (QWidget *parent, float x, float z);
    Source& operator=(const Source s);
    ~Source() override;

    float getChipSizeX() const {return chipSizeX;}
    float getChipSizeZ() const {return chipSizeZ;}
    bool getIsSet() const;
    QVector3D getSourcePosition() const;

signals:
    void sourceChanged(QVector<float> v);

private slots:

    void on_btn_OK_clicked();
    void showEvent(QShowEvent *) override;

private:
    Ui::Source *ui;

    float chipSizeX;
    float chipSizeZ;
    QVector3D sourcePosition;
    bool isSet = false;

    void generateRays();

    //Point sourcePosition;

    QVector<float> sourceFloatVector;
    QVector<Ray> sourceRays;

};

#endif // SOURCE_H
