#include "neuron.h"

Neuron::Neuron(double val):Val(val)
{
    activate();
    derive();
}

void Neuron::activate()
{
    activatedVal = 1/(1+qExp(-Val));
}

void Neuron::derive()
{
    derivatedVal = activatedVal*(1-activatedVal);
}

double Neuron::getVal() const
{
    return Val;
}

double Neuron::getActivatedVal() const
{
    return activatedVal;
}

double Neuron::getDerivatedVal() const
{
    return derivatedVal;
}

void Neuron::setVal(double value)
{
    Val = value;
    activate();
    derive();
}
