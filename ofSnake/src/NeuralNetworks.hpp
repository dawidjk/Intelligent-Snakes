//
//  NeuralNetworks.hpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/8/19.
//

#ifndef NeuralNetworks_hpp
#define NeuralNetworks_hpp

#define BREED_PERCENT 0.1
#define MUTATION_RATE 0.01
#define NETWORKS 60
#define INPUT_LAYER 6
#define INNER_LAYER 5
#define OUTPUT_LAYER 3
#define SAVE_PATH "~/Documents/smart_snake/"

#include <iostream>
#include <vector>

#include "tiny_dnn/tiny_dnn/tiny_dnn.h"

class NeuralNetworks {
    std::vector<tiny_dnn::network<tiny_dnn::sequential>> neural_networks_;
    std::vector<std::pair<int, tiny_dnn::network<tiny_dnn::sequential>>> parents_;
    std::vector<double> neural_rewards_;
    int current_network_ = 0;
    bool is_alive_ = true;
    bool is_breeding_ = false;
    int current_generation_ = 0;
    int decodeNNResult(tiny_dnn::vec_t result);
    void pickBestParents();
    void breedParents();
    double getRandomDouble();
    double getRandomDoublePositive();
    tiny_dnn::network<tiny_dnn::sequential> pickParent();

public:
    ~NeuralNetworks();
    void setup();
    int getNextMove(bool wall_straight, bool wall_left, bool wall_right, bool food_straight, bool food_left, bool food_right);

    void kill();
    bool isAlive();
    bool isBreeding();
    bool isAliveReset();
    int getGeneration();
    double reward(double reward);
    double getScore();
    void resetRewards();
    int getCurrentSnake();
    void save();
};

#endif /* NeuralNetworks_hpp */
