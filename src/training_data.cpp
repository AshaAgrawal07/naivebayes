//
// Created by Asha Agrawal on 3/12/2018.
//

#include "training_data.h"
#include "feature_vector.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void read_input(){
    std::cout << "Input file to be read: " << std::endl;
    std::ifstream inFile;
    std::string file_name;
    std::istream ins;

    std::cin >> file_name;

    inFile.open(file_name);
        //check that file is valid
        if(!inFile) {
            std::cout << "Cannot open " << file_name << std::endl;
            std::exit(1);
        }
        while (inFile >> ins) {
            Feature_Vector feature;
            feature.read(ins);
        }
        inFile.close();
        std::cout << "Training complete" << std::endl;
    }




