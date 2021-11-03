#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("CodarTelier");
    ofSetEscapeQuitsApp(false );
    setupApp();
    gui.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    if( activeCodArt_)
        activeCodArt_->Update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    //ofBackground( ofColor().whiteSmoke);

    if( activeCodArt_)
        activeCodArt_->Draw();

    if( show_ui_)
    {
        gui.begin();

        UIDrawMenu();

        ShowNewDialog();

        if( activeCodArt_)
            activeCodArt_->DrawUI();

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

        if (ImGui::MenuItem("Save As Image", "")) {

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
    shared_ptr<DrawerInfoAndFactoryBase> d = make_shared<CodArTelier::Drawer::NoiseInfoNFactory>();
    drawers_.push_back( d );
    drawers_names_.push_back( d->Name());
}

void ofApp::ShowNewDialog()
{
    if (ImGui::BeginPopupModal("New CodArt", NULL))
    {
        static int selected_drawer = 0;
        static int selected_canvas_size_mode = 2;
        static int selected_paper_size = 0;
        static int orientation = 0;

        static int canvas_width = 400;
        static int canvas_heigth = 400;
        static int canvas_resolution = 300;

        static int view_percent_width = 85;
        static int view_percent_heigth = 85;
        static bool square_canvas = true;
        static bool resize_canvas_when_view_change = true;

        if( ofxImGui::VectorCombo(" drawer", &selected_drawer, drawers_names_))
        {
            ofLog() << "Selected drawer id [" << selected_drawer << "]";
        }
        ImGui::Spacing();
        if ( ImGui::Combo(" canvas size mode", &selected_canvas_size_mode, "Raw\0Paper Format\0View Percentage\0"))
        {
            ofLog() << "Selected Canvas Size Mode [" << selected_canvas_size_mode << "]";
        }
        ImGui::Spacing();
        ImGui::Text("canvas size");
        switch (selected_canvas_size_mode)
        {
        case 0:
            ImGui::InputInt(" width", &canvas_width);
            ImGui::InputInt(" height", &canvas_heigth);
            break;
        case 1:
            ofxImGui::VectorCombo(" paper format", &selected_paper_size, paper_formats_);
            ImGui::InputInt(" dpi", &canvas_resolution);
            ImGui::RadioButton(" portrait", &orientation, 0); ImGui::SameLine();
            ImGui::RadioButton(" landscape", &orientation, 1);
            break;
        case 2:
            ImGui::Checkbox(" square canvas", &square_canvas);
            if (square_canvas)
            {
                ImGui::InputInt(" height %", &view_percent_heigth);
            }
            else
            {
                ImGui::InputInt(" width %", &view_percent_width);
                ImGui::InputInt(" height %", &view_percent_heigth);
            }
            ImGui::Checkbox(" resize canvas when view changes", &resize_canvas_when_view_change);
            break;
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("create"))
        {
            auto drawer_info = drawers_[selected_drawer];
            ofLog() << "Create CodArt with drawer [" << drawer_info->Name() << "]";
            ImGui::CloseCurrentPopup();

            if( activeCodArt_)
            {
                activeCodArt_.reset();
            }

            switch( selected_canvas_size_mode)
            {
            case 0:
                activeCodArt_ = make_shared<CodArt>();
                activeCodArt_->SetupRaw(drawer_info->Build(), canvas_width, canvas_heigth);
                break;
            case 1:
                // todo
                break;
            case 2:
                if(square_canvas)
                {
                    activeCodArt_ = make_shared<CodArt>();
                    activeCodArt_->SetupPercentSquare(drawer_info->Build(), view_percent_heigth, resize_canvas_when_view_change);
                }
                else
                {
                    activeCodArt_ = make_shared<CodArt>();
                     activeCodArt_->SetupPercent(drawer_info->Build(), view_percent_width, view_percent_heigth, resize_canvas_when_view_change);
                }
                break;
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("cancel"))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'f') ofToggleFullscreen();
    if( key == 'q') ofExit();
    if( key == 'h') show_ui_ = !show_ui_;
    if( activeCodArt_) activeCodArt_->keyPressed(key);
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
    if( activeCodArt_)
    {
        activeCodArt_->windowResized(w, h);
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
