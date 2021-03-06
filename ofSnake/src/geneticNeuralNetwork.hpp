//
//  geneticNeuralNetwork.hpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/7/19.
//

#ifndef geneticNeuralNetwork_hpp
#define geneticNeuralNetwork_hpp

#define DIRECTIONS 4
#define REWARD_POSITIVE 1
#define REWARD_NEGATIVE -1.5
#define REWARD_FOOD 10
#define PENALTY -500
#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT 2
#define DIRECTION_STRAIGHT 0
#define STUCK_LIMIT 50
#define STARVE_LIMIT 2000

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
    int getNextMove(bool wall_s, bool wall_l, bool wall_r, bool food_s, bool food_l, bool food_r);
    void setup();
    void kill();
    void ateFood();
    bool isAlive();
    bool isBreeding();
    void penaltyKill();
    double getScore();
    int getGeneration();
    int getCurrentSnake();
    void save();
    void load();
};

#endif
