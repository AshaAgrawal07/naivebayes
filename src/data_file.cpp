//
// Created by Asha Agrawal on 3/12/2018.
//

#include "data_file.h"

std::vector <std::pair<int, Feature_Vector>> images;

Data_File::data_file() {
    std::vector<std::pair<int, Feature_Vector>> data;
}

void push_back(Data_File image) {
    images.push_back(image);
}
