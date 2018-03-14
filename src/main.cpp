//
// Created by Asha Agrawal on 3/13/2018.
//
#include "training_module.h"
#include "feature_vector.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    //train the stuff
    //train will call search (creates 3D vector) and priors (which computes #times classification/total)
    vector<vector<vector<double>>> images;
    ifstream ins;
    images = images.train();

    //put images into a file
    ofstream model_file ("training model");
    model_file << images << std::endl;
    model_file.close();


}