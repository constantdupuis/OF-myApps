#pragma once

/*
* Template linux64
*/

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"

#include "ofxEasel.h"

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
        ofxXmlSettings XML;
        ofxImGui::Gui gui;
        bool showImGuiDemoWin_ = false;

        ofxCanvas canvas_ = ofxCanvas();
        ofxCanvasViewer canvasViewer_;

        bool noscale_ = false;
        int marginx_ = 10;
        int marginy_ = 10;
        bool usezoom_ = false;
        float zoom_ = 1.0;

        void drawUI();
		
};
