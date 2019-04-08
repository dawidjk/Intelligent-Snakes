//
//  NeuralNetworks.hpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/8/19.
//

#ifndef NeuralNetworks_hpp
#define NeuralNetworks_hpp

#define BREED_PERCENT 0.1
#define NETWORKS 60
#define INPUT_LAYER 6
#define INNER_LAYER 5
#define OUTPUT_LAYER 3

#include <vector>
#include "opennn/opennn.h"

class NeuralNetworks {
    std::vector<OpenNN::NeuralNetwork> neural_networks_;
    std::vector<double> neural_rewards_;
    int current_network_ = 0;
    bool is_alive_ = true;
    int current_generation_ = 0;

public:
    void setup();
    int getNextMove(bool wall_straight, bool wall_left, bool wall_right, bool food_straight, bool food_left, bool food_right);

    void kill();
    bool isAlive();
    int getGeneration();
    double reward(double reward);
};

#endif /* NeuralNetworks_hpp */
