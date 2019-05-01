#pragma once

#include <iostream>
#include <vector>

namespace snakelinkedlist {
    class SnakeBodySegment {
        int data_;
    public:
        SnakeBodySegment() : data_(0) {};
        SnakeBodySegment(const int v) : data_(v) {};
        friend std::ostream& operator<<(std::ostream& os, const SnakeBodySegment& list);
        friend bool operator==(const SnakeBodySegment& lhs, const SnakeBodySegment& rhs);
        friend bool operator!=(const SnakeBodySegment& lhs, const SnakeBodySegment& rhs);
    };
    
}
