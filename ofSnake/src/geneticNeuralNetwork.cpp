//
//  geneticNeuralNetwork.cpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/7/19.
//

#include "geneticNeuralNetwork.hpp"
#include <ApplicationServices/ApplicationServices.h>

int GeneticNN::getNextMove() {
    
    switch (std::rand() % 4) {
        case 0:
            //std::cout << "w" << std::endl;
            return 'w';
        case 1:
            //std::cout << "a" << std::endl;
            return 'a';
        case 2:
            //std::cout << "s" << std::endl;
            return 's';
        case 3:
            //std::cout << "d" << std::endl;
            return 'd';
            
        default:
            //std::cout << "default" << std::endl;
            return 'd';
    }
}
