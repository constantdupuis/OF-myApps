#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    gui.setup();

//    XML.addTag("root");
//    XML.pushTag("root");
//    XML.addValue("test","valeur");
//    XML.popTag();

//    XML.saveFile("test.xml");

    //spCanvas_ = make_shared<ofxCanvas>(800, 800);
    spPainter_ = make_shared<BronianMotionPainter>();
    //spViewer_ = make_shared<ofxCanvasViewer>(ofGetWidth(), ofGetHeight(), spCanvas_);

    //spPainter_->setup( spCanvas_->getCanvasInfos());

    //easel_ = make_shared<ofxEasel>( spCanvas_, spPainter_, spViewer_ );

    easel_ = make_shared<ofxEasel>( 800, 800, ofGetWidth(), ofGetHeight() , spPainter_);
    easel_->setup();

    zoom_ = easel_->getViewer()->fitToView();

}

//--------------------------------------------------------------
void ofApp::update(){
    easel_->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    easel_->draw();
    drawUI();
}

//--------------------------------------------------------------
void ofApp::drawUI()
{
    gui.begin();
    {
        if( !ImGui::Begin("Easel", &b_ui))
        {
            ImGui::End();
            return;
        }
        easel_->drawImGui();

        ImGui::Checkbox("ImGui Demo Window", &showImGuiDemoWin_);
        if (showImGuiDemoWin_) ImGui::ShowDemoWindow(&showImGuiDemoWin_);
        ImGui::End();
    }
    gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'f') ofToggleFullscreen();
    if( key == 'q') ofExit();

    easel_->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    easel_->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    // need to scale mouse pos, for all othe rmouse related method also !
    easel_->mouseMoved(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    easel_->mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    easel_->mousePressed(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    easel_->mouseReleased(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    easel_->mouseEntered(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    easel_->mouseExited(x,y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    easel_->windowsResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    easel_->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    easel_->dragEvent(dragInfo);
}
