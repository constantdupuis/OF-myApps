#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    valueGrid_ = make_shared<ofxValueGrid<CellWithSizeAndColor>>(20, 20, ofGetWidth(),ofGetHeight(), glm::vec2(.5f, .5f));

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(255);

    for( const shared_ptr<CellWithSizeAndColor> &c : valueGrid_->cells() )
    {
        ofSetColor(c->color_);
        ofDrawCircle( c->mapx_, c->mapy_, c->size_ );
    }
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
    valueGrid_.reset();
    valueGrid_ = make_shared<ofxValueGrid<CellWithSizeAndColor>>(20, 20, ofGetWidth(),ofGetHeight(), glm::vec2(.5f, .5f));
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
