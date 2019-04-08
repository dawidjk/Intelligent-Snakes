//
//  NeuralNetworks.cpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/8/19.
//

#include "NeuralNetworks.hpp"
void NeuralNetworks::setup() {
    for (int i = 0; i < NETWORKS; i++) {
        neural_networks_.push_back(OpenNN::NeuralNetwork(
                                                         INPUT_LAYER, INNER_LAYER, OUTPUT_LAYER));
        neural_rewards_.push_back(0);
    }
}

bool NeuralNetworks::isAlive() {
    if (is_alive_) {
        return true;
    }
    
    current_network_++;
    
    if (current_network_ >= NETWORKS) {
        current_generation_++;
        current_network_ = 0;
    }
    
    return false;
}

int NeuralNetworks::getGeneration() {
    return current_generation_;
}

double NeuralNetworks::reward(double reward) {
    return neural_rewards_[current_network_] += reward;
}

int NeuralNetworks::getNextMove(bool wall_straight, bool wall_left, bool wall_right, bool food_straight, bool food_left, bool food_right) {
    //TODO: predict direction and return corresponding int
    return 0;
}

