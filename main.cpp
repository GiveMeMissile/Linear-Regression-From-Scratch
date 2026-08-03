#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "Matrix.hpp"
#include "LinearRegression.hpp"
#include "DataProcessor.hpp"

void get_data(std::string filename, std::vector<std::vector<double>> *data);
void print_data(std::vector<std::vector<double>> *data);

int main(){
    // Get the Data
    DataProcessor processor = DataProcessor("sample.csv");
    processor.split(1);

    LinearRegression linReg = LinearRegression(processor.xTrain, processor.yTrain);

    Prediction trainPred = linReg.predict(processor.xTrain, processor.yTrain);
    Prediction testPred = linReg.predict(processor.xTest, processor.yTest);

    std::cout << "\nTraining Prediction: \n";
    std::cout << "MSE: " << trainPred.mse << "  |  " << "R Squared: " << trainPred.r2 << "\n";
    std::cout << "\nTesting Predictions: \n";
    std::cout << "MSE: " << testPred.mse << "  |  " << "R Squared: " << testPred.r2 << "\n";

    return 0;
}
