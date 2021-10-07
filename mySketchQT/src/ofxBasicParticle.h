#pragma once

#include "ofMain.h"

class ofxBasicParticle
{
public:
	ofxBasicParticle() {}
	ofxBasicParticle(glm::vec2 pos) { pos_ = pos; }
	ofxBasicParticle(float x, float y) { pos_.x = x; pos_.y = y; }
protected:
	glm::vec2 pos_;
};
