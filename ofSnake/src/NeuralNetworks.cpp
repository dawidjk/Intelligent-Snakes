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
    
    //std::cout << getLastScore() << std::endl;
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

double NeuralNetworks::getScore() {
    return neural_rewards_[current_network_];
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
        parents_.push_back(scores.at(i));
        //std::cout << scores.at(i).first << std::endl;
    }
    
    for (int i = 0; i < parents_.size(); ++i) {
        neural_networks_.at(i) = parents_.at(i).second;
    }
}

tiny_dnn::network<tiny_dnn::sequential> NeuralNetworks::pickParent() {
    int total_score = 0;
    
    for (int i = 0; i < parents_.size(); ++i) {
        total_score += parents_.at(i).first;
    }
    
    int parent_score = std::rand() % total_score;
    int cumulative_score = 0;
    
    for (int i = 0; i < parents_.size(); ++i) {
        cumulative_score += parents_.at(i).first;
        
        if (cumulative_score >= parent_score) {
            return parents_.at(i).second;
        }
    }
    
    return parents_.at(parents_.size() - 1).second;
}

void NeuralNetworks::breedParents() {
    for (int i = (int) parents_.size(); i < NETWORKS; i += 2) { // Loop through each NN
        for (int j = 0; j < parents_.at(0).second.depth(); ++j) {
            std::vector<tiny_dnn::vec_t*> parent_one;
            std::vector<tiny_dnn::vec_t*> parent_two;
            parent_one = pickParent()[j]->weights();
            parent_two = pickParent()[j]->weights();
            
            if (parent_one.size() == 0 || parent_two.size() == 0) {
                continue;
            }
            
            std::vector<std::vector<float>> layers;
            
            for (int len = 0; len < 2; ++len) {
                std::vector<float> temp_vec;
                layers.push_back(temp_vec);
            }
            
            for (int k = 0; k < parent_one.at(0)->size(); ++k) {
                int child_layer_one = 0;
                int child_layer_two = 1;
                
                if (getRandomDoublePositive() > 0.5) {
                    child_layer_one = 1;
                    child_layer_two = 0;
                }
                
                layers.at(child_layer_one).push_back(parent_one.at(0)->at(k));
                layers.at(child_layer_two).push_back(parent_two.at(0)->at(k));
                
                if (getRandomDoublePositive() < MUTATION_RATE) {
                    layers.at(child_layer_one).at(k) = getRandomDouble();
                }
                
                if (getRandomDoublePositive() < MUTATION_RATE) {
                    layers.at(child_layer_two).at(k) = getRandomDouble();
                }
            }
            
            for (int depth = 0; depth < 2; ++depth) {
                if (depth == 1 && i + depth >= NETWORKS) {
                    break;
                }
                
                std::string network_string = neural_networks_.at(i + depth).to_json(tiny_dnn::content_type::weights);
                
                rapidjson::Document json_doc;
                json_doc.Parse<rapidjson::kParseDefaultFlags>(network_string.c_str());
                
                std::string weight_index = "value" + std::to_string(j);
                
                rapidjson::Value& weights = json_doc[weight_index.c_str()]["value0"];
                
                int count = 0;
                
                for (rapidjson::Value::ValueIterator itr = weights.Begin(); itr != weights.End(); ++itr) {
                    itr->SetDouble(layers.at(depth).at(count++));
                }
            
                // write json_doc to string and load to nn
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                json_doc.Accept(writer);
                
                neural_networks_.at(i + depth).from_json(buffer.GetString(), tiny_dnn::content_type::weights);
            }
        }
    }
    
    //std::cout << getGeneration() << std::endl;
}

double NeuralNetworks::getRandomDouble(){
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(-1, 1); // rage 0 - 1
    return dis(e);
}

double NeuralNetworks::getRandomDoublePositive(){
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(0, 1); // rage 0 - 1
    return dis(e);
}

NeuralNetworks::~NeuralNetworks() {
    neural_networks_.clear();
    neural_rewards_.clear();
}

int NeuralNetworks::getCurrentSnake() {
    return current_network_;
}

void NeuralNetworks::save() {
    for (int i = 0; i < NETWORKS; ++i) {
        neural_networks_.at(i).save(SAVE_PATH + std::to_string(i));
    }
}
