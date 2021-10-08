#pragma once

#include "ofMain.h"

class ofxBasicParticle
{
public:
	ofxBasicParticle() {}
	ofxBasicParticle(glm::vec2 pos) { pos_ = pos; }
	ofxBasicParticle(float x, float y) { pos_.x = x; pos_.y = y; }
	glm::vec2& pos() { return pos_; };
	float& x() { return pos_.x; }
	float& y() { return pos_.y; }
protected:
	glm::vec2 pos_;
};
