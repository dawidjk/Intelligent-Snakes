//
//  NeuralNetworks.cpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/8/19.
//

#include "NeuralNetworks.hpp"

void NeuralNetworks::setup() {
    for (int i = 0; i < NETWORKS; i++) {
        //NeuralNetwork temp_network(6,5,3);
        //neural_networks_.push_back(temp_network);
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
    
    is_alive_ = true;
    return false;
}

int NeuralNetworks::getGeneration() {
    return current_generation_;
}

double NeuralNetworks::reward(double reward) {
    return neural_rewards_[current_network_] += reward;
}

int NeuralNetworks::getNextMove(bool wall_straight, bool wall_left, bool wall_right, bool food_straight, bool food_left, bool food_right) {
    //OpenNN::Vector<double> inputs(INPUT_LAYER, 0.0);
    //OpenNN::Vector<double> outputs(OUTPUT_LAYER, 0.0);
    
    //outputs = neural_networks_[current_network_] .get_multilayer_perceptron_pointer() ->calculate_outputs(inputs);
    
    return std::rand() % 4;//outputs.calculate_maximal_index();
}

void NeuralNetworks::kill() {
    is_alive_ = false;
}

NeuralNetworks::~NeuralNetworks() {
    //neural_networks_.clear();
    neural_rewards_.clear();
}
