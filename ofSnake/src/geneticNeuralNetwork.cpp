//
//  geneticNeuralNetwork.cpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/7/19.
//

#include "geneticNeuralNetwork.hpp"
#include <ApplicationServices/ApplicationServices.h>

void GeneticAlgorithm::setup() {
    neural_networks_.setup();
}

int GeneticAlgorithm::getNextMove(
                                  bool wall_straight, bool wall_left, bool wall_right, bool food_straight, bool food_left, bool food_right) {
    if (!neural_networks_.isAlive()) {
        return 'r';
    }
    switch (std::rand() % 3) {
        case 0:
            //std::cout << "w" << std::endl;
            return goStraight();
        case 1:
            //std::cout << "a" << std::endl;
            return turnLeft();
        case 2:
            //std::cout << "s" << std::endl;
            return turnRight();
    }
    return goStraight();
}

char GeneticAlgorithm::turnLeft() {
    current_direction_--;
    if (current_direction_ < 0) {
        current_direction_ += DIRECTIONS;
    }
    return directions_[current_direction_];
}

char GeneticAlgorithm::turnRight() {
    current_direction_++;
    if (current_direction_ >= DIRECTIONS) {
        current_direction_ -= DIRECTIONS;
    }
    return directions_[current_direction_];
}

char GeneticAlgorithm::goStraight() {
    return directions_[current_direction_];
}

void GeneticAlgorithm::kill() {
    neural_networks_.kill();
}

void GeneticAlgorithm::ateFood() {
    neural_networks_.reward(REWARD_FOOD);
}
