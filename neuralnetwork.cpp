#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(QVector<int> tplgy)
{
    topology = tplgy;
    //first layer is initialized with added bias at position (0) of input vector
    Layer *l0 = new Layer(topology.at(0)+1);
    Matrix *n0 = new Matrix(1,topology.at(0)+1, true);
    layers.append(l0);
    gradientMatrixes.append(n0);
    Matrix *m0 = new Matrix(topology.at(0)+1,topology.at(1), true);
    weightMatrixes.append(m0);
    steps.append(0);

    for (int i = 1; i<topology.size(); i++){
        Layer *l = new Layer(topology.at(i));
        Matrix *n = new Matrix(1,topology.at(i), true);
        layers.append(l);
        gradientMatrixes.append(n);
        steps.append(0);
    }
    for (int i = 1; i < topology.size()-1; i++){
        Matrix *m = new Matrix(topology.at(i),topology.at(i+1), true);
        weightMatrixes.append(m);

    }
    neuralNetworkIsSet = true;

}

NeuralNetwork::NeuralNetwork()
{

}

void NeuralNetwork::setCurrentInput(QVector<double> inpt)
{
    QVector<double> vec;
    vec.append(1);
    for (int i = 0; i < inpt.count();i++){
        vec.append(inpt.at(i));
    }
    input = vec;
    layers.at(0)->setValue(input);
}

void NeuralNetwork::setCurrentTarget(QVector<double> inpt)
{
    target = inpt;
    //initialize error vector
    if (target.count()!=layers.last()->matrixifyActivatedVals()->getNumCols()){
        qDebug()<<"result length doesnt match output layer neurons count";
        return;
    }
    if (errors.count()==0)
        for (int i = 0; i<inpt.count(); i++){
            errors.append(0);
        }
    else
        for (int i = 0; i<inpt.count(); i++){
            errors[i]=0;
        }
}

void NeuralNetwork::printToConsole()
{
    for (int i = 0; i<layers.count();i++){
        qDebug()<<"layer"<<i;
        if (i==0){
            Matrix *m = layers.at(i)->matrixifyVals();
            m->printToConsole();
        }
        else {
            Matrix *m = layers.at(i)->matrixifyActivatedVals();
            m->printToConsole();
        }
    }
    for (int i = 0; i < weightMatrixes.count(); i++){
        qDebug()<<"Matrix"<<i;
        weightMatrixes.at(i)->printToConsole();
    }
    qDebug()<<"input:"<<input;
    qDebug()<<"target:"<<target;
    qDebug()<<"error:"<<error;
    qDebug()<<"";
    //qDebug()<<"gradient matrix";
    //gradientMatrixes.at(0)->printToConsole();
}

void NeuralNetwork::feedForward()
{
    //qDebug()<<"FF start--------------------------";
    for (int i = 0; (i<layers.count()-1);i++){
        Matrix *a;
        if (i==0)
            a = layers.at(i)->matrixifyVals();
        else
            a = layers.at(i)->matrixifyActivatedVals();
        Matrix *b = weightMatrixes.at(i);
        Matrix *c = (*a)*(*b);
        //qDebug()<<"c";
        //c->printToConsole();
        QVector<double> vec;
        for (int i = 0; i < c->getNumCols(); i++)
            vec.append(c->getValue(0,i));
        //qDebug()<<vec;
        layers.at(i+1)->setValue(vec);
    }
    //layers.last()->matrixifyActivatedVals()->printToConsole();
    updateErrors();
    //qDebug()<<"FF end--------------------------";
}

