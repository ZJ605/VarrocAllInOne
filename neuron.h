#ifndef NEURON_H
#define NEURON_H

#include <QObject>
#include <QtMath>
#include <QDebug>

class Neuron
{
public:
    Neuron(double val);
    //fast sigmoid func f(x)=x/(1+abs(x))
    void activate();
    //derive sigmoid func. f'(x) = f(x)*(1-f(x))
    void derive();

    double getVal() const;

    double getActivatedVal() const;

    double getDerivatedVal() const;

    void setVal(double value);

private:
    double Val = 0;
    double activatedVal = 0;
    double derivatedVal = 0;
};

#endif // NEURON_H
