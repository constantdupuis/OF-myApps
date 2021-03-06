#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();

    guiSettings.windowSize.x = 1000;
    guiSettings.windowSize.y = 500;

	pGroup_.add(pFbm_types);
	pGroup_.add(pOctaves_nbr);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

   /* ofParameterGroup pGroup("pGroup");
    ofParameter<float> pF01("float01", 0.5, 0.0, 1.0);
    ofParameter<void> pBTN("Bouton?");
    pGroup.add(pF01);
    pGroup.add(pBTN);
    ofParameterGroup pGroup2("pGroup2");
    ofParameter<float> pF02("float02", 0.5, 0.0, 1.0);
    pGroup2.add(pF02);
    pGroup.add(pGroup2);*/

	gui.begin();
		//ofxImGui::AddGroup( pGroup_, guiSettings );
        ofxImGui::BeginWindow("Parameters", guiSettings, true);
        ofxImGui::AddRadio(pFbm_types, fbm_types, 1);
        ofxImGui::EndWindow(guiSettings);
	gui.end();
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
