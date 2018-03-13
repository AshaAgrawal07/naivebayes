//
// Created by Asha Agrawal on 3/12/2018.
//

#ifndef NAIVEBAYES_TRAINING_DATA_H
#define NAIVEBAYES_TRAINING_DATA_H

#include "feature_vector.h"

class Training_Data {
private:
    /**
     * reads the files and helps in training or testing
     * it depends on the file that is inputted
     * it will output an error message if the file does not exist/cannot be accessed
     *
     * it will create a vector of pairs of a Feature_Vectors with its corresponding classification as an int
     * it is basically the helper method for train() when it is called in main.cpp
     */
    vector<std::pair<int, Feature_Vector>> read_input();
public:

    /**
     * creates a 3D vector (a vector of vectors of vectors) with the intended size of 10x28x28 that will store the probabilities
     * goes through the elements in the vectors for each classifications and computes the probabilities using the
     * naive-bayes formula that was given
     * @param images a vector of pairs of a Feature_Vector and its corresponding classification as an int- which will
     * be made through the read_input function
     */
    void train(vector<std::pair<int, Feature_Vector>> images);
};
#endif //NAIVEBAYES_TRAINING_DATA_H
