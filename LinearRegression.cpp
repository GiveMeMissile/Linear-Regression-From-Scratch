#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include "LinearRegression.hpp"
#include "Matrix.hpp"


LinearRegression::LinearRegression(){}

LinearRegression::LinearRegression(Matrix X, Matrix y){
    this->fit(X, y);
}

void LinearRegression::fit(Matrix X, Matrix y){
    /* Calculates the weights and bias of the Linear Regression model
     * Uses OLS to Calulate the Weights and Bias of the model, the equation of which is shown below.
     * B = ((Xt)(X))^-1((Xt)(y)), 
     * Where X is the matrix of independant variables.
     * Xt is the transposed matrix of X
     * And y is the vector of target values.
    */

    Matrix transposedX = X.transpose();
    Matrix product = transposedX.matrixMultiplication(&X);
    Matrix inverse = product.invertMatrix();
    
    Matrix otherProduct = transposedX.matrixMultiplication(&y);
    Matrix weightMatrix = inverse.matrixMultiplication(&otherProduct);
    const std::vector<std::vector<double>>* betas = weightMatrix.getMatrix();

    this->bias = betas->at(0).at(0);

    for (int i = 1; i < betas->size(); i++){
        this->weights.push_back(betas->at(i).at(0));
    }
}

Prediction LinearRegression::predict(Matrix X, Matrix y){
    // Predicts the values of X, and then compares the prediction with the true y

    // Set up prediction matrixies.
    std::vector<double> predictedY;
    const std::vector<std::vector<double>>* features = X.getMatrix();
    const std::vector<std::vector<double>>* targets = y.getMatrix();

    Prediction pred;

    // Calculate the predicted values of y.
    for (int i = 0; i < features->size(); i++){
        double yPred = this->bias;
        for (int j = 1; j < features->at(0).size(); j++){
            yPred += features->at(i).at(j) * this->weights.at(j - 1);
        }
        predictedY.push_back(yPred);
    }

    // Calculate the mean of y as well as the residual sum.
    double targetMean = 0;
    double residualSum = 0;
    for (int i = 0; i < targets->size(); i++){
        targetMean += targets->at(i).at(0);
        double residual = targets->at(i).at(0) - predictedY.at(i);
        residualSum += residual * residual;
    }
    targetMean = targetMean/targets->size();
    pred.mse = residualSum/targets->size();

    // Calculate the sum of squares.
    double sumOfSquares = 0;
    for (int i = 0; i < targets->size(); i++){
        double difference = targets->at(i).at(0) - targetMean;
        sumOfSquares += difference * difference;
    }
    pred.r2 = 1 - (residualSum/sumOfSquares);

    return pred;
}

void LinearRegression::saveModel(){
    std::string saveString = std::to_string(this->bias);
    for (int i = 0; i < this->weights.size(); i++){
        saveString = saveString + " " + std::to_string(this->weights.at(i));
    }

    std::ofstream SaveFile("LinearRegressionModel.txt");

    SaveFile << saveString;

    SaveFile.close();
}