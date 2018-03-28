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

TEST_CASE("training_model training and searching tests") {
    
}