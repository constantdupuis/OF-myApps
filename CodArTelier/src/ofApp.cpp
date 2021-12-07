#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("CodarTelier");
    ofSetEscapeQuitsApp(false);
    ofSetVerticalSync(false);

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

    ofBackground( ofColor(128));

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
    if (ImGui::BeginMenu("View"))
    {
        if (ImGui::MenuItem("Canvas params", "")) {
            ui_show_canvas_params = !ui_show_canvas_params;
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
                activeCodArt_->PushConfigToXmlSettings(settings);
                settings.saveFile(ret.filePath);
            }
        }
    }
    if (ui_show_canvas_params)
    {

    }
}

void ofApp::setupApp()
{
    // Get list of drawer, names, description and ids
    codart_manager_.GetDrawersInfos(drawer_names, drawer_descriptions, drawer_ids);
}

void ofApp::setupImGui()
{
    ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontFromFileTTF("./data/fonts/Roboto-Regular.ttf", 18);
    //io.Fonts->AddFontFromFileTTF("./data/fonts/ShareTechMono-Regular.ttf", 18);
    io.Fonts->AddFontFromFileTTF("./data/fonts/DMMono-Regular.ttf", 18);
    //io.Fonts->AddFontFromFileTTF("./data/fonts/DMMono-Light.ttf", 18);

    gui.setup();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 2.0f;
    style.ScrollbarRounding = 2.0f;
    style.ChildRounding = 4.0f;
    style.TabRounding = 2.0f;

    auto theme = ofxImGui::Themes::DeepDark();
    theme.setup();
}

void ofApp::loadCodArt( ofxXmlSettings settings ){
    if( activeCodArt_)
    {
        activeCodArt_.reset();
    }

    activeCodArt_ = codart_manager_.CreateCodArtFromXmlSettings(settings);

    if (activeCodArt_)
    {
        ofLogNotice("ofApp") << "CodArt created from xml settings";
    }
    else
    {
        ofLogError("ofApp") << "Failed to create CodArt from xml settings";
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
        static int view_percent_height = 85;
        static bool square_canvas = true;
        static bool resize_canvas_when_view_change = true;
        static char name[128] = "";
        static char description[512] = "";

        ImGui::InputTextWithHint(" name", "give it a name", name, IM_ARRAYSIZE(name));
        ImGui::InputTextWithHint(" description", "what's is it", description, IM_ARRAYSIZE(description));

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();

        if( ofxImGui::VectorListBox(" drawer", &selected_drawer, drawer_names))
        {
            ofLog() << "Selected drawer id [" << selected_drawer << "]";
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();

        if ( ImGui::Combo(" canvas size mode", &selected_canvas_size_mode, "Raw\0Paper Format\0View Percentage\0"))
        {
            ofLog() << "Selected Canvas Size Mode [" << selected_canvas_size_mode << "]";
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

//        ImGui::Spacing();
//        ImGui::Text("canvas size");
        switch (selected_canvas_size_mode)
        {
        case 0:
            ImGui::InputInt(" width", &canvas_width);
            ImGui::InputInt(" height", &canvas_heigth);
            break;
        case 1:
            ofxImGui::VectorCombo(" paper format", &selected_paper_size, paper_formats_.APaperFormatNames());
            ImGui::InputInt(" dpi", &canvas_resolution);
            ImGui::RadioButton(" portrait", &orientation, 0); ImGui::SameLine();
            ImGui::RadioButton(" landscape", &orientation, 1);
            break;
        case 2:
            ImGui::Checkbox(" square canvas", &square_canvas);
            if (square_canvas)
            {
                ImGui::InputInt(" height %", &view_percent_height);
            }
            else
            {
                ImGui::InputInt(" width %", &view_percent_width);
                ImGui::InputInt(" height %", &view_percent_height);
            }
            ImGui::Checkbox(" resize canvas when view changes", &resize_canvas_when_view_change);
            break;
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("create"))
        {
            ui_show_new_dialog_ = false;
            
            ofLog() << "Create CodArt with drawer [" << drawer_names[selected_drawer] << "]";

            ImGui::CloseCurrentPopup();

            if( activeCodArt_)
            {
                activeCodArt_.reset();
            }

            CanvasSettings cnvSettings;
            glm::vec2 size;
            switch (selected_canvas_size_mode)
            {
            case 0: // RAW, width and heigth
                cnvSettings.size_mode = CANVAS_SIZE_MODE_RAW;
                cnvSettings.raw.width = canvas_width;
                cnvSettings.raw.height = canvas_heigth;
                break;
            case 1: // paper size based width and heigth
                cnvSettings.size_mode = CANVAS_SIZE_MODE_RAW;
                size = paper_formats_.PaperToPixels(
                            (ofxPaperFormat::APaperFormat)selected_paper_size,
                            canvas_resolution,
                            (ofxPaperFormat::Orientation)orientation);
                cnvSettings.raw.width = size.x;
                cnvSettings.raw.height = size.y;
                break;
            case 2: // percent of view based width and heigth
                cnvSettings.size_mode = CANVAS_SIZE_MODE_VIEW_PERCENT;
                cnvSettings.view_percentage.resize_when_view_change = resize_canvas_when_view_change;
                cnvSettings.view_percentage.square_canvas = square_canvas;
                if(square_canvas)
                {
                    cnvSettings.view_percentage.width = view_percent_height;
                    cnvSettings.view_percentage.height = view_percent_height;
                }
                else
                {
                    cnvSettings.view_percentage.width = view_percent_width;
                    cnvSettings.view_percentage.height = view_percent_height;
                }
                break;
            }

            activeCodArt_ = codart_manager_.CreateCodArt(drawer_ids[selected_drawer], cnvSettings);
            activeCodArt_->setName( name );
            activeCodArt_->setDescription(description);
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

void ofApp::UIShowCanvasParams()
{

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
    ofParameterGroup pGroup("Parameters");
//    ofParameter<float> pF01("float01", 0.5, 0.0, 1.0);
//    ofParameter<void> pBTN("Bouton?");
//    pGroup.add( pF01);
//    pGroup.add( pBTN);
//    ofParameterGroup pGroup2("pGroup2");
//    ofParameter<float> pF02("float02", 0.5, 0.0, 1.0);
//    pGroup2.add( pF02);
//    pGroup.add(pGroup2);

    if( activeCodArt_ )
    {
        ofxImGui::Settings settings;
        settings.windowPos.y += 20;

        pGroup.add( activeCodArt_->getParameters());

        ofxImGui::AddGroup(pGroup, settings);

        activeCodArt_->DrawUI();

        //if( !ofxImGui::BeginWindow( "Parameters", settings, true ))
        //{
        //    EndWindow(settings);
        //    return;
        //}
        //ofxImGui::AddGroup(pGroup, settings);

        //// CodArt parameters

        //if(ofxImGui::BeginTree("CodArt [name]", settings))
        //{
        //    activeCodArt_->DrawUI();
        //    ofxImGui::EndTree(settings);
        //}

        //EndWindow(settings);
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

    /*if( key == 'f') ofToggleFullscreen();
    if( key == 'h') show_ui_ = !show_ui_;*/

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