void NeuralNetwork::backPropagation()
{
    //qDebug()<<"BP start--------------------------";
    //ouput layer to first hidden layer
    int lastLayerIndex = layers.count()-1;
    Matrix *m = new Matrix(1,errors.count(),false);
    for (int i = 0; i < errors.count(); i++){
        double e = errors.at(i);
        double d = layers.at(lastLayerIndex)->getNeuron(i)->getDerivatedVal();
        m->setValue(0,i,e*d);
        gradientMatrixes[0] = m;
    }

    Matrix *deltaWeightMat = (*layers.at(lastLayerIndex-1)->matrixifyActivatedVals()->transpose())*(*m);
    weightMatrixes[lastLayerIndex-1]=(*weightMatrixes.at(lastLayerIndex-1))+*((*deltaWeightMat)*step);

    //hidden to input layers
    for (int i = lastLayerIndex-1; i>0; i--){
        //qDebug()<<"index"<<i;
        //qDebug()<<"grad";
        //gradientMatrixes.at(lastLayerIndex-i-1)->printToConsole();
        //qDebug()<<"weight";
        //weightMatrixes.at(i)->printToConsole();
        Matrix *mpom = (*weightMatrixes.at(i))*(*gradientMatrixes.at(lastLayerIndex-i-1)->transpose());
        //qDebug()<<"mpom";
        //mpom->printToConsole();
        int size = layers.at(i)->getSize();
        //qDebug()<<"size"<<size;
        Matrix *gradientMatrixHidden = new Matrix(1,size,false);
        for (int j = 0; j < size; j++){
            double d = layers.at(i)->getNeuron(j)->getDerivatedVal();
            gradientMatrixHidden->setValue(0,j,d*mpom->getValue(j,0));
        }
        //qDebug()<<"gradient matri hidden";
        gradientMatrixes[lastLayerIndex-i] = gradientMatrixHidden;
        //gradientMatrixes[lastLayerIndex-i]->printToConsole();
        //CHYBA
        Matrix *deltaWeightMatHidden = (*layers.at(i-1)->matrixifyActivatedVals()->transpose())*(*gradientMatrixHidden);
        //qDebug()<<"weight";
        //weightMatrixes[i-1]->printToConsole();
        //qDebug()<<"delta weight";
        //deltaWeightMatHidden->printToConsole();
        weightMatrixes[i-1]=(*weightMatrixes.at(i-1))+*((*deltaWeightMatHidden)*step);
    }
}

void NeuralNetwork::updateErrors()
{
    error = 0;
    for (int i = 0; i < target.count(); i++){
        double r = target.at(i)-layers.last()->matrixifyActivatedVals()->getValue(0,i);
        errors[i]=r;
        r*=r;
        error += r;
        errorHistory.append(error);
    }

}

void NeuralNetwork::printError()
{
    qDebug()<<"error:"<<error;
}

void NeuralNetwork::printLastLayer()
{
    layers.last()->matrixifyActivatedVals()->printToConsole();
}

void NeuralNetwork::printErrorHistory()
{
    qDebug()<<errorHistory;
}

void NeuralNetwork::exportNN()
{
    QFile file("nn.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    for (int i = 0; i< topology.count();i++){
        out << topology.at(i)<<" ";
    }
    out << "\n";
    for (int i = 0; i < weightMatrixes.count();i++){
        for (int j = 0; j < weightMatrixes.at(i)->getNumRows();j++){
            for (int k = 0; k < weightMatrixes.at(i)->getNumCols();k++){
                out << weightMatrixes.at(i)->getValue(j,k)<<" ";
            }
            out << "\n";
        }
    }
}

void NeuralNetwork::importNN()
{
    if (neuralNetworkIsSet){
        qDebug()<<"neural network is already set";
        return;
    }
    QFile file("nn.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);

    QStringList tplgylist = in.readLine(0).split(" ");
    for (int i = 0; i < tplgylist.count()-1; i++){
        topology.append(tplgylist.at(i).toInt());
    }

    Layer *l0 = new Layer(topology.at(0)+1);
    Matrix *n0 = new Matrix(1,topology.at(0)+1, true);
    layers.append(l0);
    gradientMatrixes.append(n0);
    Matrix *m0 = new Matrix(topology.at(0)+1,topology.at(1), true);
    weightMatrixes.append(m0);
    steps.append(0);

    for (int i = 1; i<topology.size(); i++){
        Layer *l = new Layer(topology.at(i));
        Matrix *n = new Matrix(1,topology.at(i), true);
        layers.append(l);
        gradientMatrixes.append(n);
        steps.append(0);
    }
    for (int i = 1; i < topology.size()-1; i++){
        Matrix *m = new Matrix(topology.at(i),topology.at(i+1), true);
        weightMatrixes.append(m);
    }
    for (int i = 0; i < weightMatrixes.count();i++){
        for (int j = 0; j < weightMatrixes.at(i)->getNumRows();j++){
            QStringList list = in.readLine(0).split(" ");
            for (int k = 0; k < weightMatrixes.at(i)->getNumCols();k++){
                weightMatrixes.at(i)->setValue(j,k,list.at(k).toDouble());
            }
        }
    }
    neuralNetworkIsSet = true;

}

void NeuralNetwork::updateOutput()
{

}
