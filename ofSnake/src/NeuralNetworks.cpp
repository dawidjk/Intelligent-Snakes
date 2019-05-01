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
        temp_net << tiny_dnn::fully_connected_layer(INPUT_LAYER, INNER_LAYER);
        temp_net << tiny_dnn::activation::tanh();
        temp_net << tiny_dnn::fully_connected_layer(INNER_LAYER, OUTPUT_LAYER);
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

double NeuralNetworks::getScore() {
    return neural_rewards_[current_network_];
}

double NeuralNetworks::reward(double reward) {
    return neural_rewards_[current_network_] += reward;
}

int NeuralNetworks::getNextMove(bool wall_s, bool wall_l, bool wall_r, bool food_s, bool food_l, bool food_r) {
    tiny_dnn::vec_t input;
    
    input.push_back(wall_s);
    input.push_back(wall_l);
    input.push_back(wall_r);
    input.push_back(food_s);
    input.push_back(food_l);
    input.push_back(food_r);
    
    tiny_dnn::vec_t results = neural_networks_[current_network_].predict(input);
    
    return decodeNNResult(results);
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
    for (int i = (int) parents_.size(); i < NETWORKS; i += 2) {
        for (int j = 0; j < parents_.at(0).second.depth(); ++j) {
            std::vector<tiny_dnn::vec_t*> parent_one;
            std::vector<tiny_dnn::vec_t*> parent_two;
            parent_one = pickParent()[j]->weights();
            parent_two = pickParent()[j]->weights();
            
            if (parent_one.size() == 0 || parent_two.size() == 0) {
                continue;
            }
            
            std::vector<std::vector<float>> layers;
            
            for (int len = 0; len < LAYER_SIZE; ++len) {
                std::vector<float> temp_vec;
                layers.push_back(temp_vec);
            }
            
            for (int k = 0; k < parent_one.at(0)->size(); ++k) {
                int child_layer_one = 0;
                int child_layer_two = 1;
                
                if (getRandomDoublePositive() > HALF_CHANCE) {
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
            
            modifyWeights(i, j, layers);
        }
    }
}

void NeuralNetworks::modifyWeights(int index_out, int index_in, std::vector<std::vector<float>> layers) {
    for (int depth = 0; depth < LAYER_SIZE; ++depth) {
        if (depth == 1 && index_out + depth >= NETWORKS) {
            break;
        }
        
        std::string network_string = neural_networks_.at(index_out + depth).to_json(tiny_dnn::content_type::weights);
        
        rapidjson::Document json_doc;
        json_doc.Parse<rapidjson::kParseDefaultFlags>(network_string.c_str());
        
        std::string weight_index = WEIGHT_NAME + std::to_string(index_in);
        
        rapidjson::Value& weights = json_doc[weight_index.c_str()][TARGET_WEIGHT];
        
        int count = 0;
        
        for (rapidjson::Value::ValueIterator itr = weights.Begin(); itr != weights.End(); ++itr) {
            itr->SetDouble(layers.at(depth).at(count++));
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        json_doc.Accept(writer);
        
        neural_networks_.at(index_out + depth).from_json(buffer.GetString(), tiny_dnn::content_type::weights);
    }
}

double NeuralNetworks::getRandomDouble(){
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(SIGMOID_LOW, SIGMOID_HIGH);
    
    return dis(e);
}

double NeuralNetworks::getRandomDoublePositive(){
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(NORMAL_LOW, NORMAL_HIGH);
    
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
    
    rapidjson::Document save_doc;
    save_doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = save_doc.GetAllocator();
    
    save_doc.AddMember(GENERATION_TEXT, getGeneration(), allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    save_doc.Accept(writer);
    
    std::ofstream of (SAVE_FILE);
    of << buffer.GetString();
    
    if (!of.good()) {
        std::cout << LOAD_FAIL << std::endl;
    }
}

void NeuralNetworks::load() {
    for (int i = 0; i < NETWORKS; ++i) {
        neural_networks_.at(i).load(SAVE_PATH + std::to_string(i));
    }
    
    std::ifstream stream (SAVE_FILE);
    std::string json;
    stream >> json;
    
    rapidjson::Document load_doc;
    load_doc.Parse<rapidjson::kParseDefaultFlags>(json.c_str());
    
    rapidjson::Value& generation = load_doc[GENERATION_TEXT];
    current_generation_ = generation.GetInt();
}
