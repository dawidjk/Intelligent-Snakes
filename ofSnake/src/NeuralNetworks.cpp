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
        
        is_breeding_ = true;
        pickBestParents();
        breedParents();
        resetRewards();
        is_breeding_ = false;
    }
    
    is_alive_ = true;
    return false;
}

bool NeuralNetworks::isAlive() {
    return is_alive_;
}

bool NeuralNetworks::isBreeding() {
    return is_breeding_;
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

bool sortDesc(const std::pair<int, tiny_dnn::network<tiny_dnn::sequential>> &a,
               const std::pair<int, tiny_dnn::network<tiny_dnn::sequential>> &b) {
    return (a.first > b.first);
}

void NeuralNetworks::pickBestParents() {
    std::vector<std::pair<int, tiny_dnn::network<tiny_dnn::sequential>>> scores;
    
    for (int i = 0; i < NETWORKS; ++i) {
        scores.push_back(std::make_pair(neural_rewards_[i], neural_networks_[i]));
    }
    
    std::sort(scores.begin(), scores.end(), sortDesc);
    parents_.clear();
    
    for (int i = 0; i < NETWORKS * BREED_PERCENT; ++i) {
        parents_.push_back(scores.at(i).second);
        //std::cout << scores.at(i).first << std::endl;
    }
}

void NeuralNetworks::breedParents() {
    // Vector of Neural Networks
    for (int i = (int) parents_.size(); i < NETWORKS; i += 2) { // Loop through each NN
        // Choose random two parents
        int p_one = std::rand() % parents_.size();
        int p_two = std::rand() % parents_.size();
        
        while (p_one == p_two) {
            p_two = std::rand() % parents_.size();
        }
        
        std::cout << parents_[p_one].to_json(tiny_dnn::content_type::weights) << std::endl;
        // Loop through each layer of parents
        for (int j = 0; j < parents_.at(p_one).depth(); ++j) {
            std::vector<tiny_dnn::vec_t*> parent_one;
            std::vector<tiny_dnn::vec_t*> parent_two;
            parent_one = parents_[p_one][j]->weights();
            parent_two = parents_[p_two][j]->weights();
            
            if (parent_one.size() == 0 || parent_two.size() == 0) {
                continue;
            }
            
            std::vector<tiny_dnn::vec_t*> child_one_layer;
            std::vector<tiny_dnn::vec_t*> child_two_layer;
            
            std::vector<int> crossover_one;
            std::vector<int> crossover_two;
            
            for (int k = 0; k < parent_one.at(0)->size(); ++k) {
                crossover_one.push_back(k);
                crossover_two.push_back(k);
            }
            
            std::random_shuffle(crossover_one.begin(), crossover_one.end());
            std::random_shuffle(crossover_two.begin(), crossover_two.end());
            
            std::vector<std::pair<int, float>> shuffled_one;
            std::vector<std::pair<int, float>> shuffled_two;
            
            for (int x = 0; x < parent_one.at(0)->size(); ++x) {
                shuffled_one.push_back(std::make_pair(crossover_one.at(x), parent_one.at(0)->at(x)));
                shuffled_two.push_back(std::make_pair(crossover_two.at(x), parent_two.at(0)->at(x)));
            }
            
            std::sort(shuffled_one.begin(), shuffled_one.end());
            std::sort(shuffled_two.begin(), shuffled_two.end());
            
            tiny_dnn::vec_t* layer_one = new tiny_dnn::vec_t;
            tiny_dnn::vec_t* layer_two = new tiny_dnn::vec_t;
            
            for (int x = 0; x < shuffled_one.size()/2; ++x) {
                layer_one->push_back(shuffled_one.at(x).second);
                layer_two->push_back(shuffled_one.at(shuffled_one.size() - x - 1).second);
            }
            
            if (shuffled_one.size() % 2 == 1) {
                int middle = (int) shuffled_one.size()/2 + 1;
                layer_one->push_back(shuffled_one.at(middle).second);
            }
            
            for (int x = 0; x < shuffled_two.size()/2; x++) {
                layer_one->push_back(shuffled_two.at(x).second);
                layer_two->push_back(shuffled_two.at(shuffled_two.size() - x - 1).second);
            }
            
            if (shuffled_two.size() % 2 == 1) {
                int middle = (int) shuffled_two.size()/2 + 1;
                layer_two->push_back(shuffled_two.at(middle).second);
            }
            
            std::cout << std::endl;
            
            child_one_layer.push_back(layer_one);
            child_two_layer.push_back(layer_two);
        }
    }
    std::cout << "********" << std::endl;
}

NeuralNetworks::~NeuralNetworks() {
    neural_networks_.clear();
    neural_rewards_.clear();
}
