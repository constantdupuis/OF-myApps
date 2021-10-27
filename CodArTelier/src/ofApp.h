#pragma once

/*
* Template linux64
*/

#include "ofMain.h"
#include "ofxImGui.h"
#include "CodArt/CodArt.h"
#include "CodArt/DrawerBase.h"
#include "CodArt/Drawers/Noise.h"

using namespace CodArTelier;

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
        bool show_ui_ = true;
        ofxImGui::Gui gui;
        bool show_imgui_demo_ = false;

        std::vector<shared_ptr<DrawerBase>> drawers_;

        void UIDrawMenu();
        void setupApp();

};
