//
//  geneticNeuralNetwork.cpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/7/19.
//

#include "geneticNeuralNetwork.hpp"
#include <ApplicationServices/ApplicationServices.h>

void GeneticNeuralNetwork::setup() {
    neural_networks_.setup();
}

int GeneticNeuralNetwork::getNextMove(
                                  bool wall_straight, bool wall_left, bool wall_right, bool food_straight, bool food_left, bool food_right) {
    if (!neural_networks_.isAlive()) {
        return 'r';
    }
    
    switch (neural_networks_.getNextMove(wall_straight, wall_left, wall_right, food_straight, food_left, food_right)) {
        case 0:
            if (food_straight) {
                neural_networks_.reward(REWARD_POSITIVE);
            } else {
                neural_networks_.reward(REWARD_NEGATIVE);
            }
            
            return goStraight();
            
        case 1:
            if (food_left) {
                neural_networks_.reward(REWARD_POSITIVE);
            } else {
                neural_networks_.reward(REWARD_NEGATIVE);
            }
            
            return turnLeft();
            
        case 2:
            if (food_right) {
                neural_networks_.reward(REWARD_POSITIVE);
            } else {
                neural_networks_.reward(REWARD_NEGATIVE);
            }
            
            return turnRight();
    }
    
    neural_networks_.reward(REWARD_NEGATIVE);
    return goStraight();
}

char GeneticNeuralNetwork::turnLeft() {
    current_direction_--;
    
    if (current_direction_ < 0) {
        current_direction_ += DIRECTIONS;
    }
    
    return directions_[current_direction_];
}

char GeneticNeuralNetwork::turnRight() {
    current_direction_++;
    
    if (current_direction_ >= DIRECTIONS) {
        current_direction_ -= DIRECTIONS;
    }
    
    return directions_[current_direction_];
}

char GeneticNeuralNetwork::goStraight() {
    return directions_[current_direction_];
}

void GeneticNeuralNetwork::kill() {
    neural_networks_.kill();
}

void GeneticNeuralNetwork::ateFood() {
    neural_networks_.reward(REWARD_FOOD);
}
