#pragma once

#include <iostream>
#include <vector>
#include "Matrix.hpp"

class LinearRegression{
    public:
        LinearRegression();

        LinearRegression(Matrix X, Matrix y);

        void fit(Matrix X, Matrix y);

    private:
        std::vector<double> weights;

        double bias;
};