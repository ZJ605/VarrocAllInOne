#include "geometrydialog.h"
#include "ui_geometrydialog.h"
#include <QDebug>
#include <QMessageBox>
#include <qevent.h>
GeometryDialog::GeometryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeometryDialog)
{
    ui->setupUi(this);
    ui->btn_OK->setFocus();
    //ui->txtEdit->setText("-0.2 -0.5 0.0 0.5 0.5 0.0 -0.1 0.3 0.0");
    //ui->txtEdit->setText("-0.2 -0.5 0.0 0.5 0.5 0.0 -0.1 0.3 0.0 -0.2 0.5 0.0 -2.0 2.0 0.0");
    //ui->txtEdit->setText("-1.0 -1.0 0.0 1.0 -1.0 0.0 0.0 1.0 0.0");
    //ui->txtEdit->setText("-1.9 -1.9 0.0 0.9 -0.9 0.0 0.0 0.9 0.0");
    //ui->txtEdit->setText("-0.9 -0.9 0.0 0.9 -0.9 0.0 0.0 0.9 0.0");
    //ui->txtEdit->setText("-0.9 -0.9 0.0 -0.7 -0.8 0.0 -0.5 -0.5 0.0 0.0 0.0 0.0 0.2 0.4 0.0 0.4 0.7 0.0 0.5 0.8 0.0 0.9 0.9 0.0");
    //ui->txtEdit->setText("-0.9 -0.9 0.0 -0.7 -0.8 0.0 -0.5 -0.5 0.0 0.0 0.0 0.0 0.2 0.4 0.0 0.4 0.7 0.0 0.5 0.8 0");
    //ui->txtEdit->setText("-15.0 -0.0 0.0 -13.0 -10.0 0.0 -10.0 -0.5 0.0 0.0 0.0 0.0 0.2 0.4 0.0 0.4 0.7 0.0 0.5 0.8 0");
    ui->txtEdit->setText("-15.0 -0.0 0.0 -14.0 -7.75 0.0 -13.0 -10.95 0.0 -12.0 -13.41 0.0 -11.0 -15.49 0.0 -10.0 -17.32 0.0 -9.0 -18.97 0 -8.0 -20.49 0.0");
    ui->txtEdit_spread->setText("0  0\n-5 -0\n-10 -2\n-15 -1\n-20 -0.5\n-30 -0\n-40 -0\n-50 -0");
    ui->ln_startPoint->setText("15 0 0");
}

GeometryDialog::~GeometryDialog()
{
    delete ui;
}

void GeometryDialog::keyPressEvent(QKeyEvent *ev)
{
    //qDebug()<<ev->key();
    if (ev->key()==Qt::Key_Enter)
        on_btn_OK_clicked();
}

void GeometryDialog::on_btn_OK_clicked()
{
    {
    QStringList startPoint = ui->ln_startPoint->text().split(" ");
    qDebug()<<"obsah"<<ui->txtEdit->toPlainText();
    m_startPoint.setX(startPoint[0].toFloat());
    m_startPoint.setY(startPoint[1].toFloat());
    m_startPoint.setZ(startPoint[2].toFloat());
    }
    QStringList list = ui->txtEdit->toPlainText().split(" ");
    if (list.count()%3==0){
        for(int i=0;i<list.count();i++) {
            float x = list.at(i).toFloat();
            float y = list.at(++i).toFloat();
            float z = list.at(++i).toFloat();
            QVector3D point(x,y,z);
            m_points.append(point);
            //qDebug()<<"point in dialog"<<point;

            //emit pointsRead(m_points);
        }

    }
    QStringList listSpread = ui->txtEdit_spread->toPlainText().split("\n");
        if (true){
            //m_points.append(m_startPoint);
            for (int i = 0;i<listSpread.count();i++){
                QVector3D p(listSpread.at(i).split(" ").at(0).toFloat(),listSpread.at(i).split(" ").at(1).toFloat(),0);
                m_spreadPoints.append(p);
            }

        }
    //qDebug()<<m_inputPoints;    

    if (m_source){
        emit pointAndSourceRead(m_startPoint, m_points, m_source);
        close();
    }

    else {
        QMessageBox* mb = new QMessageBox();
        mb->setText("source must be set");
        mb->show();
    }

}

void GeometryDialog::setSource(Source *source)
{
    m_source = source;
    sourceIsSet = true;
}


void GeometryDialog::on_btn_setSource_clicked()
{
    m_source = new Source();
    m_source->show();

}
