//
//  NeuralNetworks.hpp
//  ofIntelligentSnake
//
//  Created by David Kluszczynski on 4/8/19.
//

#ifndef NeuralNetworks_hpp
#define NeuralNetworks_hpp

#define BREED_PERCENT 0.1
#define MUTATION_RATE 0.05
#define NETWORKS 100
#define INPUT_LAYER 6
#define INNER_LAYER 5
#define OUTPUT_LAYER 3
#define LAYER_SIZE 2
#define HALF_CHANCE 0.5
#define SIGMOID_LOW -1
#define SIGMOID_HIGH 1
#define NORMAL_LOW 0
#define NORMAL_HIGH 1

#define SAVE_PATH "/Users/dave07747/Documents/CS126/final-project-dawidjk/smart_snake/"
#define SAVE_FILE "/Users/dave07747/Documents/CS126/final-project-dawidjk/smart_snake/save.json"
#define WEIGHT_NAME "value"
#define TARGET_WEIGHT "value0"
#define GENERATION_TEXT "Generation"
#define LOAD_FAIL "Could not save JSON file!"

#include <iostream>
#include <vector>
#include <fstream>

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
    void modifyWeights(int index_out, int index_in, std::vector<std::vector<float>> layers);
    double getRandomDouble();
    double getRandomDoublePositive();
    tiny_dnn::network<tiny_dnn::sequential> pickParent();

public:
    ~NeuralNetworks();
    void setup();
    int getNextMove(bool wall_s, bool wall_l, bool wall_r, bool food_s, bool food_l, bool food_r);
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
    void load();
};

#endif
