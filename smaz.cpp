#include "smaz.h"
#include <QDebug>
smaz::smaz()
{

}

void smaz::test(const QVector<QVector3D> &a)
{
    qDebug()<<"a: "<<a.first();
}
