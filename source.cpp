#include "source.h"
#include "ui_source.h"

Source::Source(QWidget *parent) :
    sourcePosition(Point()),sourceDirection1(QVector3D(0,0,0)),sourceDirection2(QVector3D(0,0,0)),QDialog(parent),
    ui(new Ui::Source)
{
    ui->setupUi(this);
}

Source::~Source()
{
    delete ui;
}

Source::Source(const Source &s)
{
    sourcePosition = s.sourcePosition;
    sourceSize1 = s.sourceSize1;
    sourceSize2 = s.sourceSize2;
    sourceNormal = s.sourceNormal;
    sourceDirection1 = s.sourceDirection1;
    sourceDirection2 = s.sourceDirection2;
}

Source &Source::operator =(const Source &s)
{
    sourcePosition = s.sourcePosition;
    sourceSize1 = s.sourceSize1;
    sourceSize2 = s.sourceSize2;
    sourceNormal = s.sourceNormal;
    sourceDirection1 = s.sourceDirection1;
    sourceDirection2 = s.sourceDirection2;
    return *this;
}

void Source::on_btn_OK_clicked()
{
    sourcePosition.setPoint(QVector3D(ui->ln_PosX->text().toFloat(),ui->ln_PosY->text().toFloat(),ui->ln_PosZ->text().toFloat()));
    QString dir1=ui->ln_Dir1->text();
    if (dir1.split(" ").count()>2){
        QVector3D pom;
        pom.setX(dir1.split(" ")[0].toFloat());
        pom.setY(dir1.split(" ")[1].toFloat());
        pom.setZ(dir1.split(" ")[2].toFloat());
        sourceDirection1 = pom.normalized();
    }

    QString dir2=ui->ln_Dir2->text();
    if (dir2.split(" ").count()>2){
        QVector3D pom;
        pom.setX(dir2.split(" ")[0].toFloat());
        pom.setY(dir2.split(" ")[1].toFloat());
        pom.setZ(dir2.split(" ")[2].toFloat());
        sourceDirection2 = pom.normalized();
    }
    sourceNormal = QVector3D::crossProduct(sourceDirection1,sourceDirection2).normalized();

    sourceSize1 = ui->ln_Size1->text().toFloat();
    //qDebug()<<"source size 1 in source: "<<sourceSize1;
    sourceSize2 = ui->ln_Size2->text().toFloat();
    QVector3D pom0(sourcePosition.getPoint().x()+sourceDirection1.x()*sourceSize1/2.0f-sourceDirection2.x()*sourceSize2/2.0f,
                   sourcePosition.getPoint().y()+sourceDirection1.y()*sourceSize1/2.0f-sourceDirection2.y()*sourceSize2/2.0f,
                   sourcePosition.getPoint().z()+sourceDirection1.z()*sourceSize1/2.0f-sourceDirection2.z()*sourceSize2/2.0f);

    QVector3D pom1(pom0.x()-sourceDirection2.x()*sourceSize2,
                   pom0.y()-sourceDirection2.y()*sourceSize2,
                   pom0.z()-sourceDirection2.z()*sourceSize2);
    QVector3D pom2(pom1.x()-sourceDirection1.x()*sourceSize1,
                   pom1.y()-sourceDirection1.y()*sourceSize1,
                   pom1.z()-sourceDirection1.z()*sourceSize1);
    QVector3D pom3(pom2.x()+sourceDirection2.x()*sourceSize2,
                   pom2.y()+sourceDirection2.y()*sourceSize2,
                   pom2.z()+sourceDirection2.z()*sourceSize2);

    sourceFloatVector.append(pom0.x());
    sourceFloatVector.append(pom0.y());
    sourceFloatVector.append(pom0.z());
    sourceFloatVector.append(pom1.x());
    sourceFloatVector.append(pom1.y());
    sourceFloatVector.append(pom1.z());
    sourceFloatVector.append(pom2.x());
    sourceFloatVector.append(pom2.y());
    sourceFloatVector.append(pom2.z());
    sourceFloatVector.append(pom3.x());
    sourceFloatVector.append(pom3.y());
    sourceFloatVector.append(pom3.z());
    sourceFloatVector.append(pom0.x());
    sourceFloatVector.append(pom0.y());
    sourceFloatVector.append(pom0.z());

    isSet = true;

    emit sourceChanged(sourceFloatVector);

    close();
}

void Source::showEvent(QShowEvent *)
{
    ui->ln_PosX->text()= QString::number(sourcePosition.getPoint().x());
    ui->ln_PosY->text()= QString::number(sourcePosition.getPoint().y());
    ui->ln_PosZ->text()= QString::number(sourcePosition.getPoint().z());
    ui->ln_Dir1->text()=QString::number(sourceDirection1.x())+QString::number(sourceDirection1.y())+QString::number(sourceDirection1.z());
    ui->ln_Dir2->text()=QString::number(sourceDirection2.x())+QString::number(sourceDirection2.y())+QString::number(sourceDirection2.z());
}

void Source::generateRays()
{
    int rayNmr = 50;
    for (int i=0;i<rayNmr;i++) {

    }
}

float Source::getSourceSize2() const
{
    return sourceSize2;
}

float Source::getSourceSize1() const
{
    return sourceSize1;
}

void Source::setSourceNormal(const QVector3D &value)
{
    sourceNormal = value;
}

QVector3D Source::getSourceDirection2() const
{
    return sourceDirection2;
}

void Source::setSourceDirection2(const QVector3D &value)
{
    sourceDirection2 = value;
}

QVector3D Source::getSourceDirection1() const
{
    return sourceDirection1;
}

void Source::setSourceDirection1(const QVector3D &value)
{
    sourceDirection1 = value;
}

void Source::setSourcePosition(const Point &value)
{
    sourcePosition = value;
}

QVector3D Source::getSourceNormal() const
{
    return sourceNormal;
}

Point Source::getSourcePosition() const
{
    return sourcePosition;
}

bool Source::getIsSet() const
{
    return isSet;
}
