#ifndef LAYER_H
#define LAYER_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include "neuron.h"
#include "matrix.h"

class Layer
{
public:
    Layer(int size);

    Matrix *matrixifyVals();
    Matrix *matrixifyActivatedVals();
    Matrix *matrixifyDerivedVals();

    void setValue(QVector<double> input);
    ///!
    //! \brief getValue - returns value of neuron at index position
    //! \param index
    //! \return
    //!
    Neuron* getNeuron(int index);

    int getSize() const;

private:
    int size;
    QVector<Neuron *> neurons;
};

#endif // LAYER_H
