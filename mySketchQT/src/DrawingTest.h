#pragma once

#include "SubSketchBase.h"

class DrawingTest : public SubSketchBase
{
public:
    void setup() {

        ofEnableAntiAliasing();
        ofSetVerticalSync(true);
    }

    void update() {
       
    }

    void draw() {
     
    }

private:

    ofxImGui::Gui gui;


};
