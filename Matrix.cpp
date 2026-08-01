#include <iostream>
#include <vector>
#include "Matrix.hpp"


Matrix::Matrix(std::vector<std::vector<double>> *matrix){
    this->matrix = *matrix;
}

double Matrix::dotProduct(const std::vector<double> *a, const std::vector<double> *b){
    double product = 0;
    for (int i = 0; i < a->size(); i++){
        product += a->at(i) * b->at(i);
    }

    return product;
}


Matrix Matrix::transpose(){
    // Method which transposes the matrix

    std::vector<std::vector<double>> transposedMatrix;

    for (int i = 0; i < this->matrix.at(0).size(); i++){
        transposedMatrix.push_back(*this->getColumn(i));
    }

    return Matrix(&transposedMatrix);
}


bool Matrix::checkIfCanMultiply(int columnSize){
    // Checks if matrix multiplication can be preformed

    int rowSize = this->matrix.at(0).size();
    if (columnSize == rowSize){
        return true;
    }else{
        return false;
    }
}


Matrix Matrix::matrixMultiplication(Matrix* matrixB){
    // Preforms matrix multiplication with the inputted matrix B
    // May optimize this function later, as right now it is quite unoptimized...

    int matrixBSize = matrixB->getColumn(0)->size();

    if (!this->checkIfCanMultiply(matrixBSize)){
        return NULL;
    }

    std::vector<std::vector<double>> product;

    for (int i = 0; i < this->matrix.size(); i++){
        std::vector<double> productRow;
        for (int j = 0; j < matrixB->getRowLength(); j++){
            std::vector<double>* columnPtr = matrixB->getColumn(j);  

            productRow.push_back(this->dotProduct(&this->matrix.at(i), columnPtr));
        }
        product.push_back(productRow);
    }
    Matrix productMatrix = Matrix(&product);

    return productMatrix;
}


Matrix Matrix::partitionMatrix(int colIdx, int rowIdx){
    // This function creates a new matrix with the a row and column removed.
    // This is used for calculating the inverse matrix and the Determinate.

    std::vector<std::vector<double>> partitionedMatrix(matrix);

    // Remove the row from the new matrix.
    partitionedMatrix.erase(partitionedMatrix.begin() + rowIdx);

    // Remove the column from the new Matrix
    for (int i = 0; i < partitionedMatrix.size(); i++){
        partitionedMatrix.at(i).erase(partitionedMatrix.at(i).begin() + colIdx);
    }

    Matrix resultPartitionedMatrix = Matrix(&partitionedMatrix);

    return resultPartitionedMatrix;
}


double Matrix::calculateDeterminate(){
    // This function is going to be a computational nightmare...

    if (!this->isSquare()){
        std::cout << "\nShape Error:\n";
        throw std::invalid_argument("Matrix must have the same number of rows and columns to find the Determinate");
        return -1;
    }
    if (this->isTwoByTwo()){
        /* 
        If matrix is 2x2, calculate the determinate using the formula ad - bc, where the matrix is:
        [a, b]
        [c, d]
        When calculating the determinate for bigger matrixies, this is used as the base case.
        */
        return this->matrix.at(0).at(0)*this->matrix.at(1).at(1) - this->matrix.at(0).at(1)*this->matrix.at(1).at(0);
    }
    double determinate = 0;
    // std::cout << "\nStrat new calculation\n";
    for (int i = 0; i < this->matrix.size(); i++){
        Matrix partition = this->partitionMatrix(i, 0);
        double value = this->matrix.at(0).at(i) * partition.calculateDeterminate();
        if (i % 2 == 1){
            determinate = determinate - value;
        }else{
            determinate = determinate + value;
        }
        // std::cout << "\nDeterminate:  " << determinate;
        // std::cout << "  |  ";
        // std::cout << "Value:  " << value;
        // std::cout << "  |  ";
        // std::cout << "Index Value:  " << this->matrix.at(0).at(i);
        // std::cout << "\nMatrix: \n";
        // partition.printMatrix();
    }

    return determinate;
}


bool Matrix::isSquare(){
    if (this->getRowLength() == this->getColumnLength()){
        return true;
    }
    return false;
}


bool Matrix::isTwoByTwo(){
    if (this->getRowLength() == 2 && this->getColumnLength() == 2){
        return true;
    }
    return false;
}


std::vector<double>* Matrix::getColumn(int index){
    // Gets the desired column from the matrix

    std::vector<double> column;
    std::vector<double>* columnPrt = &column;
    for (int i = 0; i < this->matrix.size(); i++){
        column.push_back(matrix.at(i).at(index));
    }
    return columnPrt;
}


void Matrix::printMatrix(){
    for (auto row: this->matrix){
        for (auto val: row){
            std::cout << val << ", ";
        }
        std::cout << "\n";
    }
}


int Matrix::getRowLength(){
    return this->matrix.at(0).size();
}


int Matrix::getColumnLength(){
    return this->matrix.size();
}