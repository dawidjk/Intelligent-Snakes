#include "snake.h"

using namespace snakelinkedlist;

const float Snake::kbody_size_modifier_ = 0.02;

SnakeBody* Snake::getHead() const {
	return head_;
};

ofVec2f Snake::getBodySize() const {
	return body_size_;
};

Snake::Snake() {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();
	screen_dims_.set(width, height);

	float body_d = kbody_size_modifier_ * width;
	body_size_.set(body_d, body_d);

	current_direction_ = RIGHT;

	head_ = new SnakeBody();
	head_->position.set(0, 2 * body_d);
	head_->color = ofColor(0, 200, 0);
	head_->next = nullptr;
}

Snake& Snake::operator=(const Snake& other) {
	screen_dims_ = other.screen_dims_;
	body_size_ = other.body_size_;

	snake_body.clear();
	current_direction_ = RIGHT;

	head_ = new SnakeBody();

	SnakeBody* curr = head_;
	SnakeBody* other_body = other.head_;
	while (other_body) {
		curr->position = other_body->position;
		curr->color = other_body->color;
        
		if (other_body->next) {
			curr->next = new SnakeBody();
		}

		curr = curr->next;
		other_body = other_body->next;
	}

	return *this;
}

Snake::~Snake() {
	SnakeBody* curr = head_;
    
	while (curr) {
		SnakeBody* next = curr->next;
		delete curr;
		curr = next;
	}
}

void Snake::update() {
	SnakeBody* prev = head_;
	SnakeBody* curr = head_->next;
	ofVec2f curr_old_pos = head_->position;
    
	while (curr) {
		ofVec2f old_pos_temp = curr->position;
		curr->position = curr_old_pos;
		curr_old_pos = old_pos_temp;

		prev = curr;
		curr = curr->next;
	}

	switch (current_direction_) {
		case UP:
			head_->position.set(head_->position.x, head_->position.y - body_size_.y);
			break;
		case DOWN:
			head_->position.set(head_->position.x, head_->position.y + body_size_.y);
			break;
		case LEFT:
			head_->position.set(head_->position.x - body_size_.x, head_->position.y);
			break;
		case RIGHT:
			head_->position.set(head_->position.x + body_size_.x, head_->position.y);
			break;
	}
}

bool Snake::isDead() const {
	if (head_->position.x < 0
		|| head_->position.y < 0
		|| head_->position.x > screen_dims_.x - body_size_.x
		|| head_->position.y > screen_dims_.y - body_size_.y) {
		return true;
	}
    
	ofRectangle head_rect(head_->position.x, head_->position.y, body_size_.x, body_size_.y);
    
	for (SnakeBody* curr = head_->next; curr; curr = curr->next) {
		ofRectangle body_rect(curr->position.x, curr->position.y, body_size_.x, body_size_.y);
        
		if (head_rect.intersects(body_rect)) {
			return true;
		}
	}
    
	return false;
}

bool Snake::isDeadPredictor(SnakeBody *head) {
    if (head->position.x < 0
        || head->position.y < 0
        || head->position.x > screen_dims_.x - body_size_.x
        || head->position.y > screen_dims_.y - body_size_.y) {
        return true;
    }

    if (head->next == nullptr || head->next->next == nullptr) {
        return false;
    }

    ofRectangle head_rect(head->position.x, head->position.y, body_size_.x, body_size_.y);
    
    for (SnakeBody* curr = head->next->next; curr->next; curr = curr->next) {
        ofRectangle body_rect(curr->position.x, curr->position.y, body_size_.x, body_size_.y);
        
        if (head_rect.intersects(body_rect)) {
            return true;
        }
    }

    return false;
}

bool Snake::isStraightSafe() {
    SnakeBody *temp_head = new SnakeBody();
    temp_head->next = head_;
    temp_head->color = head_->color;
    ofVec2f temp_vec;
    
    switch (current_direction_) {
        case UP:
            temp_vec.set(head_->position.x, head_->position.y - body_size_.y);
            break;
            
        case DOWN:
            temp_vec.set(head_->position.x, head_->position.y +  body_size_.y);
            break;
            
        case LEFT:
            temp_vec.set(head_->position.x -  body_size_.x, head_->position.y);
            break;
            
        case RIGHT:
            temp_vec.set(head_->position.x + body_size_.x, head_->position.y);
            break;
    }
    
    temp_head->position = temp_vec;
    return isDeadPredictor(temp_head);
}

bool Snake::isLeftSafe() {
    SnakeBody *temp_head = new SnakeBody();
    temp_head->next = head_;
    temp_head->color = head_->color;
    ofVec2f temp_vec;
    
    switch (current_direction_) {
        case UP:
            temp_vec.set(head_->position.x - body_size_.x, head_->position.y);
            break;
            
        case DOWN:
            temp_vec.set(head_->position.x + body_size_.x, head_->position.y);
            break;
            
        case LEFT:
            temp_vec.set(head_->position.x, head_->position.y + body_size_.y);
            break;
            
        case RIGHT:
            temp_vec.set(head_->position.x, head_->position.y - body_size_.y);
            break;
    }
    
    temp_head->position = temp_vec;
    return isDeadPredictor(temp_head);
}

