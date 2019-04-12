//
//  NeuralNetworks.cpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/8/19.
//

#include "NeuralNetworks.hpp"

void NeuralNetworks::setup() {
    for (int i = 0; i < NETWORKS; i++) {
        tiny_dnn::network<tiny_dnn::sequential> temp_net;
        temp_net << tiny_dnn::fully_connected_layer(6, 5);
        temp_net << tiny_dnn::activation::tanh();
        temp_net << tiny_dnn::fully_connected_layer(5, 3);
        temp_net << tiny_dnn::activation::tanh();
        neural_networks_.push_back(temp_net);
        neural_rewards_.push_back(0);
    }
}

bool NeuralNetworks::isAliveReset() {
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

bool NeuralNetworks::isAlive() {
    return is_alive_;
}

int NeuralNetworks::getGeneration() {
    return current_generation_;
}

double NeuralNetworks::getLastScore() {
    int previous_network = current_network_ - 1;
    double reward;
    
    if (previous_network < 0) {
        previous_network = NETWORKS - 1;
        reward = neural_rewards_[previous_network];
        resetRewards();
    } else {
        reward = neural_rewards_[previous_network];
    }
    
    return neural_rewards_[previous_network];
}

double NeuralNetworks::reward(double reward) {
    return neural_rewards_[current_network_] += reward;
}

int NeuralNetworks::getNextMove(bool wall_straight, bool wall_left, bool wall_right, bool food_straight, bool food_left, bool food_right) {
    tiny_dnn::vec_t input;
    
    input.push_back(wall_straight);
    input.push_back(wall_left);
    input.push_back(wall_right);
    input.push_back(food_straight);
    input.push_back(food_left);
    input.push_back(food_right);
    
    tiny_dnn::vec_t results = neural_networks_[current_network_].predict(input);
    
    
    return decodeNNResult(results);
    //return std::rand() % 4;
}

int NeuralNetworks::decodeNNResult(tiny_dnn::vec_t result) {
    int direction = 0;
    double value = -1;
    
    for (int i = 0; i < result.size(); ++i) {
        if (result.at(i) > value) {
            value = result.at(i);
            direction = i;
        }
    }
    
    return direction;
}

void NeuralNetworks::kill() {
    is_alive_ = false;
}

void NeuralNetworks::resetRewards() {
    for (int i = 0; i < neural_rewards_.size(); ++i) {
        neural_rewards_[i] = 0;
    }
    
    current_generation_++;
}

NeuralNetworks::~NeuralNetworks() {
    neural_networks_.clear();
    neural_rewards_.clear();
}
