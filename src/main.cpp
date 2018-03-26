//
// Created by Asha Agrawal on 3/13/2018.
//
#include "training_model.h"
#include "feature_vector.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    //train the stuff
    //train will call search (creates 3D vector) and priors (which computes #times classification/total)
    vector<pair<int, FeatureVector>> image;
    TrainingModel training_images;
    image = training_images.read_file_input();
    ifstream ins;
    training_images.train(image);

    //put images into a file
    ofstream model_file ("training model");
    model_file << training_images << std::endl;
    model_file.close();


    //getting the test images and their labels
    string file_name;
    string file_answers_name;

    ifstream test_data_file;
    ifstream test_answers_file;

    cout << "Input test file to be read: " << endl;
    cin >> file_name;
    cout << "Input test answer file to be read: " << endl;
    cin >> file_answers_name;

    test_answers_file.open(file_answers_name);
    test_data_file.open(file_name);
    //check that file is valid
    if (!test_answers_file.is_open() || !test_data_file.is_open()) {
        cout << "Cannot open file" << endl;
        exit(1);
    }

    //start the confusion matrix portion
    //column is the classification that should've been outputed
    //row is what the program classified the image

    vector<vector<int>> confusion_matrix;
    while(!test_data_file.eof()) {
        Feature_Vector feature;
        pair<int, Feature_Vector> image;
        feature.read(ins);
        int class_identified = training_images.calculate_posterior_probability(feature, training_images.prior);
        int real_class;
        cin >> real_class;
        confusion_matrix[real_class][class_identified]++;
    }

    //output the accuracy based on the diagonal of the conusion_matrix and the number of inputs in it
    int total = 0;
    int diagonal = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            total += confusion_matrix[i][j];
            if (i == j) {
                diagonal += confusion_matrix[i][j];
            }
        }
    }
    double accuracy = diagonal/total;
    cout << accuracy << endl;

    return 0;
}