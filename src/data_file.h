//
// Created by Asha Agrawal on 3/12/2018.
//

#ifndef NAIVEBAYES_DATA_FILE_H
#define NAIVEBAYES_DATA_FILE_H

#include "feature_vector.h"

class Data_File {
    static std::vector <std::pair<int, Feature_Vector>> images;
private:
public:
    /**
     * constructor for Data_File
     * basically, I have a single data_file for the entire project, and will push feature_vectors into it once its read
     * and I will map it to its classification (the int in the pair)
     */
    Data_File::data_file();

    /**
     * finds the associated classification name for a specific feature_vector
     * @param feature the feature_vector that we want to find the classification for
     * @return the classification of the specific vector [0-9]
     */
    int findClassification(Feature_Vector feature);

};

#endif //NAIVEBAYES_DATA_FILE_H
