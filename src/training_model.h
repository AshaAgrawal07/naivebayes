//
// Created by Asha Agrawal on 3/12/2018.
//

#ifndef NAIVEBAYES_TRAINING_DATA_H
#define NAIVEBAYES_TRAINING_DATA_H

#include <vector>
#include "feature_vector.h"

class TrainingModel {


public:
    vector<vector<vector<double>>> model;
    vector<double> prior;

    /**
     * reads the files and helps in training or testing
     * it depends on the file that is inputted
     * it will output an error message if the file does not exist/cannot be accessed
     *
     * it will create a vector of pairs of a FeatureVectors with its corresponding classification as an int
     * it is basically the helper method for train() when it is called in main.cpp
     */
    vector<pair<int, FeatureVector>> read_file_input();

    /**
     * is a helper method for train()
     * given a specific classification, search will go through all of the images and compute the probabilities for that
     * classification and then compute the probabilities for each cell using the given laplace's smoothing factor
     * @param classification the specific number 0-9 that we want to compute the probabilities for
     * @param images the vector of images that we have stored
     * @return a vector of vector of doubles (basically the computed probabilities for each cell for the particular
     * classification)
     */
    vector<vector<double>> search (int classification, vector <std::pair<int, FeatureVector>> images);

    /**
     * @param images the vector of images that we have stored along with their respective classifications
     * @return the probabilities of each specific class appearing in the entire file in a vector
     */
    vector<double> priors (vector<pair<int, FeatureVector>> images);

    /**
     * creates a 3D vector (a vector of vectors of vectors) with the intended size of 10x28x28 that will store the
     * probabilities
     * goes through the elements in the vectors for each classifications and computes the probabilities using the
     * naive-bayes formula that was given
     * @param images a vector of pairs of a Feature_Vector and its corresponding classification as an int- which will
     * be made through the read_input function
     * @return the 3D vector with the probabilities
     */
    vector<vector<vector<double>>> train_data_model (vector<pair<int, FeatureVector>> images);

    /**
     * calculates the posterior probabilities using logarithms
     * @param input_feature the FeatureVector (for test images) we want to fine the classification for
     * @param prior the vector of P(classification)
     * @return int, the most probable classification for the given Feature_Vector
     */
    int calculate_posterior_probability(FeatureVector input_feature, vector<double> prior);

    /**
     * reads the model from the input stream as a 10x28x28 3D vector
     * @param ins the input stream
     */
    void read_model (ifstream& ins);

    /**
     * outputs the model in 3D vector format
     * @param outs the output stream
     */
    void write_model (ostream& outs);
};

/**
 * operator overloading of >>
 * @param ins the input stream
 * @param model the model in question
 * @return the input stream
 */
ifstream& operator >> (ifstream& ins, TrainingModel& models);

/**
 * operator overloading of <<
 * @param outs the output stream
 * @param model the model in question
 * @return the output stream
 */
ostream& operator << (ostream& outs, TrainingModel& models);
#endif //NAIVEBAYES_TRAINING_DATA_H
