#pragma once

#include <vector>
#include <iostream>

class Matrix{
    private:
        std::vector<std::vector<double>> matrix;

        Matrix getMiniMatrix(int colIdx, int rowIdx);

        bool checkIfCanMultiply(int rowSize);

        bool isSquare();

        bool isTwoByTwo();

    public:
        static double dotProduct(const std::vector<double> *a, const std::vector<double> *b);

        Matrix(std::vector<std::vector<double>> *matrix);

        Matrix transpose();

        const std::vector<std::vector<double>>* getMatrix();

        double calculateDeterminate();

        Matrix matrixMultiplication(Matrix* matrixB);

        Matrix invertMatrix();

        std::vector<double>* getColumn(int index);

        void printMatrix();

        int getRowLength();

        int getColumnLength();
};