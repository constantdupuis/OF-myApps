#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    gui.setup();

    XML.addTag("root");
    XML.pushTag("root");
    XML.addValue("test","valeur");
    XML.popTag();

    XML.saveFile("test.xml");

    canvasViewer_.setCanvas( canvas_ );
    canvasViewer_.setSize( ofGetWidth(), ofGetHeight() );
    canvasViewer_.setMargin( 10, 10 );
    canvasViewer_.fitToView();
    zoom_ = canvasViewer_.getScale();


    canvas_.begin();
        ofSetColor(0,200,100);
        ofDrawRectRounded(0,0, canvas_.widht(), canvas_.height(), 15);
    canvas_.end();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    canvasViewer_.draw();
    drawUI();
}

//--------------------------------------------------------------
void ofApp::drawUI()
{
    gui.begin();
    {

        ImGui::Text("View");
        ImGui::Separator();

        ImGui::SliderInt("x", &marginx_, 0, 1000);
        ImGui::SliderInt("y", &marginy_, 0, 1000);
        canvasViewer_.setMargin(marginx_, marginy_);
        if( ImGui::Button("fit to screen"))
        {
            zoom_ = canvasViewer_.fitToView();
        }

        ImGui::NewLine();

        ImGui::Text("Scale");
        ImGui::SliderFloat("factor", &zoom_, 0.01f, 10.0);
        canvasViewer_.setScale(zoom_);
        if( ImGui::Button("reset scale"))
        {
            zoom_ = canvasViewer_.resetScale();
        }

        ImGui::NewLine();

        ImGui::Text("Autre");
        ImGui::Separator();

        ImGui::Checkbox("ImGui Demo Window", &showImGuiDemoWin_);
        if (showImGuiDemoWin_) ImGui::ShowDemoWindow(&showImGuiDemoWin_);
    }
    gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'f') ofToggleFullscreen();
    if( key == 'q') ofExit();
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
    canvasViewer_.setSize(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
