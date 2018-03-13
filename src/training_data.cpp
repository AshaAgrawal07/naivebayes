//
// Created by Asha Agrawal on 3/12/2018.
//

#include "training_data.h"
#include "feature_vector.h"
#include "data_file.h"
#include <fstream>
#include <iostream>
#include <iomanip>

vector <std::pair<int, Feature_Vector>> read_input() {
    std::string file_data_name;
    std::srting file_answers_name;
    std::istream ins;

    std::ifstream training_data_file;
    std::ifstream training_answers_file;

    std::cout << "Input data file to be read: " << std::endl;
    std::cin >> file_data_name;
    std::cout << "Input answer file to be read: " << std::endl;
    std::cin >> file_answers_name;

    training_data_file.open(file_data_name);
    training_answers_file.open(file_answers_name);
    //check that file is valid
    if (!training_data_file.is_open() || !training_answers_file.is_open()) {
        std::cout << "Cannot open file" << std::endl;
        std::exit(1);
    }

    //at this point, i know that files will be read
    //now creating a vector of pairs that contains a Feature_Vector and its corresponding classification (int)
    vector <std::pair<int, Feature_Vector>> images;
    int classification;
    while (training_data_file >> ins && training_answers_file >> classification) {
        Feature_Vector feature;
        vector <std::pair<int, Feature_Vector>> image;
        image = std::pair<classification, feature.read(ins)>;
        images.push_back(image);
    }
    training_data_file.close();
    std::cout << "Training complete" << std::endl;
    return images;
}

void train(vector <std::pair<int, Feature_Vector>> images) {
    std::vector<std::vector<std::vector>> probabilities;

    //go through images 10 times to find the all of the Frequency_Vectors with the specific classification
    for (int i = 0; i < 10; i++) {
        
    }
}




