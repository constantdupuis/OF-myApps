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
	    std::vector<std::string> paper_formats_ {"A0","A1","A2","A3","A4","A5","A6","A7","A8"};
        bool show_ui_ = true;
        ofxImGui::Gui gui;
        bool show_imgui_demo_ = false;
        bool show_imgui_new_ = false;
        bool ui_show_codart_settings = true;
		bool ctrl_key_was_pressed_ = false;

        std::vector<shared_ptr<DrawerInfoAndFactoryBase>> drawers_;
        std::vector<std::string> drawers_names_;

		std::shared_ptr<CodArt> activeCodArt_;

        void setupApp();
        void setupImGui();
        void UIDrawMenu();
        void UIShowNewDialogs();
        void UICodArt();

};
