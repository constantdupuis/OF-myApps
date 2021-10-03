#pragma once

#include "ofMain.h"
#include "ofxMQTT.h"
#include "ofxGui.h"
#include <list>

class ofApp : public ofBaseApp{

	public:
		ofxMQTT client;

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
		ofxPanel gui;
		float rotation = 0.0f;
		float rotationSpeed = 40.0f;
		std::list<ofPath> paths;		
		
};
