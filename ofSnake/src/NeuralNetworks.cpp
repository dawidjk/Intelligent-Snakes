//
//  NeuralNetworks.cpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/8/19.
//

#include "NeuralNetworks.hpp"
const size_t k_input = 6;
const size_t k_inner = 5;
const size_t k_output = 3;

void NeuralNetworks::setup() {
    for (int i = 0; i < NETWORKS; i++) {
        //OpenNN::NeuralNetwork temp_network;
        //temp_network.set(INPUT_LAYER, INNER_LAYER, OUTPUT_LAYER);
        int temp_network = 0;
        neural_networks_.push_back(temp_network);
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
    //OpenNN::Vector<double> inputs(INPUT_LAYER, 0.0);
    //OpenNN::Vector<double> outputs(OUTPUT_LAYER, 0.0);
    
    //outputs = neural_networks_[current_network_] .get_multilayer_perceptron_pointer() ->calculate_outputs(inputs);
    
    return (int) 0;//outputs.calculate_maximal_index();
}

void NeuralNetworks::kill() {
    is_alive_ = false;
}

NeuralNetworks::~NeuralNetworks() {
    neural_networks_.clear();
    neural_rewards_.clear();
}
