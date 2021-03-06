#pragma once

/*
* Template linux64
*/

#include "ofMain.h"

#include "SubSketchBase.h"

#include "PerlinNoiseFlowSketch.h"
#include "PerlinFlowFeatherColor.h"
#include "BronianMotionGrid.h"
#include "Trainees.h"
#include "DrawingTest.h"

#include "ofxValueGrid.h"
#include "CellWithSizeAndColor.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    private:

		unique_ptr<SubSketchBase> subSketch;
};
