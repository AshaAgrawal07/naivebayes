//
// Created by Asha Agrawal on 3/12/2018.
//

#ifndef NAIVEBAYES_TRAINING_DATA_H
#define NAIVEBAYES_TRAINING_DATA_H

#include "feature_vector.h"

class Training_Module {
    std::vector<std::vector<std::vector>> probabilities;
    std::vector<std::vector<std::vector>> module;
    std::vector<double> prior;

private:
    /**
     * reads the files and helps in training or testing
     * it depends on the file that is inputted
     * it will output an error message if the file does not exist/cannot be accessed
     *
     * it will create a vector of pairs of a Feature_Vectors with its corresponding classification as an int
     * it is basically the helper method for train() when it is called in main.cpp
     */
    vector<std::pair<int, Feature_Vector>> read_file_input();

    /**
     * is a helper method for train()
     * given a specific classification, search will go through all of the images and compute the probabilities for that
     * classification and then compute the probabilities for each cell using the given laplace's smooting factor
     * @param classification the specific number 0-9 that we want to compute the probabilities for
     * @param images the vector of images that we have stored
     */
    void search(int classification, vector <std::pair<int, Feature_Vector>> images);

public:

    /**
     * creates a 3D vector (a vector of vectors of vectors) with the intended size of 10x28x28 that will store the probabilities
     * goes through the elements in the vectors for each classifications and computes the probabilities using the
     * naive-bayes formula that was given
     * @param images a vector of pairs of a Feature_Vector and its corresponding classification as an int- which will
     * be made through the read_input function
     */
    void train(vector<std::pair<int, Feature_Vector>> images);

    /**
     *
     * @param classification the specific number 0-9 that we want to count the occurances for from given file
     * @param images the vector of images that we have stored
     * @return the probability of a specific class appearing in the entire file
     */
    double priors(int classification, vector <std::pair<int, Feature_Vector>> images);

    /**
     * calculates the posterior probabilities using logarithms
     * @param module the model we want to compute the class probabilities for
     * @param prior vector of P(classification)
     * @return a vector of pairs of classifications 0-9 and its corresponding posterior probability
     */
    std::vector<std::pair<int, double>> calculate_posterior_probability(std::vector<std::vector<std::vector>> module,
                                                                        std::vector<double> prior);

    /**
     * reads the module from the input stream as a 10x28x28 3D vector
     * @param ins the input stream
     */
    void read_module(istream& ins);

    /**
     * outputs the module in 3D vector format
     * @param outs the output stream
     */
    void write_module(ostream& outs);
};

/**
 * operator overloading of >>
 * @param ins the input stream
 * @param model the module in question
 * @return the input stream
 */
istream& operator >> (istream& ins, Training_Module model);

/**
 * operator overloading of <<
 * @param outs the output stream
 * @param model the module in question
 * @return the output stream
 */
ostream& operator << (ostream& outs, Training_Module& model);
#endif //NAIVEBAYES_TRAINING_DATA_H
