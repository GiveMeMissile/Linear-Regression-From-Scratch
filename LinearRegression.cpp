#include <iostream>
#include <vector>
#include "LinearRegression.hpp"
#include "Matrix.hpp"

LinearRegression::LinearRegression(){}

LinearRegression::LinearRegression(Matrix X, Matrix y){
    this->fit(X, y);
}

void LinearRegression::fit(Matrix X, Matrix y){
    // It all comes together now...

    Matrix transposedX = X.transpose();
    Matrix product = transposedX.matrixMultiplication(&X);
    Matrix inverse = product.invertMatrix();
    
    Matrix otherProduct = transposedX.matrixMultiplication(&y);
    Matrix weightMatrix = inverse.matrixMultiplication(&otherProduct);

    weightMatrix.printMatrix();
}