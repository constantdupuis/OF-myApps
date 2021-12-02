#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cols_ = 10;
    rows_ = 10;
    on_resize();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
   
    ofBackground(50);
    
    ofSetRectMode(OF_RECTMODE_CORNER);
        
    ofPushMatrix();
        ofTranslate( translate_);

        ofFill();
        ofSetColor(ofColor().yellow);
        ofDrawRectangle(0,0, grid_.width(), grid_.heigth());

        for (const auto& c : grid_.cells())
        {
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofNoFill();
            ofSetColor(ofColor().greenYellow);
            ofDrawRectangle(c->left(), c->top(), c->width(), c->height());

            ofSetRectMode(OF_RECTMODE_CENTER);
            ofFill();
            ofSetColor(ofColor().red);
            ofDrawRectangle(c->pointX(), c->pointY(), c->width()*0.5, c->height()*0.5);

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
    cout << "ofApp::windowResized\n";
    on_resize();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::on_resize()
{
    auto ww = ofGetWidth() * view_ratio;
    auto wh = ofGetHeight() * view_ratio;
    grid_.setup(cols_, rows_, ofGetWidth() * view_ratio, ofGetHeight() * view_ratio);


    ww = ofGetWidth();
    wh = ofGetHeight();
    auto tx = (ww - grid_.width()) / 2.0f;
    auto ty = (wh - grid_.heigth()) / 2.0f;

    translate_ = glm::vec2(tx, ty);
}
