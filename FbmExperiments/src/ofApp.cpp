#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cols_ = 200;
    rows_ = 200;
    animation_speed_ = 5.0f;

    on_resize();
}

//--------------------------------------------------------------
void ofApp::update(){
    animation_ += animation_speed_;
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    ofBackground(60);
            
    ofPushMatrix();
        ofTranslate( translate_);

        ofFill();
        ofSetColor(50);
        ofDrawRectangle(0,0, grid_.width(), grid_.heigth());

        for (const auto& c : grid_.cells())
        {
            auto n = add( c->pointX(), c->pointY() );
            ofSetColor(n*255);
            ofDrawRectangle( c->left(), c->top(), c->width(), c->height());
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
    auto ww = ofGetWidth();
    auto wh = ofGetHeight();

    grid_.setup(cols_, rows_, wh * view_ratio, wh * view_ratio);

    auto tx = (ww - grid_.width()) / 2.0f;
    auto ty = (wh - grid_.heigth()) / 2.0f;

    translate_ = glm::vec2(tx, ty);
}

float ofApp::add( float x, float y)
{
    auto freq = 0.001;
    auto speed = 0.01f;
    auto octave_nbr = 8;
    float n = 0.0;
    glm::vec2 translate(10,100);
    for( auto o = 0; o < octave_nbr; o++)
    {
        auto s = ofNoise((x + translate.x) * freq, (y  +translate.y) * freq, animation_ * speed);
        n += s;
        freq *= 2.0f;
        translate.x += 10;
    }
    n /= octave_nbr;
    //n = n * .5 + .5;
    return n;
}
