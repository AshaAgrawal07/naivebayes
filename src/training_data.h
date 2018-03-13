//
// Created by Asha Agrawal on 3/12/2018.
//

#ifndef NAIVEBAYES_TRAINING_DATA_H
#define NAIVEBAYES_TRAINING_DATA_H
class Training_Data {

public:
    /**
     * reads the files and helps in training or testing
     * it depends on the file that is inputted
     * it will output an error message if the file does not exist/cannot be accessed
     *
     * it will create a vector of pairs of a Feature_Vectors with its corresponding classification as an int
     */
    void read_input();
};
#endif //NAIVEBAYES_TRAINING_DATA_H
