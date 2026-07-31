#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "Matrix.hpp"
#include "LinearRegression.hpp"

void get_data(std::string filename, std::vector<std::vector<double>> *data);
void print_data(std::vector<std::vector<double>> *data);

int main(){
    // Get the Data
    std::vector<std::vector<double>> data;
    get_data("sample.txt", &data);
    Matrix matrix = Matrix(&data);

    // Display the Original Matrix
    std::cout << "Original Matrix\n";
    matrix.printMatrix();

    // Transpose the matrix and display the new matrix.
    Matrix transposedMatrix = matrix.transpose();
    std::cout << "\nTransposed Matrix\n";
    transposedMatrix.printMatrix();

    // Preform Matrix multiplication
    Matrix product = matrix.matrixMultiplication(&transposedMatrix);
    std::cout << "\nProduct Matrix\n";
    product.printMatrix();
    return 0;
}

void print_data(std::vector<std::vector<double>> *data){
    for (auto row: *data){
        for (auto val: row){
            std::cout << val << ", ";
        }
        std::cout << "\n";
    }
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