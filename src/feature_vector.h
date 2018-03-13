//
// Created by Asha Agrawal on 3/11/2018.
//

#ifndef NAIVEBAYES_ASHAAGRAWAL07_FEATURE_VECTOR_H
#define NAIVEBAYES_ASHAAGRAWAL07_FEATURE_VECTOR_H

#include <iostream>

using namespace std;

class Feature_Vector {

private:
    vector <vector<bool>> feature;
public:

    /**
     * creates an empty 28X28 feature_vector
     * is the constructor
     */
    Feature_Vector();

    /**
     * Basically takes in the characters and converts it into booleans: 0 if whitespace, 1 otherwise
     * @param ins the input stream that the function will read and turn into a 28x28 boolean vector
     */
    void read(istream& ins);
    void write(ostream& outs);

};
istream& operator >> (istream& ins, Feature_Vector& featurev);
ostream& operator << (ostream& outs, Feature_Vector featurev);

#endif //NAIVEBAYES_ASHAAGRAWAL07_FEATURE_VECTOR_H
