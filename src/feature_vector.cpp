//
// Created by Asha Agrawal on 3/11/2018.
//

#include "feature_vector.h"
#include <iostream>
#include <vector>

vector <vector<bool>> feature;

Feature_Vector::Feature_Vector() {
    vector<vector<bool>> feature;
}

vector<vector<bool>> read(istream& ins) {
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            bool input;
            if (!ins.eof()) {
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

bool get_value(int i, int j) {
    if (i < feature.size() && j < feature.size() && i > 0 && j > 0) {
        return feature[i][j];
    }
    return false;
}

int get_size() {
    return feature.size();
}

void Feature_Vector::write(std::ostream& outs) {
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

istream& operator >> (std::istream& ins,  Feature_Vector& feature_vector)
{
    feature_vector.read(ins);
    return ins;
}

ostream& operator<< (std::ostream& outs, Feature_Vector feature_vector)
{
    feature_vector.write(outs);
    return outs;
}