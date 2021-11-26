#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    subSketch = make_unique<PerlinNoiseFlowSketch>();
    //subSketch = make_unique<PerlinFlowFeatherColor>();
    //subSketch = make_unique<BronianMotionGrid>();
    //subSketch = make_unique<Trainees>();
    //subSketch = make_unique<DrawingTest>();
    subSketch->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    subSketch->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    subSketch->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if( key == 'f') ofToggleFullscreen();
    if( key == 'q') ofExit();

    subSketch->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    subSketch->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    subSketch->mouseMoved(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    subSketch->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    subSketch->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    subSketch->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    subSketch->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    subSketch->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    subSketch->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    subSketch->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    subSketch->dragEvent(dragInfo);
}
