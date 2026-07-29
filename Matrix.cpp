#include <iostream>
#include <vector>
#include "Matrix.hpp"

Matrix::Matrix(std::vector<std::vector<double>> *matrix){
    this->matrix = *matrix;
}

Matrix Matrix::transpose(){
    // Method which transposes the matrix

    std::vector<std::vector<double>> transposed_matrix;

    for (int i = 0; i < this->matrix.at(0).size(); i++){
        std::vector<double> row;

        for (int j = 0; j < this->matrix.size(); j++){
            row.push_back(matrix.at(j).at(i));
        }
        transposed_matrix.push_back(row);
    }

    return Matrix(&transposed_matrix);
}

void Matrix::print_matrix(){
    for (auto row: this->matrix){
        for (auto val: row){
            std::cout << val << ", ";
        }
        std::cout << "\n";
    }
}

// class Matrix{

//     private:
//         std::vector<std::vector<double>> matrix;
//     public:
        
//         Matrix(std::vector<std::vector<double>> *matrix){
//             this->matrix = *matrix;
//         }

//         Matrix transpose(){
//             // Method which transposes the matrix

//             std::vector<std::vector<double>> transposed_matrix;

//             for (int i = 0; i < this->matrix.at(0).size(); i++){
//                 std::vector<double> row;

//                 for (int j = 0; j < this->matrix.size(); j++){
//                     row.push_back(matrix.at(j).at(i));
//                 }
//             }

//             return Matrix(&transposed_matrix);
//         }

//         Matrix matrix_multiplication(){

//         }

//         Matrix invert_matrix(){

//         }

//         void print_matrix(){
//             for (auto row: this->matrix){
//                 for (auto val: row){
//                     std::cout << val << ", ";
//                 }
//                 std::cout << "\n";
//             }
//         }
// };