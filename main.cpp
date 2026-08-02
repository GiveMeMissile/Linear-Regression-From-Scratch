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
    processor.printMatrix();
    std::cout << "Split time!\n";
    processor.split(1);
    std::cout << "SPLITTED!!!\n";

    std::cout << "Train X: \n";
    processor.xTrain.printMatrix();
    std::cout << "\nTrain y: \n";
    processor.yTrain.printMatrix();

    std::cout << "\nTest X: \n";
    processor.xTest.printMatrix();
    std::cout << "\nTest y: \n";
    processor.yTest.printMatrix();

    Matrix transpose = processor.xTrain.transpose();
    Matrix product = transpose.matrixMultiplication(&processor.xTrain);
    std::cout << "\nProduct Between transpose and trainX: \n";
    product.printMatrix();

    Matrix invertedProduct = product.invertMatrix();
    std::cout << "\nInverted Product: \n";
    invertedProduct.printMatrix();

    return 0;
}
