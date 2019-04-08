//
//  geneticNeuralNetwork.cpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/7/19.
//

#include "geneticNeuralNetwork.hpp"
#include <ApplicationServices/ApplicationServices.h>

int GeneticNN::getNextMove() {
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

char GeneticNN::turnLeft() {
    current_direction_--;
    if (current_direction_ < 0) {
        current_direction_ += DIRECTIONS;
    }
    return directions_[current_direction_];
}

char GeneticNN::turnRight() {
    current_direction_++;
    if (current_direction_ >= DIRECTIONS) {
        current_direction_ -= DIRECTIONS;
    }
    return directions_[current_direction_];
}

char GeneticNN::goStraight() {
    return directions_[current_direction_];
}
