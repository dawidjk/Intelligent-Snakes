//
//  geneticNeuralNetwork.hpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/7/19.
//

#ifndef geneticNeuralNetwork_hpp
#define geneticNeuralNetwork_hpp

#define DIRECTIONS 4
#define NUM_GENERATIONS 1000
#define REWARD_POSITIVE 1
#define REWARD_NEGATIVE -1.5
#define REWARD_FOOD 10

#include "NeuralNetworks.hpp"

class GeneticNeuralNetwork {
    NeuralNetworks neural_networks_;
    char directions_[DIRECTIONS] = {'w', 'd', 's', 'a'};
    int current_direction_ = 1;
    char turnLeft();
    char turnRight();
    char goStraight();
    
public:
    int getNextMove(bool wall_straight, bool wall_left, bool wall_right, bool food_straight, bool food_left, bool food_right);
    void setup();
    void kill();
    void ateFood();
};

#endif /* geneticNeuralNetwork_hpp */
