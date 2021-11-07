#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("CodarTelier");
    ofSetEscapeQuitsApp(false );
    setupApp();
    setupImGui();
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
        UIShowNewDialogs();
        UIShowMessageBoxes();
        UICodArt();
        gui.end();
    }
}

void ofApp::UIDrawMenu()
{
    //bool show_new_codart = false;
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        if( ImGui::MenuItem("New ...", ""))
        {
            ui_show_new_dialog_ = true;
        }
        if (ImGui::MenuItem("Open ...", "")) {
            ui_show_open_dialog_ = true;
        }
        if (ImGui::BeginMenu("Open recent ...", "")) {
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Save", "")) {
            ui_show_save_dialog_ = true;
        }
        if (ImGui::MenuItem("Save As ...", "")) {

        }
        if (ImGui::MenuItem("Save As Image", "")) {

        }
        if (ImGui::MenuItem("Exit", "")) {
            
            // TODO : check if any openned CodArt doesn't need to be saved
            // TODO : stop ArtCode Drawer

            ofExit();
        }

        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
        if (ImGui::MenuItem("ImGui demo", "")) {
            ui_show_imgui_demo_ = !ui_show_imgui_demo_;
        }
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    if( ui_show_new_dialog_ ) ImGui::OpenPopup("New CodArt");
    if( ui_show_open_dialog_) UIShowOpenDialogs();
    if( ui_show_imgui_demo_ ) ImGui::ShowDemoWindow( &ui_show_imgui_demo_ );
    if (ui_show_save_dialog_)
    {
        // TODO : First check is any CodArt exists
        ui_show_save_dialog_ = false;

        if (!activeCodArt_)
        {
            ImGui::OpenPopup("No CodArt");
            //ofSystemAlertDialog("No CodArt to save !");
        }
        else {
            auto ret = ofSystemSaveDialog("filename.cod", "Save your CodArt");
            if (ret.bSuccess)
            {
                ofxXmlSettings settings;
                activeCodArt_->PushSettings(settings);
                settings.saveFile(ret.filePath);
            }
        }

        
    }
}

void ofApp::setupApp()
{
    // push drawers in list for later selection
    shared_ptr<DrawerInfoAndFactoryBase> d = make_shared<CodArTelier::Drawer::ArdoiseFbmInfoNFactory>();
    drawers_.push_back( d );
    drawers_names_.push_back( d->Name());
    drawers_by_id_[d->Id()] = d;
}

void ofApp::setupImGui()
{
    ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontFromFileTTF("./data/fonts/Roboto-Regular.ttf", 18);
    io.Fonts->AddFontFromFileTTF("./data/fonts/ShareTechMono-Regular.ttf", 18);

    gui.setup();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 2.0f;
    style.ScrollbarRounding = 2.0f;
    style.ChildRounding = 4.0f;
    style.TabRounding = 2.0f;
}

void ofApp::loadCodArt( ofxXmlSettings settings ){
    if( activeCodArt_)
    {
        activeCodArt_.reset();
    }


}

void ofApp::UIShowNewDialogs()
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
        static char filename[128] = "";

        ImGui::InputTextWithHint("name", "enter a name", filename, IM_ARRAYSIZE(filename));

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
            ui_show_new_dialog_ = false;
            ImGui::CloseCurrentPopup();

            if( activeCodArt_)
            {
                activeCodArt_.reset();
            }

            switch( selected_canvas_size_mode)
            {
            case 0: // RAW width and heigth
                activeCodArt_ = make_shared<CodArt>();
                activeCodArt_->SetupRaw(drawer_info->Build(), canvas_width, canvas_heigth);
                break;
            case 1: // paper size based width and heigth
                // TODO
                break;
            case 2: // percent of view based width and heigth
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
        ImGui::SetItemDefaultFocus();

        ImGui::SameLine();
        if (ImGui::Button("cancel"))
        {
            ui_show_new_dialog_ = false;
            ImGui::CloseCurrentPopup();
        }
            

        ImGui::EndPopup();
    }
}

void ofApp::UIShowOpenDialogs()
{
    ui_show_open_dialog_ = false;
    auto ret = ofSystemLoadDialog("Open an CodArt", false, "./codarts");
    if (ret.bSuccess)
    {
        ofxXmlSettings settings;
        settings.loadFile(ret.filePath);
        loadCodArt( settings );
    }
}

void ofApp::UIShowMessageBoxes()
{
    if (ImGui::BeginPopupModal("No CodArt", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("No CodArt openned to save !\n\n");
        ImGui::Separator();

        ImGui::Spacing();
        if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::SetItemDefaultFocus();

        ImGui::EndPopup();
    }
}

void ofApp::UICodArt()
{
    if( activeCodArt_ )
    {
        //auto drawers_by_id_[activeCodArt_->id]
        if (!ImGui::Begin("CodArt [name]"))
        {
            ImGui::End();
            return;
        }
        if( ImGui::CollapsingHeader("Drawer", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf))
        {
            activeCodArt_->DrawUI();
        }
        ImGui::End();
    }

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //ofLog() << "KeyPressed entered key  [" << key << "] char ["<< (char)key <<"]";

    if (ctrl_key_was_pressed_ && !(key == OF_KEY_CONTROL || key == OF_KEY_LEFT_CONTROL || key == OF_KEY_RIGHT_CONTROL))
    {
        //ofLog() << "CTRL+Key post received [" << key << "]";
        if( key == 14) ui_show_new_dialog_ = true;
        ctrl_key_was_pressed_ = false;
        return;
    }

    if (key == OF_KEY_CONTROL || key == OF_KEY_LEFT_CONTROL || key == OF_KEY_RIGHT_CONTROL)
    {
        //ofLog() << "CTRL pressed key";
        ctrl_key_was_pressed_ = true;
        return;
    }

    if( key == 'f') ofToggleFullscreen();
    if( key == 'h') show_ui_ = !show_ui_;

    if( activeCodArt_ ) activeCodArt_->keyPressed(key);
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
