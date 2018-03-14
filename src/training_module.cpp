//
// Created by Asha Agrawal on 3/12/2018.
//

#include "training_module.h"
#include "feature_vector.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

vector<vector<vector<double>>> module;
vector<double> prior;

ifstream ins;

vector<pair<int, Feature_Vector>> read_file_input() {
    string file_data_name;
    string file_answers_name;

    ifstream training_data_file;
    ifstream training_answers_file;

    cout << "Input data file to be read: " << endl;
    cin >> file_data_name;
    cout << "Input answer file to be read: " << endl;
    cin >> file_answers_name;

    training_data_file.open(file_data_name);
    training_answers_file.open(file_answers_name);
    //check that file is valid
    if (!training_data_file.is_open() || !training_answers_file.is_open()) {
        cout << "Cannot open file" << endl;
        exit(1);
    }

    //at this point, i know that files will be read
    //now creating a vector of pairs that contains a Feature_Vector and its corresponding classification (int)
    vector<pair<int, Feature_Vector>> images;
    int classification;
    while (training_data_file) {
        Feature_Vector feature;
        pair<int, Feature_Vector> image;
        image = make_pair(classification, feature.read(ins));
        images.push_back(image);
    }
    training_data_file.close();
    cout << "Reading of training images complete" << endl;
    return images;
}

vector<vector<vector<double>>>train(vector<pair<int, Feature_Vector>> images) {
    Training_Module trainer;
    //go through images 10 times to find the all of the Frequency_Vectors with the specific classification
    for (int i = 0; i < 10; i++) {
        trainer.search(i, images);
        trainer.priors(i, images);
    }
    return trainer.write_module(ostream::out&);
}

void search(int classification, vector <pair<int, Feature_Vector>> images) {
    int classification_occurance_counter = 0;
    vector <vector<double>> cell_occurance_counter;

    //go through each Feature_Vector and Classification pair
    for (int i = 0; i < images.size(); i++) {

        //see if the classification of the pair is the one we are searching for
        if (images[i].first == classification) {
            classification_occurance_counter++;

            //now go through the entire Feature_Vector and get the number of occurances of a '1' for a specific cell
            for (int j = 0; j < images[i].second.get_size(); j++) {
                for (int k = 0; k < images[i].second.get_size(); k++) {
                    if (images[i].second.get_value(j, k) == 1) {
                        cell_occurance_counter[j][k]++;
                    }
                }
            }
        }
    }

    //now that i have gone through each Feature_Vector with the specified classification, i want to compute the
    // probability of each cell
    //i will change the value of k by myself
    double k = 0.000000000001;
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            //using given formula: (k + #times Fi,j = f for class c)/(2k + Total # of training examples of class c)
            double computed_probability =
                    (k + cell_occurance_counter[i][j]) / ((2 * k) + classification_occurance_counter);
            cell_occurance_counter[i][j] = computed_probability;
        }
    }
    //add these freshly computed probabilities to the 3D module vector
    for(int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            module[classification][i][j] = cell_occurance_counter[i][j];
        }
    }
}

void priors(int classification, vector <pair<int, Feature_Vector>> images) {
    double classification_occurance_counter = 0;

    //go through each Feature_Vector and Classification pair
    for (int i = 0; i < images.size(); i++) {

        //see if the classification of the pair is the one we are searching for
        if (images[i].first == classification) {
            classification_occurance_counter++;
        }
    }
    prior.push_back(classification_occurance_counter / images.size());
}

int calculate_posterior_probability(Feature_Vector input_feature, vector<double> prior) {
    std::vector<std::pair<int, double>> posteriors;
    double posterior_probability = 0;
    for (int i = 0; i < 10; i++) {
        posterior_probability += prior[i];
        for (int j = 0; j<28; j++) {
            for (int k = 0; k < 28; k++) {
                posterior_probability += log((input_feature.get_value(j, k))/module[i][j][k]);
            }
        }
        pair<int, double> pairs;
        pairs.first = i;
        pairs.second = posterior_probability;
        posteriors.push_back(pairs);
    }

    //now go through all of the probabilities and find the class with the highest probability
    double max_probability = 0;
    int max_class = 0;

    for(int i = 0; i < 10; i++) {
        if (posteriors[i].second > max_probability) {
            max_probability = posteriors[i].second;
            max_class = posteriors[i].first;
        }
    }

    return max_class;
}

void read_module(istream &ins) {
    for (int k = 0; k < 10; k++) {
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                double input;
                ins >> input;
                module[k][i][j] = input;
            }
        }
    }
}

void write_module(ostream &outs) {
    outs << "{";
    for (int k = 0; k < 10; k++) {
        outs << k << ": {";
        for (int i = 0; i < 28; i++) {
            outs << "{";
            for (int j = 0; j < 28; j++) {
                outs << module[k][i][j];
                if (j != 27) {
                    outs << " ";
                }
            }
            outs << "}";
            if (i != 27) {
                outs << "\n";
            }
        }
        outs << "}";
        if (k != 9) {
            outs << "\n";
        }
    }
    outs << "}";
}

istream &operator>>(istream &ins, Training_Module& model) {
    model.read_module(ins);
    return ins;
}

ostream &operator<<(ostream &outs, Training_Module& model) {
    model.write_module(outs);
    return outs;
}

