#include "layer.h"

Layer::Layer(int size):size(size)
{
    for (int i = 0; i<size;i++){
        Neuron *n = new Neuron(1);
        neurons.append(n);
    }
}

Matrix *Layer::matrixifyVals()
{
    Matrix *m = new Matrix(1,neurons.count(),false);
    for (int i = 0; i<neurons.count(); i++){
        m->setValue(0,i,neurons.at(i)->getVal());
        //qDebug()<<"matrixif at i"<<m->getValue(0,i);
    }
    return m;
}

Matrix *Layer::matrixifyActivatedVals()
{
    Matrix *m = new Matrix(1,neurons.count(),false);
    for (int i = 0; i<neurons.count(); i++){
        m->setValue(0,i,neurons.at(i)->getActivatedVal());
    }
    return  m;
}

Matrix *Layer::matrixifyDerivedVals()
{
    Matrix *m = new Matrix(1,neurons.count(),false);
    for (int i = 0; i<neurons.count(); i++){
        m->setValue(0,i,neurons.at(i)->getDerivatedVal());
    }
    return m;
}

void Layer::setValue(QVector<double> input)
{
    if (neurons.count()!=input.count()){
        qDebug()<<"input size doesnt match layer size in layer.setvalue()";
        return;
    }
    for (int i = 0; i< input.count(); i++){
        neurons.at(i)->setVal(input.at(i));
    }
}

Neuron* Layer::getNeuron(int index)
{
    return neurons[index];
}

int Layer::getSize() const
{
    return size;
}
