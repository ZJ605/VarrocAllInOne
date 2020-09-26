#ifndef MATRIX_H
#define MATRIX_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>

class Matrix
{
public:
    Matrix(int rows, int cols, bool random);
    Matrix(const Matrix& a);
    Matrix *operator*(const Matrix& a);
    Matrix *operator*(Matrix* a);
    Matrix *operator*(double a);
    Matrix *operator=(const Matrix& a);
    Matrix *operator+(const Matrix& a);
    Matrix *operator-(const Matrix& a);
    Matrix *operator/(const Matrix&); //element by element multiplication

    Matrix *transpose();
    double generateRandomNumber();
    void setValue(int r, int c, double value);
    double getValue(int r, int c) const;
    void printToConsole();

    int getNumRows() const;

    void setNumRows(int value);

    int getNumCols() const;
    void setNumCols(int value);

    bool getIsRandom() const;

private:
    int numRows;
    int numCols;
    bool isRandom;

    QVector<QVector<double> > values;
};

#endif // MATRIX_H
