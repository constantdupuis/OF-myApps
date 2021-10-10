#pragma once

#include "ofMain.h"

class ofxBasicParticle
{
public:

    ofxBasicParticle() {
        ofxBasicParticle(0.0f, 0.0f);
    }

    ofxBasicParticle(float x, float y) {
        pos_ = glm::vec2(x, y);
    }

    ofxBasicParticle(glm::vec2 pos) {
        pos_ = pos;
        velocity_ = glm::vec2(0.0f, 0.0f);
        acceleration_ = glm::vec2(0.0f, 0.0f);
    }

    ofxBasicParticle(float x, float y, float velocity_x, float velocity_y) {
        pos_ = glm::vec2(x, y);
        velocity_ = glm::vec2(velocity_x, velocity_y);
        acceleration_ = glm::vec2(0.0f, 0.0f);
    }

    ofxBasicParticle(glm::vec2 pos, glm::vec2 velocity) {
        pos_ = pos;
        velocity_ = velocity;
        acceleration_ = glm::vec2(0.0f, 0.0f);
    }

    ofxBasicParticle(float x, float y, float velocity_x_, float velocity_y_, float acceleration_x, float acceleration_y) {
        pos_ = glm::vec2(x, y);
        velocity_ = glm::vec2(velocity_x_, velocity_y_);
        acceleration_ = glm::vec2(acceleration_x, acceleration_y);
    }

    ofxBasicParticle(glm::vec2 pos, glm::vec2 velocity, glm::vec2 acceleration) {
        pos_ = pos;
        velocity_ = velocity;
        acceleration_ = acceleration;
    }

    void update( float deltaTime )
    {
        velocity_ += acceleration_ * deltaTime;
        pos_ += velocity_;
    }

    void update()
    {
        velocity_ += acceleration_;
        pos_ += velocity_;
    }

    glm::vec2& pos() { return pos_; }
    float& x() { return pos_.x; }
    float& y() { return pos_.y; }

    glm::vec2& velocity() {return velocity_;}
    glm::vec2& acceleration() { return acceleration_;}

protected:
	glm::vec2 pos_;
    glm::vec2 velocity_;
    glm::vec2 acceleration_;
};
