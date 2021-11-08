#pragma once

/*
* Template linux64
*/

#include "ofMain.h"
#include "ofxImGui.h"
#include "CodArt/CodArt.h"
#include "CodArt/CodArtDocument.h"
#include "CodArt/DrawerBase.h"
#include "CodArt/DrawerManager.h"
#include "CodArt/CodArtManager.h"
//#include "CodArt/Drawers/ArdoiseFbm.h"

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
        bool ui_show_imgui_demo_ = false;
        bool ui_show_new_dialog_ = false;
		bool ui_show_save_dialog_ = false;
        bool ui_show_open_dialog_ = false;

		bool ctrl_key_was_pressed_ = false;

		//TODO remove
        //DrawerManager drawer_manager_;

		CodArtManager codart_manager_;

        std::vector<shared_ptr<DrawerInfoAndFactoryBase>> drawers_;
        std::vector<std::string> drawers_names_;
        std::map<string, shared_ptr<DrawerInfoAndFactoryBase>> drawers_by_id_;

		std::shared_ptr<CodArt> activeCodArt_;
        CodArtDocument codArtDoc_;

        void setupApp();
        void setupImGui();
        void loadCodArt(ofxXmlSettings settings);
        void UIDrawMenu();
        void UIShowNewDialogs();
        void UIShowOpenDialogs();
		void UIShowMessageBoxes();
        void UICodArt();

};
