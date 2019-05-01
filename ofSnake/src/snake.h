#include "ll.h"
#include "ofMain.h"
#include "snakebody.h"
#pragma once

namespace snakelinkedlist {
    typedef enum {
        UP = 0,
        DOWN,
        RIGHT,
        LEFT
    } SnakeDirection;

    struct SnakeBody {
        SnakeBody* next;
        ofVec2f position;
        ofColor color;
    };

    class Snake {
        private:
            bool isDeadPredictor(SnakeBody *head);
            SnakeDirection current_direction_;
            ofVec2f screen_dims_;
            static const float kbody_size_modifier_;
            ofVec2f body_size_;
            SnakeBody* head_;
            cs126linkedlist::LinkedList<int> snake_body;

        public:
            SnakeBody* getHead() const;
            Snake();
            Snake& operator=(const Snake& other);
            ~Snake();
            ofVec2f getBodySize() const;
            bool isDead() const;
            void update();
            void eatFood(ofColor new_body_color);
            void resize(int w, int h);
            int getFoodEaten() const;
            SnakeDirection getDirection() const;
            char getDirectionChar() const;
            void setDirection(SnakeDirection new_direction);
            bool isStraightSafe();
            bool isLeftSafe();
            bool isRightSafe();
            bool isFoodStraight(ofRectangle food);
            bool isFoodLeft(ofRectangle food);
            bool isFoodRight(ofRectangle food);
    };
}
