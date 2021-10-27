#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("CodarTelier");
    setupApp();
    gui.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    if( show_ui_)
    {
        gui.begin();

        UIDrawMenu();

        gui.end();
    }
}

void ofApp::UIDrawMenu()
{
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("New ...", "")) {

        }

        if (ImGui::MenuItem("Open ...", "")) {

        }

        if (ImGui::BeginMenu("Open recent ...", "")) {
            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("Save", "")) {

        }

        if (ImGui::MenuItem("Save As ...", "")) {

        }

        if (ImGui::MenuItem("Exit", "ALT+F4")) {
            //StopRendering();
            ofExit();
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Info"))
    {
        if(ImGui::BeginMenu("Drawer list"))
        {
            for( auto& d: drawers_)
            {
                ImGui::MenuItem(d->name().c_str());
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Help"))
    {
        if (ImGui::MenuItem("ImGui demo", "")) {
            show_imgui_demo_ = !show_imgui_demo_;
        }
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    if( show_imgui_demo_ ) ImGui::ShowDemoWindow( &show_imgui_demo_ );
}

void ofApp::setupApp()
{
    drawers_.push_back( make_shared<CodArTelier::Drawer::Noise>() );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'f') ofToggleFullscreen();
    if( key == 'q') ofExit();
    if( key == 'h') show_ui_ = !show_ui_;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
