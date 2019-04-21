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
    starve_count_++;
    
    if (starve_count_ > STARVE_LIMIT) {
        starve_count_ = 0;
        penaltyKill();
    }
    
    if (!neural_networks_.isAliveReset()) {
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
    if (last_action_ == DIRECTION_LEFT) {
        stuck_count_++;
    } else {
        stuck_count_ = 0;
    }
    
    if (stuck_count_ > STUCK_LIMIT) {
        penaltyKill();
    }
    
    current_direction_--;
    last_action_ = DIRECTION_LEFT;
    
    if (current_direction_ < 0) {
        current_direction_ += DIRECTIONS;
    }
    
    //std::cout << "Turning Left" << std::endl;
    
    return directions_[current_direction_];
}

char GeneticNeuralNetwork::turnRight() {
    if (last_action_ == DIRECTION_RIGHT) {
        stuck_count_++;
    } else {
        stuck_count_ = 0;
    }
    
    if (stuck_count_ > STUCK_LIMIT) {
        penaltyKill();
    }
    
    current_direction_++;
    last_action_ = DIRECTION_RIGHT;
    
    if (current_direction_ >= DIRECTIONS) {
        current_direction_ -= DIRECTIONS;
    }
    
    //std::cout << "Turning Right" << std::endl;
    
    return directions_[current_direction_];
}

char GeneticNeuralNetwork::goStraight() {
    stuck_count_ = 0;
    last_action_ = DIRECTION_STRAIGHT;
    
    //std::cout << "Going Straight" << std::endl;
    
    return directions_[current_direction_];
}

void GeneticNeuralNetwork::kill() {
    neural_networks_.kill();
}

void GeneticNeuralNetwork::penaltyKill() {
    neural_networks_.reward(PENALTY);
    neural_networks_.kill();
}

void GeneticNeuralNetwork::ateFood() {
    starve_count_ = 0;
    neural_networks_.reward(REWARD_FOOD);
}

bool GeneticNeuralNetwork::isAlive() {
    return neural_networks_.isAlive();
}

bool GeneticNeuralNetwork::isBreeding() {
    return neural_networks_.isBreeding();
}

double GeneticNeuralNetwork::getScore() {
    return neural_networks_.getScore();
}

int GeneticNeuralNetwork::getGeneration() {
    return neural_networks_.getGeneration();
}

int GeneticNeuralNetwork::getCurrentSnake() {
    return neural_networks_.getCurrentSnake();
}

void GeneticNeuralNetwork::save() {
    neural_networks_.save();
}

void GeneticNeuralNetwork::load() {
    neural_networks_.load();
}
