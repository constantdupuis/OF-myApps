#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync( true );
}

//--------------------------------------------------------------
void ofApp::update(){
    rotation += rotationSpeed * ofGetLastFrameTime();

    paths.push_front( ofPath() );
    paths.push_front( ofPath() );
    paths.push_front( ofPath() );
    paths.push_front( ofPath() );
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofColor colorOne(34, 193, 195);
    ofColor colorTwo(253, 187, 45);
    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);

    ofSetColor(255);

    ofPath path;
    path.setCircleResolution(200);
    path.arc(ofGetWidth() * 0.5,ofGetHeight() *0.5,200,200,0+rotation,196+rotation);
    path.setFilled( false);
    path.setStrokeWidth(2);
    path.draw();

    paths.clear();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
