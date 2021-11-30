#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"

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
		ofxImGui::Gui gui;
		
		ofxImGui::Settings guiSettings;

		std::vector<std::string> fbm_types {"normal", "turbulence", "ridge"};
		ofParameter<int> pFbm_types{ "Fbm types", 0, 0, 3 };
		ofParameter<int> pOctaves_nbr {"Octaves nbr", 1, 0, 20};

		ofParameterGroup pGroup_{"Parameters"};
		
};
