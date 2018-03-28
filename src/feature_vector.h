//
// Created by Asha Agrawal on 3/11/2018.
//

#ifndef NAIVEBAYES_ASHAAGRAWAL07_FEATURE_VECTOR_H
#define NAIVEBAYES_ASHAAGRAWAL07_FEATURE_VECTOR_H

#include <iostream>
#include <vector>

using namespace std;

class FeatureVector {

public:
    vector<vector<bool>> feature;

    /**
     * creates an empty 28X28 feature_vector
     * is the constructor
     */
    FeatureVector();

    /**
     *
     * @param i the row
     * @param j the column
     * @return the boolean value stored there
     */
    bool get_value (int i, int j);

    /**
     *
     * @return the size of the feature vector
     */
    int get_size();
    /**
     * Basically takes in the characters and converts it into booleans: 0 if whitespace, 1 otherwise
     * @param ins the input stream that the function will read and turn into a 28x28 boolean vector
     * @return a vector of vector of bools (basically the feature vector for the image)
     */
    vector<vector<bool>> read(istream& ins);

    /**
     * @param outs the out stream the function will use to output the Feature_Vector
     */
    void write (ostream& outs);

};
/**
 * overloading operator >>
 * @param ins the input stream
 * @param featurevector the feature vector in question
 * @return the input stream
 */
istream& operator >> (istream& ins, FeatureVector &featurevector);

/**
 * overloading operator <<
 * @param outs the output stream
 * @param featurevector the feature vector in question
 * @return the output stream
 */
ostream& operator << (ostream& outs, FeatureVector &featurevector);

#endif //NAIVEBAYES_ASHAAGRAWAL07_FEATURE_VECTOR_H