bool Snake::isRightSafe() {
    SnakeBody *temp_head = new SnakeBody();
    temp_head->next = head_;
    temp_head->color = head_->color;
    ofVec2f temp_vec;
    
    switch (current_direction_) {
        case UP:
            temp_vec.set(head_->position.x + body_size_.x, head_->position.y);
            break;
            
        case DOWN:
            temp_vec.set(head_->position.x - body_size_.x, head_->position.y);
            break;
            
        case LEFT:
            temp_vec.set(head_->position.x, head_->position.y - body_size_.y);
            break;
            
        case RIGHT:
            temp_vec.set(head_->position.x, head_->position.y + body_size_.y);
            break;
    }
    
    temp_head->position = temp_vec;
    return isDeadPredictor(temp_head);
}

bool Snake::isFoodStraight(ofRectangle food) {
    if (head_ == nullptr || body_size_.y < 0) {
        return false;
    }
    
    ofRectangle head_rect(head_->position.x, head_->position.y, body_size_.x, body_size_.y);
    bool intersects = false;
    bool straight = false;
    
    switch (current_direction_) {
        case UP:
            intersects = food.intersects(head_rect.getTopLeft(), head_rect.getTopRight());
            straight = head_rect.getTopLeft().y > food.getBottomLeft().y;
            return intersects || straight;
            
        case DOWN:
            intersects = food.intersects(head_rect.getTopLeft(), head_rect.getTopRight());
            straight = head_rect.getBottomLeft().y < food.getTopLeft().y;
            return intersects || straight;
            
        case LEFT:
            intersects = food.intersects(head_rect.getTopLeft(), head_rect.getBottomLeft());
            straight = head_rect.getBottomLeft().x > food.getBottomRight().x;
            return intersects || straight;
            
        case RIGHT:
            intersects = food.intersects(head_rect.getTopLeft(), head_rect.getBottomLeft());
            straight = head_rect.getBottomRight().x < food.getBottomLeft().x;
            return intersects || straight;
    }
    
    return false;
}

bool Snake::isFoodLeft(ofRectangle food) {
    ofRectangle head_rect(head_->position.x, head_->position.y, body_size_.x, body_size_.y);
    
    switch (current_direction_) {
        case UP:
            return head_rect.getX() > food.getX();
            
        case DOWN:
            return head_rect.getX() < food.getX();
            
        case LEFT:
            return head_rect.getY() < food.getY();
            
        case RIGHT:
            return head_rect.getY() > food.getY();
    }
    
    return false;
}

bool Snake::isFoodRight(ofRectangle food) {
    ofRectangle head_rect(head_->position.x, head_->position.y, body_size_.x, body_size_.y);
    
    switch (current_direction_) {
        case UP:
            return head_rect.getX() < food.getX();
            
        case DOWN:
            return head_rect.getX() > food.getX();
            
        case LEFT:
            return head_rect.getY() > food.getY();
            
        case RIGHT:
            return head_rect.getY() < food.getY();
    }
    
    return false;
}

void Snake::eatFood(ofColor newBodyColor) {
	snake_body.push_back(1);
	SnakeBody* new_body = new SnakeBody();
	new_body->color = newBodyColor;
	new_body->next = nullptr;
	SnakeBody* last_body = head_;
    
	while (last_body->next) {
		last_body = last_body->next;
	}

	switch (current_direction_) {
		case UP:
			new_body->position.set(last_body->position.x, last_body->position.y + body_size_.y);
			break;
		case DOWN:
			new_body->position.set(last_body->position.x, last_body->position.y - body_size_.y);
			break;
		case LEFT:
			new_body->position.set(last_body->position.x + body_size_.x, last_body->position.y);
			break;
		case RIGHT:
			new_body->position.set(last_body->position.x - body_size_.x, last_body->position.y);
			break;
	}

	last_body->next = new_body;
}

void Snake::resize(int w, int h) {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();

	for (SnakeBody* curr = head_; curr != NULL; curr = curr->next) {
		float new_x = ((curr->position.x / screen_dims_.x) * w);
		float new_y = ((curr->position.y / screen_dims_.y) * h);
		curr->position.set(new_x, new_y);
	}
    
	screen_dims_.set(width, height);

	float body_d = kbody_size_modifier_ * width;
	body_size_.set(body_d, body_d);
}

int Snake::getFoodEaten() const {
	return snake_body.size();
}

SnakeDirection Snake::getDirection() const {
	return current_direction_;
}

char Snake::getDirectionChar() const {
    switch (current_direction_) {
        case UP:
            return 'w';
        case DOWN:
            return 's';
        case LEFT:
            return 'a';
        case RIGHT:
            return 'd';
    }
    
    return 'd';
}

void Snake::setDirection(SnakeDirection newDirection) {
	current_direction_ = newDirection;
}
