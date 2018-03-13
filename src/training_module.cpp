//
// Created by Asha Agrawal on 3/12/2018.
//

#include "training_module.h"
#include "feature_vector.h"
#include <fstream>
#include <iostream>
#include <iomanip>

std::vector <std::vector<std::vector>> probabilities;
std::vector<std::vector<std::vector>> module;
std::vector<double> prior;

vector <std::pair<int, Feature_Vector>> read_file_input() {
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
    //go through images 10 times to find the all of the Frequency_Vectors with the specific classification
    for (int i = 0; i < 10; i++) {
        probabilities.search(i, images);
        prior.priors(i, images);
    }
}

void search(int classification, vector <std::pair<int, Feature_Vector>> images) {
    int classification_occurance_counter = 0;
    vector <std::vector<double>> cell_occurance_counter;

    //go through each Feature_Vector and Classification pair
    for (int i = 0; i < images.size(); i++) {

        //see if the classification of the pair is the one we are searching for
        if (images[i].first == classification) {
            classification_occurance_counter++;

            //now go through the entire Feature_Vector and get the number of occurances of a '1' for a specific cell
            for (int j = 0; j < images[i].second.size(); j++) {
                for (int k = 0; k < images[i].second.size(); k++) {
                    if (images[i][j][k] == 1) {
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
    //add these freshly computed probabilities to the 3D probabilities vector
    probabilities.push_back(cell_occurance_counter);
}

std::vector<double> priors(int classification, vector <std::pair<int, Feature_Vector>> images) {
    double classification_occurance_counter = 0;

    //go through each Feature_Vector and Classification pair
    for (int i = 0; i < images.size(); i++) {

        //see if the classification of the pair is the one we are searching for
        if (images[i].first == classification) {
            classification_occurance_counter++;
        }
    }
    prior.push_back(classification_occurance_counter / images.size());
    return prior;
}

std::vector<std::pair<int, double>> calculate_posterior_probability(std::vector<std::vector<std::vector>> module,
                                                                    std::vector<double> prior) {
    std::vector<std::pair<int, double>> posteriors;
    double posterior_probability = 0;
    for (int i = 0; i < 10; i++) {
        posterior_probability += prior[i];
        for (int j = 0; j<28; j++) {
            for (int k = 0; k < 28; k++) {
                posterior_probability += std::log(module[j][k]);
            }
        }
        std::pair<int, double> pairs;
        pairs.first = i;
        pairs.second = posterior_probability;
        posteriors.push_back(pairs);
    }
    return posteriors;
}

void Training_Module::read_module(std::istream &ins) {
    for (int k = 0; k < 10; k++) {
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                double input;
                ins >> input;
                module[k][i][j].push_back(input);
            }
        }
    }
}

void Training_Module::write_module(std::ostream &outs) {
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

istream &operator>>(std::istream &ins, Training_Module& model) {
    model.read_module(ins);
    return ins;
}

ostream &operator<<(std::ostream &outs, Training_Module& model) {
    model.write_module(outs);
    return outs;
}

