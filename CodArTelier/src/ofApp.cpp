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

        ShowNewDialog();

        gui.end();
    }
}

void ofApp::UIDrawMenu()
{
    bool show_new_codart = false;
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        if( ImGui::MenuItem("New ...", "CTRL+N"))
        {
            show_new_codart = true;
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
            
            // TODO : check if any openned CodArt doesn't need to be saved
            // TODO : stop ArtCode Drawer

            ofExit();
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

    if( show_new_codart ) ImGui::OpenPopup("New CodArt");
    if( show_imgui_demo_ ) ImGui::ShowDemoWindow( &show_imgui_demo_ );
}

void ofApp::setupApp()
{
    // push drawers in list for later selection
    shared_ptr<DrawerInfoAndFactoryBase> d = make_shared<CodArTelier::Drawer::NoiseInfoFactory>();
    drawers_.push_back( d );
    drawers_names_.push_back( d->Name());
}

void ofApp::ShowNewDialog()
{
    if (ImGui::BeginPopupModal("New CodArt", NULL))
    {
        int selected_drawer = 0;
        if( ofxImGui::VectorCombo(" Drawer", &selected_drawer, drawers_names_))
        {
            ofLog() << "Selected Drawer id [" << selected_drawer << "]";
        }
        if (ImGui::Button("Create"))
        {
            auto drawer_info = drawers_[selected_drawer];
            ofLog() << "Create CodArt with drawer [" << drawer_info->Name() << "]";
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Close"))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }
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
