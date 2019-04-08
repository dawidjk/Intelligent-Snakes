//
//  geneticNeuralNetwork.hpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/7/19.
//

#ifndef geneticNeuralNetwork_hpp
#define geneticNeuralNetwork_hpp

#define INPUT_LAYER 8
#define INNER_LAYER 5
#define OUTPUT_LAYER 3
#define DIRECTIONS 4

#include <stdio.h>
#include "opennn/opennn.h"

class GeneticNN {
    OpenNN::Vector<OpenNN::NeuralNetwork> neural_networks_;
    char directions_[DIRECTIONS] = {'w', 'd', 's', 'a'};
    int current_direction_ = 1;
    char turnLeft();
    char turnRight();
    char goStraight();
    
public:
    int getNextMove();
    void generateNetStructure();
};

#endif /* geneticNeuralNetwork_hpp */
