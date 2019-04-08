//
//  geneticNeuralNetwork.hpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/7/19.
//

#ifndef geneticNeuralNetwork_hpp
#define geneticNeuralNetwork_hpp

#define NUM_GENERATIONS
#define MUTATION_PERCENT 20
#define NETWORKS 25
#define INPUT_LAYER 6
#define INNER_LAYER 5
#define OUTPUT_LAYER 3
#define DIRECTIONS 4
#define REWARD_POSITIVE 1
#define REWARD_NEGATIVE -1.5
#define REWARD_FOOD 10

#include <stdio.h>
#include <vector>
#include "opennn/opennn.h"

class GeneticNN {
    std::vector<OpenNN::NeuralNetwork> neural_networks_;
    std::vector<int> neural_rewards_;
    int current_netowrk_ = 0;
    
    char directions_[DIRECTIONS] = {'w', 'd', 's', 'a'};
    int current_direction_ = 1;
    char turnLeft();
    char turnRight();
    char goStraight();
    
public:
    int getNextMove();
    void setup();
};

#endif /* geneticNeuralNetwork_hpp */
