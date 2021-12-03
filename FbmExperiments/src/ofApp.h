#pragma once


#include "ofMain.h"
#include "libs/ofxValueGrid.h"


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
		ofxBasicValueGrid grid_;
		float view_ratio = 0.8;
		int cols_;
		int rows_;
		glm::vec2 translate_;

        float animation_ = 0.0f;
        float animation_speed_ = 0.001f;

		void on_resize();
		float fbm(float x, float y);
        float add( float x, float y);
		float mult(float x, float y);
};
