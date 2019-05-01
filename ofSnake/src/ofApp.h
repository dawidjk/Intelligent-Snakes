#pragma once
#include <ctime>
#include <cstdlib>
#include <utility>

#include "ofMain.h"
#include "snake.h"
#include "SnakeFood.h"
#include "geneticNeuralNetwork.hpp"

namespace snakelinkedlist {

    enum GameState {
      IN_PROGRESS = 0,
      PAUSED,
      FINISHED
    };

    class snakeGame : public ofBaseApp {
    private:
        GeneticNeuralNetwork genetic_algorithm;
        GameState current_state_ = IN_PROGRESS;
        Snake game_snake_;
        SnakeFood game_food_;
        int longest_body_ = 0;
        double total_score = 0;
        int last_generation = 0;
        bool should_press_ = true;
        bool should_update_ = true;
        void drawFood();
        void drawSnake();
        void drawGameOver();
        void drawGamePaused();
        void drawGeneration();
        void drawScore();
        void drawHighScore();
        void drawCurrentSnake();
        void drawAverageScore();
        void reset();

    public:
        void setup();
        void update();
        void draw();
        void keyPressed(int key);
        void windowResized(int w, int h);
    };
}
