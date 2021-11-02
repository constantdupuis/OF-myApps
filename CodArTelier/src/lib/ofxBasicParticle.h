#pragma once

#include "ofMain.h"

class ofxBasicParticle
{
public:

    ofxBasicParticle() {
        ofxBasicParticle(0.0f, 0.0f);
    }

    ofxBasicParticle(float x, float y) {
        pos_.x = x;
        pos_.y = y;
        prev_pos_ = pos_;
        velocity_ = glm::vec2(0.0f, 0.0f);
        acceleration_ = glm::vec2(0.0f, 0.0f);
    }

    ofxBasicParticle(glm::vec2 pos) {
        pos_ = pos;
        prev_pos_ = pos_;
        velocity_ = glm::vec2(0.0f, 0.0f);
        acceleration_ = glm::vec2(0.0f, 0.0f);
    }

    ofxBasicParticle(float x, float y, float velocity_x, float velocity_y) {
        pos_.x = x;
        pos_.y = y;
        prev_pos_ = pos_;
        velocity_.x = velocity_x;
        velocity_.y = velocity_y;
        acceleration_ = glm::vec2(0.0f, 0.0f);
    }

    ofxBasicParticle(glm::vec2 pos, glm::vec2 velocity) {
        pos_ = pos;
        prev_pos_ = pos_;
        velocity_ = velocity;
        acceleration_ = glm::vec2(0.0f, 0.0f);
    }

    ofxBasicParticle(float x, float y, float velocity_x, float velocity_y, float acceleration_x, float acceleration_y) {
        pos_.x = x;
        pos_.y = y;
        prev_pos_ = pos_;
        velocity_.x = velocity_x;
        velocity_.y = velocity_y;
        acceleration_.x = acceleration_x;
        acceleration_.y = acceleration_y;
    }

    ofxBasicParticle(glm::vec2 pos, glm::vec2 velocity, glm::vec2 acceleration) {
        pos_ = pos;
        prev_pos_ = pos_;
        velocity_ = velocity;
        acceleration_ = acceleration;
    }

    void update( float deltaTime )
    {
        if( dead_) return;
        velocity_ += acceleration_ * deltaTime;
        pos_ += velocity_;
        updateLife();
    }

    void update()
    {
        if( dead_) return;
        velocity_ += acceleration_;
        pos_ += velocity_;
        updateLife();
    }

    glm::vec2& pos() { return pos_; }
    float x() { return pos_.x; }
    float y() { return pos_.y; }
    glm::vec2& velocity() {return velocity_;}
    glm::vec2& acceleration() { return acceleration_;}

    void setLife(int start_life) {
        life_ = start_life_ = start_life;
        if( life_ > 0) dead_ = false;
    }
    int life() { return life_;}
    bool isDead() { return dead_;}
    void resurect( int new_life = -1){
        if( new_life == -1)
            setLife(new_life);
        else
            setLife(start_life_);
    }

protected:
	glm::vec2 pos_;
    glm::vec2 prev_pos_;
    glm::vec2 velocity_;
    glm::vec2 acceleration_;
    int life_ = std::numeric_limits<int>::max();
    int start_life_ = std::numeric_limits<int>::max();
    bool dead_ = false;
    float normalized_life_ = 1.0;

    void updateLife()
    {
       life_--;
       if( life_ == 0) dead_ = true;
       normalized_life_ = (float)life_/(float)start_life_;
    }
};
