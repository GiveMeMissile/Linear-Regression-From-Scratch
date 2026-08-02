#pragma once

#include <vector>
#include <iostream>
#include "Matrix.hpp"

class DataProcessor: public Matrix{
    public:

        DataProcessor(std::string filename);

        void split(int targetIdx);

        Matrix yTrain;
        Matrix xTrain;
        Matrix yTest;
        Matrix xTest;

    private:
        void getData(std::string filename);
};