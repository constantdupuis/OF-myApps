#pragma once

#include "SubSketchBase.h"
#include "ofxImGui.h"

class DrawingTest : public SubSketchBase
{
public:
    void setup() {
        gui.setup();
        ofEnableAntiAliasing();
        ofSetVerticalSync(true);
        ofSetBackgroundAuto(false);
        ofBackground( background_ );
        ofFill();

    }

    void update() {

    }

    void draw() {


        //drawUI();
    }

    void mousePressed(int x, int y, int button) {
        ofSetColor(draw_color_);
        ofDrawRectangle(x, y, 10,10);
    }

private:

    ofxImGui::Gui gui;
    ofColor background_ = ofColor(255);
    ofColor draw_color_ = ofColor(0);

    ImVec4 imColor_;

    void drawUI()
    {
        gui.begin();
            imColor_.x = (float)background_.r/255.0;
            imColor_.y = (float)background_.g/255.0;
            imColor_.z = (float)background_.b/255.0;
            imColor_.w = (float)background_.a/255.0;
            ImGui::ColorEdit4("background", (float*)&imColor_);
            background_.r = imColor_.x*255;
            background_.g = imColor_.y*255;
            background_.b = imColor_.z*255;
            background_.a = imColor_.w*255;
        gui.end();
    }
};
