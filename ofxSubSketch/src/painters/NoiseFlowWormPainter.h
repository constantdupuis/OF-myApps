#ifndef NOISEFLOWWORMPAINTER_H
#define NOISEFLOWWORMPAINTER_H

#include "../SubSketchBase.h"
#include "ofxImGui.h"
#include "ofxValueGrid.h"
#include "ofxBasicParticle.h"
#include "glm/gtx/rotate_vector.hpp"


class Easel {
public:
    Easel(){}
    Easel( int view_width, int view_height, int canvas_width, int canvas_height) {
        view_width_ = view_width;
        view_height_ = view_height;
        canvas_width_ = canvas_width;
        canvas_height_ = canvas_height;
        calculate();
    }

    int getViewWidth() { return view_width_;}
    int getViewHeight() { return view_height_;}
    int getCanvasWidth() { return canvas_width_;}
    int getCanvasHeight() { return canvas_height_;}

    void setViewSize(int view_width, int view_height) {
        view_width_ = view_width;
        view_height_ = view_height;
        calculate();
    }

    void setCanvasSize(int canvas_width, int canvas_height) {
        canvas_width_ = canvas_width;
        canvas_height_ = canvas_height;
        calculate();
    }

    glm::vec2 getCanvasPos() { return canvas_pos_;}
private:
    glm::vec2 canvas_pos_;
    int view_width_ = 1000;
    int view_height_ = 1000;
    int canvas_width_ = 400;
    int canvas_height_ = 400;

    void calculate()
    {
        canvas_pos_.x = (view_width_- canvas_width_) / 2;
        canvas_pos_.y = (view_height_- canvas_height_) / 2;
    }
};

class NoiseFlowWormPainter : public SubSketchBase
{
public:
    void setup()
    {
        ofEnableAntiAliasing();
        ofSetVerticalSync(true);
        ofSetBackgroundAuto(false);

        localSetup();
    }

    void update()
    {

    }

    void draw()
    {
        ofPushMatrix();
        ofTranslate(easel_.getCanvasPos());



        ofPopMatrix();
    }

    void windowResized(int w, int h) {
        localSetup();
    }

private:
    Easel easel_;
    ofxImGui::Gui gui;

    glm::vec2 canvas_size_;
    glm::vec2 canvas_top_left_;

    void localSetup()
    {
        easel_.setViewSize(ofGetWidth(), ofGetHeight());
        easel_.setCanvasSize(ofGetHeight() * 0.75, ofGetHeight() * 0.75);
    }
};

#endif // NOISEFLOWWORMPAINTER_H
