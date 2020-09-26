#include "matrix.h"

Matrix::Matrix(int rows, int cols, bool random):numRows(rows), numCols(cols),isRandom(random)
{
    for (int i = 0; i<numRows; i++){
        QVector<double> rowvalues;
        for (int j = 0; j<numCols; j++){
            double r = 0.0;
            if (isRandom)
                r = generateRandomNumber();
            rowvalues.append(r);
        }
        values.append(rowvalues);
    }
}

Matrix::Matrix(const Matrix &a):numRows(a.getNumRows()), numCols(a.getNumCols())
{
    for (int i = 0; i<numRows; i++){
        QVector<double> rowvalues;
        for (int j = 0; j<numCols; j++){
            double r = a.getValue(i,j);
            rowvalues.append(r);
        }
        values.append(rowvalues);
    }
}

Matrix *Matrix::transpose()
{
    Matrix *m = new Matrix(numCols,numRows,false);
    for (int i = 0; i<numRows; i++){
        for (int j = 0; j<numCols; j++){
            m->setValue(j,i, getValue(i,j));
        }
    }
    return m;
}

double Matrix::generateRandomNumber()
{
    return QRandomGenerator::global()->generateDouble();
}

void Matrix::setValue(int r, int c, double value)
{
    values[r][c] = value;
}

double Matrix::getValue(int r, int c) const
{
    return  values[r][c];
}

void Matrix::printToConsole()
{
    for (int i = 0; i<numRows; i++){
        qDebug()<<values.at(i);
    }
}

Matrix *Matrix::operator*(const Matrix &b)
{
    int br = b.getNumRows();
    int bc = b.getNumCols();
    int ar = getNumRows();
    int ac = getNumCols();

    if (ac!=br){
        qDebug()<<"matrix's dimensions dont match in matrix multiplication";
        return new Matrix(0,0,false);
    }
    Matrix *m = new Matrix(ar, bc, false);
    for (int i = 0; i < ar; i++)
        for (int j = 0; j< bc; j++){
            double x = 0;
            for (int k = 0; k < ac; k++)
                x+=getValue(i,k) * b.getValue(k,j);
            m->setValue(i,j,x);
        }
    return m;
}

Matrix *Matrix::operator*(Matrix *a)
{
    numRows = a->getNumRows();
    numCols = a->getNumCols();
    isRandom = a->getIsRandom();
    for (int i = 0; i<numRows; i++){
        QVector<double> rowvalues;
        for (int j = 0; j<numCols; j++){
            double r = a->getValue(i,j);
            rowvalues.append(r);
        }
        values.append(rowvalues);
    }
    return this;
}

Matrix *Matrix::operator*(double a)
{
    Matrix *m = new Matrix(getNumRows(), getNumCols(), false);
    for (int i = 0; i < getNumRows(); i++)
        for (int j = 0; j< getNumCols(); j++){
            m->setValue(i,j,getValue(i,j)*a);
        }
    return m;
}

Matrix *Matrix::operator=(const Matrix &a)
{
    numRows = a.getNumRows();
    numCols = a.getNumCols();
    isRandom = a.getIsRandom();
    for (int i = 0; i<numRows; i++){
        QVector<double> rowvalues;
        for (int j = 0; j<numCols; j++){
            double r = a.getValue(i,j);
            rowvalues.append(r);
        }
        values.append(rowvalues);
    }
    return this;
}

Matrix *Matrix::operator+(const Matrix &a)
{
    if (a.getNumRows()!=numRows || a.getNumCols()!=numCols){
        qDebug()<<"matrixes must be of same dimensions for addition";
        Matrix *m = nullptr;
        return m;
    }
    Matrix *m = new Matrix(numRows,numCols,false);
    for (int i = 0; i<numRows; i++){
        for (int j = 0; j<numCols; j++){
            double r = a.getValue(i,j)+getValue(i,j);
            m->setValue(i,j,r);
        }
    }
    return m;
}

Matrix *Matrix::operator-(const Matrix &a)
{
    if (a.getNumRows()!=numRows || a.getNumCols()!=numCols){
        qDebug()<<"matrixes must be of same dimensions for addition";
        Matrix *m = nullptr;
        return m;
    }
    Matrix *m = new Matrix(numRows,numCols,false);
    for (int i = 0; i<numRows; i++){
        for (int j = 0; j<numCols; j++){
            double r = getValue(i,j)-a.getValue(i,j);
            m->setValue(i,j,r);
        }
    }
    return m;
}

Matrix *Matrix::operator/(const Matrix &in)
{
    if (getNumRows()!=1||in.getNumRows()!=1||getNumCols()!=in.getNumCols()){
        qDebug()<<"matrix sizes doesnt match. Dot product is ipossible";
        Matrix *m = nullptr;
        return m;
    }
    Matrix *m = new Matrix(1,getNumCols(),false);
    for (int i = 0; i<getNumCols(); i++){
        m->setValue(0,i,getValue(0,i)*in.getValue(0,i));
    }
    return  m;
}

int Matrix::getNumRows() const
{
    return numRows;
}

void Matrix::setNumRows(int value)
{
    numRows = value;
}

int Matrix::getNumCols() const
{
    return numCols;
}

void Matrix::setNumCols(int value)
{
    numCols = value;
}

bool Matrix::getIsRandom() const
{
    return isRandom;
}
