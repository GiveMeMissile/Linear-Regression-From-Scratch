#include <iostream>
#include <vector>
#include "Matrix.hpp"


Matrix::Matrix(std::vector<std::vector<double>> *matrix){
    this->matrix = *matrix;
}

double Matrix::dotProduct(const std::vector<double> *a, const std::vector<double> *b){
    // Returns the dot product between the two inputted vectors

    if (!(a->size() == b->size())){
        throw std::invalid_argument("Both vectors must be of equal length to preform a Dot Product.");
    }

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


void Matrix::multiply(double value){
    // Multiplies all elements within the matrix by the given value.

    for (int i = 0; i < this->matrix.size(); i++){
        for (int j = 0; j < this->matrix.at(0).size(); j++){
            this->matrix.at(i).at(j) = this->matrix.at(i).at(j)*value;
        }
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
    // Can be used to remove individual rows and columns too, as the other operation is ignored if the index is negitive
    
    std::vector<std::vector<double>> partitionedMatrix(matrix);

    // Remove the row from the new matrix.
    if (rowIdx >= 0){
        partitionedMatrix.erase(partitionedMatrix.begin() + rowIdx);
    }

    // Remove the column from the new Matrix
    if (colIdx >= 0){
        for (int i = 0; i < partitionedMatrix.size(); i++){
            partitionedMatrix.at(i).erase(partitionedMatrix.at(i).begin() + colIdx);
        }
    }

    Matrix resultPartitionedMatrix = Matrix(&partitionedMatrix);

    return resultPartitionedMatrix;
}


double Matrix::calculateDeterminat(){
    // This function is going to be a computational nightmare...
    // It calculates the Determinant for the matrix.

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
        double value = this->matrix.at(0).at(i) * partition.calculateDeterminat();
        if (i % 2 == 1){
            determinate = determinate - value;
        }else{
            determinate = determinate + value;
        }
    }
    return determinate;
}


Matrix Matrix::calculateMatrixOfMinors(){
    // Creates a Matrix of Minors, which is a matrix containing the Determinants of the smaller partitioned matrixies within it.
    // This is used when inverting a matrix, as the matrix of minors is an important part of that operation.

    std::vector<std::vector<double>> minors;

    for (int i = 0; i < this->matrix.size(); i++){
        std::vector<double> row;
        for (int j = 0; j < this->matrix.at(0).size(); j++){
            Matrix partition = this->partitionMatrix(i, j);
            double determinate = partition.calculateDeterminat();
            row.push_back(determinate);
        }
        minors.push_back(row);
    }

    Matrix matrixOfMinors = Matrix(&minors);
    return matrixOfMinors;
}


void Matrix::cofactorMatrix(){
    // Inverts the sign of every other value in the matrix.
    // Essentially adds a checkerboard of negitive signs across the matrix.

    for (int i = 0; i < this->matrix.size(); i++){
        for (int j = 0; j < this->matrix.at(0).size(); j++){
            if ((i % 2 + j) % 2 == 1){
                this->matrix.at(i).at(j) = -this->matrix.at(i).at(j);
            }
        }
    }
}


Matrix Matrix::invertMatrix(){
    /* Inverts the matrix using Matrix of Minors. So that   Originl_Matrix * Inverted Matrix = Identity Matrix
    Here is a better example:
    Original Inverted   Identity
    [a, b] * [ai, bi] = [1, 0]
    [c, b]   [ci, di]   [0, 1]
    */

    double determinant = this->calculateDeterminat();
    if (determinant == 0){
        std::cout << "\nError: \n";
        std::cout << "The Determinant of this Matrix is zero, thus it cannot be inverted.";
        return NULL;
    }
    Matrix invertedMatrix = this->calculateMatrixOfMinors();
    invertedMatrix.cofactorMatrix();
    determinant = 1/determinant;
    invertedMatrix.multiply(determinant);
    return invertedMatrix;
}


bool Matrix::isSquare(){
    // Checks if the number of rows are equal to the number of columns

    if (this->getRowLength() == this->getColumnLength()){
        return true;
    }
    return false;
}


bool Matrix::isTwoByTwo(){
    // Checks if the current matrix is a 2x2, with the number of rows and columns being both equal to 2.

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
    // Displays the current matrix in the console

    for (auto row: this->matrix){
        for (auto val: row){
            std::cout << val << ", ";
        }
        std::cout << "\n";
    }
}


int Matrix::getRowLength(){
    // Returns the length of the row

    return this->matrix.at(0).size();
}


int Matrix::getColumnLength(){
    // Returns the length of the column

    return this->matrix.size();
}