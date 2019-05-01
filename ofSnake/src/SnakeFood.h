#pragma once
#include <random>
#include "ofMain.h"

namespace snakelinkedlist {
    class SnakeFood {
        private:
            ofVec2f window_dims_;
            std::mt19937 generator_;
            std::uniform_int_distribution<> dist_x_;
            std::uniform_int_distribution<> dist_y_;
            std::uniform_int_distribution<> dist_color_;
            static const float kfood_modifier_;
            static const int kcolor_lower_;
            static const int kcolor_upper_;
            ofRectangle food_rect_;
            ofColor color_;

        public:
            SnakeFood();
            void rebase();
            void resize(int w, int h);
            ofRectangle getFoodRect();
            ofColor getColor();
    };
}
