//
//  geneticNeuralNetwork.hpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/7/19.
//

#ifndef geneticNeuralNetwork_hpp
#define geneticNeuralNetwork_hpp

#include <stdio.h>
#include "opennn/opennn.h"

class GeneticNN {
    OpenNN::Vector<OpenNN::NeuralNetwork> neural_networks;
    
public:
    int getNextMove();
};

#endif /* geneticNeuralNetwork_hpp */
