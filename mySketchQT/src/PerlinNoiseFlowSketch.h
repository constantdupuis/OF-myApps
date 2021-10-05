#pragma once

#include "SubSketchBase.h"
#include "ofxValueGrid.h"
#include "PerlinFlowCellData.h"

class PerlinNoiseFlowSketch : public SubSketchBase
{
public:
	void setup() {
		valueGrid_ = make_shared<ofxValueGrid<PerlinFlowCellData>>(10,10,200,200, glm::vec2(.5f,.5f));
	}
	
	void update() {
	}
	
	void draw() {
	}

	void windowResized(int w, int h) {
	}

private:
	shared_ptr<ofxValueGrid<PerlinFlowCellData>> valueGrid_;
};

