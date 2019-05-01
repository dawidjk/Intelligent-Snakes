#include "ofApp.h"
#include <iostream>

using namespace snakelinkedlist;

// Setup method
void snakeGame::setup(){
	ofSetWindowTitle("Intelligent Snake");

	srand(static_cast<unsigned>(time(0))); // Seed random with current time
    genetic_algorithm.setup();
}

void snakeGame::update() {
	if (should_update_) {
		if (current_state_ == IN_PROGRESS) {
			ofVec2f snake_body_size = game_snake_.getBodySize();
			ofVec2f head_pos = game_snake_.getHead()->position;

			ofRectangle snake_rect(head_pos.x, head_pos.y, snake_body_size.x, snake_body_size.y);
        
			if (snake_rect.intersects(game_food_.getFoodRect())) {
				game_snake_.eatFood(game_food_.getColor());
				game_food_.rebase();
                genetic_algorithm.ateFood();
			}
            
			game_snake_.update();
			
			if (game_snake_.isDead()) {
				current_state_ = FINISHED;
                genetic_algorithm.kill();
			}
		}
	}
    
    should_update_ = true;
    
    if (!genetic_algorithm.isBreeding() && current_state_ != PAUSED) {
        char next_move = genetic_algorithm.getNextMove( game_snake_.isStraightSafe(), game_snake_.isLeftSafe(), game_snake_.isRightSafe(), game_snake_.isFoodStraight(game_food_.getFoodRect()), game_snake_.isFoodLeft(game_food_.getFoodRect()), game_snake_.isFoodRight(game_food_.getFoodRect()));
        
        if (next_move != game_snake_.getDirectionChar()) {
            keyPressed(next_move);
        }
    }
}

void snakeGame::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
	if(current_state_ == PAUSED) {
		drawGamePaused();
	}
	else if(current_state_ == FINISHED) {
		drawGameOver();
	}
	drawFood();
	drawSnake();
    drawGeneration();
    drawScore();
    drawHighScore();
    drawCurrentSnake();
    drawAverageScore();
}

void snakeGame::keyPressed(int key){
	if (key == OF_KEY_F12) {
		ofToggleFullscreen();
		return;
	}
    
	int upper_key = toupper(key);
    
    if (key == '1') {
        genetic_algorithm.save();
    }
    
    if (upper_key == 'L') {
        genetic_algorithm.load();
    }

    if (upper_key == 'R') {
        total_score += game_snake_.getFoodEaten();
        
        if (game_snake_.getFoodEaten() > longest_body_) {
            longest_body_ = game_snake_.getFoodEaten();
        }
        
        reset();
    }
    
	if (upper_key == 'P' && current_state_ != FINISHED) {
		current_state_ = (current_state_ == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
	} else if (current_state_ == IN_PROGRESS) {
		SnakeDirection current_direction = game_snake_.getDirection();

		if (upper_key == 'W' && current_direction != DOWN && current_direction != UP) {
			game_snake_.setDirection(UP);
			update();
			should_update_ = false;
		} else if (upper_key == 'A' && current_direction != RIGHT && current_direction != LEFT) {
			game_snake_.setDirection(LEFT);
			update();
			should_update_ = false;
		} else if ((upper_key == 'S') && current_direction != UP && current_direction != DOWN) {
			game_snake_.setDirection(DOWN);
			update();
			should_update_ = false;
		} else if (upper_key == 'D' && current_direction != LEFT && current_direction != RIGHT) {
			game_snake_.setDirection(RIGHT);
			update();
			should_update_ = false;
		}
	}
}

void snakeGame::reset() {
	game_snake_ = Snake();
	game_food_.rebase();
	current_state_ = IN_PROGRESS;
}

void snakeGame::windowResized(int w, int h){
	game_food_.resize(w, h);
	game_snake_.resize(w, h);
}

void snakeGame::drawFood() {
	ofSetColor(game_food_.getColor());
	ofDrawRectangle(game_food_.getFoodRect());
}

void snakeGame::drawSnake() {
	ofVec2f snake_body_size = game_snake_.getBodySize();
	ofVec2f head_pos = game_snake_.getHead()->position;
	ofSetColor(game_snake_.getHead()->color);
	ofDrawRectangle(head_pos.x, head_pos.y, snake_body_size.x, snake_body_size.y);

	for (SnakeBody* curr = game_snake_.getHead(); curr != NULL; curr = curr->next) {
		ofVec2f currPos = curr->position;
		ofSetColor(curr->color);
		ofDrawRectangle(currPos.x, currPos.y, snake_body_size.x, snake_body_size.y);
	}
}

void snakeGame::drawGameOver() {
	string total_food = std::to_string(game_snake_.getFoodEaten());
	string lose_message = "You Lost! Final Score: " + total_food;
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(lose_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void snakeGame::drawGamePaused() {
	string pause_message = "P to Unpause!";
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void snakeGame::drawGeneration() {
    string generation_message = "Generation: " + std::to_string(genetic_algorithm.getGeneration());
    
    ofSetColor(255, 255, 255);
    ofTrueTypeFont font;
    ofRectangle text_rect = font.getStringBoundingBox(generation_message,0,0);

    ofDrawBitmapString(generation_message, 10, 20);
}

void snakeGame::drawScore() {
    string score_message = "Score: " + std::to_string(game_snake_.getFoodEaten());
    
    ofSetColor(255, 255, 255);
    ofTrueTypeFont font;
    ofRectangle text_rect = font.getStringBoundingBox(score_message,0,0);

    ofDrawBitmapString(score_message, 10, 35);
}

void snakeGame::drawHighScore() {
    string score_message = "High Score: " + std::to_string(longest_body_);
    
    ofSetColor(255, 255, 255);
    ofTrueTypeFont font;
    ofRectangle text_rect = font.getStringBoundingBox(score_message,0,0);
    
    ofDrawBitmapString(score_message, 10, 50);
}

void snakeGame::drawCurrentSnake() {
    string current_snake = "Current Snake: " + std::to_string(genetic_algorithm.getCurrentSnake());
    
    ofSetColor(255, 255, 255);
    ofTrueTypeFont font;
    ofRectangle text_rect = font.getStringBoundingBox(current_snake,0,0);
    
    ofDrawBitmapString(current_snake, 10, 65);
}

void snakeGame::drawAverageScore() {
    if (genetic_algorithm.getGeneration() != last_generation) {
        last_generation = genetic_algorithm.getGeneration();
        total_score = 0;
    }
    
    string average_score = "Average Generation Score: " + std::to_string(total_score / (genetic_algorithm.getCurrentSnake() + 1));
    
    ofSetColor(255, 255, 255);
    ofTrueTypeFont font;
    ofRectangle text_rect = font.getStringBoundingBox(average_score,0,0);
    
    ofDrawBitmapString(average_score, 10, 80);
}
