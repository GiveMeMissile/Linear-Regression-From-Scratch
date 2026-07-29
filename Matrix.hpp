#pragma once

#include <vector>
#include <iostream>

class Matrix{
    private:
        std::vector<std::vector<double>> matrix;

    public:
        Matrix(std::vector<std::vector<double>> *matrix);

        Matrix transpose();

        Matrix matrix_multiplication();

        Matrix invert_matrix();

        void print_matrix();
};