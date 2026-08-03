#pragma once

#include <iostream>
#include <vector>
#include "Matrix.hpp"

struct Prediction{
    double r2;
    double mse;
};

class LinearRegression{
    public:
        LinearRegression();

        LinearRegression(Matrix X, Matrix y);

        void fit(Matrix X, Matrix y);

        Prediction predict(Matrix X, Matrix y);

    private:
        std::vector<double> weights;

        double bias;
};