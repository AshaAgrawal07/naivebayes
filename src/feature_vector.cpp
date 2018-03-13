//
// Created by Asha Agrawal on 3/11/2018.
//

#include "feature_vector.h"
#include "data_file.h"
#include <iostream>

Feature_Vector::Feature_Vector() {
    std::vector<std::vector<bool>> feature;
}

Feature_Vector Feature_Vector::read(istream& ins) {
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            bool input;
            if (ins >> " ") {
                ins >> input;
                input = 0;
            } else {
                ins >> input;
                input = 1;
            }
            feature[i].push_back(input);
        }
    }
    return feature;
}

void Feature_Vector::write(ostream& outs) {
    outs << "{";
    for (int i = 0; i < 28; i++) {
        outs << "{";
        for (int j = 0; j < 28; j++) {
            outs << feature[i][j];
            if (j != 27) {
                outs << " ";
            }
        }
        outs << "}" << "\n";
    }
    outs << "}";
}

istream& operator >> (istream& ins,  Feature_Vector& feature_vector)
{
    feature_vector.read(ins);
    return ins;
}

ostream& operator<< (ostream& outs, Feature_Vector feature_vector)
{
    feature_vector.write(outs);
    return outs;
}