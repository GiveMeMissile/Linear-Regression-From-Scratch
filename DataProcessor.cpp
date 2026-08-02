#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <algorithm>
#include "Matrix.hpp"
#include "DataProcessor.hpp"

DataProcessor::DataProcessor(std::string filename) : Matrix(){
    this->getData(filename);
}

void DataProcessor::getData(std::string filename){
    // Loads the data from the inputted file and saves it in the inputted data vector.
    // The Last row will be determined

    std::string row;

    std::ifstream Data(filename);

    while (std::getline(Data, row)){
        // std::cout << row << "\n";
        std::stringstream ss(row);
        std::vector<double> savedRow;

        std::string value;
        
        while (std::getline(ss, value, ',')){
            try{
                savedRow.push_back(std::stod(value));
            }catch (const std::invalid_argument& e){
                // Empties the saveRow and exits the loop if non numeric value is detected.
                savedRow = {};
                break;
            }
        }
        if (!savedRow.empty()){
            savedRow.push_back(1.0);  // Adds a column of ones to the Matrix to adjust for biases.
            this->matrix.push_back(savedRow);
        }
    }
    Data.close();
}

void DataProcessor::split(int targetIdx){
    // Splits the Dataset into targets and features, and then splits those into training and testing datasets
    // This function will do an 80-20 Train-Test split on the dataset.

    // Set up random number Generators
    std::random_device rd;
    std::mt19937 gen(rd());

    // Randomly shuffle the current matrix.
    std::shuffle(this->matrix.begin(), this->matrix.end(), gen);

    // Seperate Matrix into Targets and Features
    std::vector<double> targets = this->getColumn(targetIdx);
    Matrix featuresMatrix = this->partitionMatrix(targetIdx, -1);
    const std::vector<std::vector<double>>* featuresPrt = featuresMatrix.getMatrix();

    // Get the splits for test and train
    int dataSize = targets.size();
    auto trainEnd = (dataSize - (int)(dataSize/5));;

    // Split the Vectors into train and test
    
    // Start by splitting the features/X matrix. 
    std::vector<std::vector<double>> trainX;
    std::vector<std::vector<double>> testX;
    for (int i = 0; i < featuresPrt->size(); i++){
        if (i + 1 <= featuresPrt->size() - (int)(featuresPrt->size()/5)){
            trainX.push_back(featuresPrt->at(i));
        }else{
            testX.push_back(featuresPrt->at(i));
        }
    }

    std::vector<double> trainY;
    std::vector<double> testY;
    for (int i = 0; i < targets.size(); i++){
        if (i + 1 <= targets.size() - (int)(targets.size()/5)){
            trainY.push_back(targets.at(i));
        }else{
            testY.push_back(targets.at(i));
        }
    }
    std::cout << "\nShape Check: \n";
    std::cout << "Train Y: " << trainY.size() << "  |  Test Y: " << testY.size() << "\n";

    // Save the splitted values as Matrixies
    this->xTrain = Matrix(trainX);
    this->xTest = Matrix(testX);
    this->yTrain = Matrix(trainY).transpose();
    this->yTest = Matrix(testY).transpose();
}