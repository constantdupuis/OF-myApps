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
        if (ImGui::BeginMenu("New ...", "")) {
            for (auto& d : drawers_)
            {
                if (ImGui::MenuItem(d->Name().c_str()))
                {
                    // TODO : ask if any already openned CodArt want to saved parameters
                    newCodArt( d->Build() );
                }
            }
            ImGui::EndMenu();
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

    /*if (ImGui::BeginMenu("Info"))
    {
        if(ImGui::BeginMenu("Drawer list"))
        {
            for( auto& d: drawers_)
            {
                ImGui::MenuItem(d->Name().c_str());
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }*/

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
    // push drawers in list for later selection
    drawers_.push_back( make_shared<CodArTelier::Drawer::NoiseInfoFactory>() );
}

void ofApp::newCodArt( shared_ptr<DrawerBase> drawBase )
{
    if (activeCodArt_)
    {
        activeCodArt_->Stop();
        activeCodArt_->Release();
        activeCodArt_.reset();
    }

    activeCodArt_ = make_shared<CodArt>();
    activeCodArt_->SetDrawer(drawBase);
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
