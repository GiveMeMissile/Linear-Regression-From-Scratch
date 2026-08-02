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
    DataProcessor processor = DataProcessor("sample.txt");
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

    return 0;
}

void get_data(std::string filename, std::vector<std::vector<double>> *data){
    // Loads the data from the inputted file and saves it in the inputted data vector.
    // The Last row will be determined

    std::string row;

    std::ifstream Data(filename);

    while (std::getline(Data, row)){
        // std::cout << row << "\n";
        std::stringstream ss(row);
        std::vector<double> saved_row;

        std::string value;
        
        while (std::getline(ss, value, ',')){
            try{
                saved_row.push_back(std::stod(value));
            }catch (const std::invalid_argument& e){
                std::cout << "\nError: \n";
                std::cout << "Value in Dataset contain a non numeric Value";
            }
        }

        data->push_back(saved_row);
    }
    Data.close();
}