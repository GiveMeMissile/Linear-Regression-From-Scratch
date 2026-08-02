#pragma once

#include <vector>
#include <iostream>

class Matrix{
    private:

        void cofactorMatrix();

        Matrix calculateMatrixOfMinors();

        bool checkIfCanMultiply(int rowSize);

        bool isSquare();

        bool isTwoByTwo();

    protected:

        std::vector<std::vector<double>> matrix;

        Matrix partitionMatrix(int colIdx, int rowIdx);

    public:
        Matrix();

        Matrix(std::vector<std::vector<double>> *matrix);

        Matrix(std::vector<std::vector<double>> matrix);

        Matrix(std::vector<double> vector);

        void multiply(double value);

        static double dotProduct(const std::vector<double> *a, const std::vector<double> *b);

        Matrix transpose();

        const std::vector<std::vector<double>>* getMatrix();

        double calculateDeterminat();

        Matrix matrixMultiplication(Matrix* matrixB);

        Matrix invertMatrix();

        std::vector<double> getColumn(int index);

        void printMatrix();

        int getRowLength();

        int getColumnLength();
};