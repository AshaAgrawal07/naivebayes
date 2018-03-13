//
// Created by Asha Agrawal on 3/11/2018.
//

#ifndef NAIVEBAYES_ASHAAGRAWAL07_FEATURE_VECTOR_H
#define NAIVEBAYES_ASHAAGRAWAL07_FEATURE_VECTOR_H

#include <iostream>

using namespace std;

class Feature_Vector {

private:
    vector <std::vector<bool>> feature;
public:

    /**
     * creates an empty 28X28 feature_vector
     * is the constructor
     */
    Feature_Vector();

    /**
     *
     * @param i the row
     * @param j the column
     * @return the boolean value stored there
     */
    bool get_Value(int i, int j);
    /**
     * Basically takes in the characters and converts it into booleans: 0 if whitespace, 1 otherwise
     * @param ins the input stream that the function will read and turn into a 28x28 boolean vector
     */
    void read(istream& ins);

    /**
     * @param outs the out stream the function will use to output the Feature_Vector
     */
    void write(ostream& outs);

};
/**
 * overloading operator >>
 * @param ins the input stream
 * @param featurev the feature vector in question
 * @return the input stream
 */
istream& operator >> (istream& ins, Feature_Vector& featurev);

/**
 * overloading operator <<
 * @param outs the output stream
 * @param featurev the feature vector in question
 * @return the output stream
 */
ostream& operator << (ostream& outs, Feature_Vector featurev);

#endif //NAIVEBAYES_ASHAAGRAWAL07_FEATURE_VECTOR_H
