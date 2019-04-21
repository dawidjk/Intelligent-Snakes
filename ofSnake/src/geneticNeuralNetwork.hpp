//
//  geneticNeuralNetwork.hpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/7/19.
//

#ifndef geneticNeuralNetwork_hpp
#define geneticNeuralNetwork_hpp

#define DIRECTIONS 4
#define NUM_GENERATIONS 100
#define REWARD_POSITIVE 1
#define REWARD_NEGATIVE -1.5
#define REWARD_FOOD 50
#define PENALTY -150
#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT 2
#define DIRECTION_STRAIGHT 0
#define STUCK_LIMIT 50
#define STARVE_LIMIT 1000

#include "NeuralNetworks.hpp"

class GeneticNeuralNetwork {
    NeuralNetworks neural_networks_;
    char directions_[DIRECTIONS] = {'w', 'd', 's', 'a'};
    int current_direction_ = 1;
    int last_action_ = 0;
    int stuck_count_ = 0;
    int starve_count_ = 0;
    char turnLeft();
    char turnRight();
    char goStraight();
    
public:
    int getNextMove(bool wall_straight, bool wall_left, bool wall_right, bool food_straight, bool food_left, bool food_right);
    void setup();
    void kill();
    void ateFood();
    bool isAlive();
    bool isBreeding();
    void penaltyKill();
    double getScore();
    int getGeneration();
    int getCurrentSnake();
};

#endif /* geneticNeuralNetwork_hpp */
