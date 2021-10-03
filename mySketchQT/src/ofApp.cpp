#include "ofApp.h"


void ofApp::setupGrid()
{
    valueGrid_.reset();
    valueGrid_ = make_shared<ofxValueGrid<CellWithSizeAndColor>>(150, 150, ofGetHeight() *.9,ofGetHeight()*.9, glm::vec2(.5f, .5f));
}

//--------------------------------------------------------------
void ofApp::setup(){
    setupGrid();
    ofEnableAntiAliasing();
}

//--------------------------------------------------------------
void ofApp::update(){
    animation += 1.0;
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(128);

    ofSetRectMode( OF_RECTMODE_CENTER );
    //ofNoFill();
    //ofSetLineWidth(4);

    ofPushMatrix();

    ofTranslate( (ofGetWidth()-valueGrid_->width())/2, (ofGetHeight()-valueGrid_->heigth())/2 );

    for( const shared_ptr<CellWithSizeAndColor> &c : valueGrid_->cells() )
    {

//        auto noiseCol0 = ofNoise(c->pointX()*0.04, c->pointY()*0.04, animation * 0.01);
//        auto noiseCol1 = ofNoise(c->pointX()*0.01, c->pointY()*0.01, animation * 0.01);
//        auto noiseCol2 = ofNoise(c->pointX()*0.003, c->pointY()*0.003, animation * 0.01);
//        ofSetColor( noiseCol0 * noiseCol1 * noiseCol2 * 255);
//        ofDrawRectangle( c->pointX(), c->pointY(), c->width(), c->height());

//        auto noiseCol0 = ofNoise(c->pointX()*0.01, c->pointY()*0.01, animation*0.01);
//        auto noiseCol1 = ofNoise(1.0 + c->pointX()*0.01, c->pointY()*0.01, animation*0.01);
//        auto noiseCol2 = ofNoise(5.0 + c->pointX()*0.01, c->pointY()*0.01, animation*0.01);
//        ofSetColor( noiseCol0 * 255, noiseCol1 * 255, noiseCol2 * 255);
//        ofDrawRectangle( c->pointX(), c->pointY(), c->width(), c->height());


        auto noiseCol00 = ofNoise(c->pointX()*0.005, c->pointY()*0.005, animation*0.005) / 2.0;
        auto noiseCol0 = ofNoise(c->pointX()*0.01, c->pointY()*0.01, animation*0.01) / 4.0;
        auto noiseCol1 = ofNoise(c->pointX()*0.02, c->pointY()*0.02, animation*0.02) / 8.0;
        auto noiseCol2 = ofNoise(c->pointX()*0.04, c->pointY()*0.04, animation*0.04) / 16.0;
        //auto noiseCol3 = ofNoise(c->pointX()*0.08, c->pointY()*0.08, animation*0.01) / 16.0;
        //auto noiseCol4 = ofNoise(c->pointX()*0.16, c->pointY()*0.16, animation*0.01) / 32.0;
        ofSetColor( (noiseCol00 + noiseCol0 + noiseCol1 + noiseCol2) * 255);
        ofDrawRectangle( c->pointX(), c->pointY(), c->width(), c->height());

//        ofSetColor(0);
//        ofSetLineWidth(ofRandom(2, 8));
//        ofDrawRectangle( c->pointX(), c->pointY(), c->width() * 0.8, c->height() * 0.8 );

//        if( ofRandom(1.0) > 0.5){
//            ofSetLineWidth(ofRandom(2, 8));
//            ofDrawRectangle( c->pointX(), c->pointY(), c->width() * 0.6, c->height() * 0.6 );
//        }
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
