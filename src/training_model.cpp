//
// Created by Asha Agrawal on 3/12/2018.
//

#include "training_model.h"
#include "feature_vector.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

//10x28x28 vector that stores the probabilties of markings occurring at specific cells for each classification
vector<vector<vector<double>>> model;
vector<double> prior;

vector<pair<int, FeatureVector>> read_file_input() {
    string data_filename;
    string labels_filename;

    ifstream training_data_file;
    ifstream training_answers_file;

    cout << "Input data file to be read: " << endl;
    cin >> data_filename;
    cout << "Input answer file to be read: " << endl;
    cin >> labels_filename;

    training_data_file.open(data_filename);
    training_answers_file.open(labels_filename);
    //check that file is valid
    if (!training_data_file.is_open() || !training_answers_file.is_open()) {
        cout << "Cannot open file" << endl;
        exit(1);
    }

    //at this point, i know that files will be read
    //now creating a vector of pairs that contains a FeatureVector and its corresponding classification (int)
    vector<pair<int, FeatureVector>> images;
    int classification;
    while (training_data_file.peek() != training_data_file.eof()) {
        FeatureVector feature;
        pair<int, FeatureVector> image;
        image = make_pair(classification, feature.read(cin));
        images.push_back(image);
    }
    training_data_file.close();
    training_answers_file.close();
    cout << "Reading of training images complete" << endl;
    return images;
}

vector<vector<vector<double>>> train_data_model (vector<pair<int, FeatureVector>> images) {
    TrainingModel trainer;
    //go through images 10 times to find the all of the FrequencyVectors with the specific classification
    for(int i = 0; i < 10; i++) {
        model.push_back(trainer.search(i, images));
    }
    trainer.write_model(cout);
    return model;
}

vector<vector<double>> search (int classification, vector <pair<int, FeatureVector>> images) {
    int classification_occurrence_counter = 0;
    vector <vector<double>> cell_occurrence_counter;
    vector<vector<double>> classification_cell_probabilities;

    //go through each FeatureVector and Classification pair
    for (int i = 0; i < images.size(); i++) {

        //see if the classification of the pair is the one we are searching for
        if (images[i].first == classification) {
            classification_occurrence_counter++;

            //now go through the entire FeatureVector and get the number of occurrences of a '1' for a specific cell
            for (int j = 0; j < images[i].second.get_size(); j++) {
                for (int k = 0; k < images[i].second.get_size(); k++) {
                    if (images[i].second.get_value(j, k) == 1) {
                        cell_occurrence_counter[j][k]++;
                    }
                }
            }
        }
    }

    //now that i have gone through each Feature_Vector with the specified classification, i want to compute the
    // probability of each cell
    //i will change the value of k manually
    double k = 0.001;
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            //using given formula: (k + #times Fi,j = f for class c)/(2k + Total # of training examples of class c)
            double computed_probability =
                    (k + cell_occurrence_counter[i][j]) / ((2 * k) + classification_occurrence_counter);
            classification_cell_probabilities[i][j] = computed_probability;
        }
    }
    return classification_cell_probabilities;
}

vector<double> priors (vector<pair<int, FeatureVector>> images) {
    double classification_occurrence_counter = 0;
    //intended size of 10 by the end of this function

    //go through each classification
    for(int classification = 0; classification < 10; classification++) {
        //go through each Feature_Vector and Classification pair
        for (int i = 0; i < images.size(); i++) {

            //see if the classification of the pair is the one we are searching for
            if (images[i].first == classification) {
                classification_occurrence_counter++;
            }
        }
        prior.push_back(classification_occurrence_counter / images.size());
    }
}

int calculate_posterior_probability (FeatureVector input_feature, vector<double> prior) {
    TrainingModel trainer;
    vector<pair<int, double>> posteriors;
    double posterior_probability = 0;

    for (int i = 0; i < 10; i++) {
        posterior_probability += prior[i];
        for (int j = 0; j<28; j++) {
            for (int k = 0; k < 28; k++) {
                posterior_probability += log((input_feature.get_value(j, k))/model[i][j][k]);
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

void read_model (ifstream &ins) {
    for (int k = 0; k < 10; k++) {
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                double input;
                ins >> input;
                model[k][i][j] = input;
            }
        }
    }
}

void write_model (ostream &outs) {
    outs << "{";
    for (int k = 0; k < 10; k++) {
        outs << k << ": {";
        for (int i = 0; i < 28; i++) {
            outs << "{";
            for (int j = 0; j < 28; j++) {
                outs << model[k][i][j];
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

ifstream &operator >> (ifstream &ins, TrainingModel &models) {
    models.read_model(ins);
    return ins;
}

ostream &operator << (ostream &outs, TrainingModel &models) {
    models.write_model(outs);
    return outs;
}

