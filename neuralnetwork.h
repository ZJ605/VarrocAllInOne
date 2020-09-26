#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QtMath>
#include <QFile>
#include <QTextStream>
#include "matrix.h"
#include "layer.h"
//#include "json.hpp"

class NeuralNetwork
{
public:
    NeuralNetwork(QVector<int> tplgy); //first number indicates number of inputs; next numbers number of neurons in next layers, last number indicates number of outputs
    NeuralNetwork();
    void setCurrentInput(QVector<double> inpt);
    void setCurrentTarget(QVector<double> inpt);
    void printToConsole();
    void feedForward();
    void backPropagation();
    void updateErrors();
    void printError();
    void printLastLayer();
    void printErrorHistory();
    void exportNN();
    void importNN();

private:
    QVector<int> topology;
    QVector<Layer *> layers;
    QVector<Matrix *> weightMatrixes;
    QVector<Matrix *> gradientMatrixes; //first element coressponds to last error*derivative of last layer
    QVector<double> input;
    QVector<double> target;
    QVector<double> errors;
    double error;
    QVector<double> errorHistory;
    double step = 20;
    QVector<double> steps;

    bool neuralNetworkIsSet = false;

    void updateOutput();
};

#endif // NEURALNETWORK_H
