//
// Created by Asha on 3/27/2018.
//

#include "catch.hpp"
#include "../src/training_model.h"
#include "../src/feature_vector.h"
#include <vector>

TEST_CASE("feature_vector get tests") {
    FeatureVector featurevector;
    featurevector.feature.push_back({1, 0});
    featurevector.feature.push_back({0, 1});

    REQUIRE(featurevector.get_size() == 2);

    REQUIRE(featurevector.get_value(0, 0) == true);
    REQUIRE(featurevector.get_value(1, 0) == false);
    REQUIRE(featurevector.get_value(0, 1) == false);
    REQUIRE(featurevector.get_value(1, 1) == false);
}

TEST_CASE("feature_vector read tests" ) {
    //tried using this link:  https://stackoverflow.com/questions/35581186/how-to-test-class-reading-from-stdistream
    std::istringstream vector_to_test("#+  ##");
    FeatureVector featurevector;
    featurevector.read(vector_to_test);

    REQUIRE(featurevector.get_value(0, 0) == true);
    REQUIRE(featurevector.get_value(0, 1) == true);
    REQUIRE(featurevector.get_value(0, 2) == false);
    REQUIRE(featurevector.get_value(0, 3) == false);
    REQUIRE(featurevector.get_value(0, 4) == true);
    REQUIRE(featurevector.get_value(0, 5) == true);
}

TEST_CASE("training_model training, searching, and priors tests") {
    FeatureVector featurevector1;
    featurevector1.feature.push_back({1, 1});
    featurevector1.feature.push_back({0, 1});
    pair<int, FeatureVector> pair1;
    pair1.first = 7;
    pair1.second = featurevector1;

    FeatureVector featurevector2;
    featurevector2.feature.push_back({1, 0});
    featurevector2.feature.push_back({1, 0});
    pair<int, FeatureVector> pair2;
    pair2.first = 1;
    pair2.second = featurevector2;

    FeatureVector featurevector3;
    featurevector3.feature.push_back({0, 1});
    featurevector3.feature.push_back({0, 1});
    pair<int, FeatureVector> pair3;
    pair3.first = 1;
    pair3.second = featurevector3;

    vector<pair<int, FeatureVector>> images;
    images.push_back(pair1);
    images.push_back(pair2);
    images.push_back(pair3);

    TrainingModel trainer;
    vector<vector<double>> search_for_1 = {{.5, .5},{.5, .5}};
    vector<vector<double>> search_for_7 = {{.999001996, .999001996}, {.000998, .999001996}};
    REQUIRE(trainer.search(1, images) == search_for_1);
    REQUIRE(trainer.search(7, images) == search_for_7);

    //the resulting probability vectors for the other numbers (except 1 and 7) happen to equal that of search_for_1
    vector<vector<vector<double>>> trained_model = {search_for_1, search_for_1, search_for_1, search_for_1,
                                                    search_for_1, search_for_1, search_for_1, search_for_7,
                                                    search_for_1, search_for_1};
    REQUIRE(trainer.train_data_model(images) == trained_model);

    vector<double> prior= {0, .6667, 0, 0, 0, 0, 0, .3333, 0, 0};
    REQUIRE(trainer.priors(images) == prior);
}

TEST_CASE("calculate_posterior_probabilities tests") {
    FeatureVector featurevector1;
    featurevector1.feature.push_back({1, 1});
    featurevector1.feature.push_back({0, 1});
    pair<int, FeatureVector> pair1;
    pair1.first = 7;
    pair1.second = featurevector1;

    FeatureVector featurevector2;
    featurevector2.feature.push_back({1, 0});
    featurevector2.feature.push_back({1, 0});
    pair<int, FeatureVector> pair2;
    pair2.first = 1;
    pair2.second = featurevector2;

    FeatureVector featurevector3;
    featurevector3.feature.push_back({0, 1});
    featurevector3.feature.push_back({0, 1});
    pair<int, FeatureVector> pair3;
    pair3.first = 1;
    pair3.second = featurevector3;

    vector<pair<int, FeatureVector>> images;
    images.push_back(pair1);
    images.push_back(pair2);
    images.push_back(pair3);

    TrainingModel trainer;
    trainer.train_data_model(images);
    vector<double> prior = trainer.priors(images);

    FeatureVector featurevector4;
    featurevector4.feature.push_back({1, 1});
    featurevector4.feature.push_back({1, 1});

    REQUIRE(trainer.calculate_posterior_probability(featurevector4, prior)== 7);
}