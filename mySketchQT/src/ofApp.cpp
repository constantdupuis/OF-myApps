#include "ofApp.h"


void ofApp::setupGrid()
{
    valueGrid_.reset();
    valueGrid_ = make_shared<ofxValueGrid<CellWithSizeAndColor>>(6, 6, ofGetHeight() *.8,ofGetHeight()*.8, glm::vec2(.5f, .5f));
}

//--------------------------------------------------------------
void ofApp::setup(){
    setupGrid();
    ofEnableAntiAliasing();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(255);

    ofSetRectMode( OF_RECTMODE_CENTER );
    ofNoFill();
    ofSetLineWidth(4);

    ofPushMatrix();

    ofTranslate( (ofGetWidth()  - valueGrid_->width()) /2, (ofGetHeight() - valueGrid_->heigth()) /2 );

    for( const shared_ptr<CellWithSizeAndColor> &c : valueGrid_->cells() )
    {
        ofSetColor(0);
        ofSetLineWidth(ofRandom(2, 8));
        ofDrawRectangle( c->pointX(), c->pointY(), c->width() * 0.8, c->height() * 0.8 );

        if( ofRandom(1.0) > 0.5){
            ofSetLineWidth(ofRandom(2, 8));
            ofDrawRectangle( c->pointX(), c->pointY(), c->width() * 0.6, c->height() * 0.6 );
        }
//        ofSetColor(c->color_);
//        ofDrawCircle( c->pointX(), c->pointY(), c->size_ );
    }

    ofPopMatrix();
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
    setupGrid();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
