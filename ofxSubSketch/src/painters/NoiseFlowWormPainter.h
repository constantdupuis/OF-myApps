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
        view_size_.x = view_width;
        view_size_.y = view_height;
        canvas_size_.x = canvas_width;
        canvas_size_.y = canvas_height;
        allocateFbo();
        calculate();
    }

    Easel( glm::vec2 view_size, glm::vec2 canvas_size) {
        view_size_ = view_size;
        canvas_size_ = canvas_size;
        allocateFbo();
        calculate();
    }


    int getViewWidth() { return view_size_.x;}
    int getViewHeight() { return view_size_.y;}
    int getCanvasWidth() { return canvas_size_.x;}
    int getCanvasHeight() { return canvas_size_.y;}

    const glm::vec2& getViewSize() { return view_size_;}
    const glm::vec2& getCanvasSize() { return canvas_size_;}
    const glm::vec2& getCanvasPos() { return canvas_pos_;}

    void setViewSize(glm::vec2 view_size) {
        view_size_ = view_size;
        calculate();
    }

    void setViewSize(int view_width, int view_height) {
        view_size_.x = view_width;
        view_size_.y = view_height;
        calculate();
    }

    void setCanvasSize(glm::vec2 canvas_size) {
        canvas_size_ = canvas_size;
        allocateFbo();
        calculate();
    }

    void setCanvasSize(int canvas_width, int canvas_height) {
        canvas_size_.x = canvas_width;
        canvas_size_.y = canvas_height;
        allocateFbo();
        calculate();
    }

    void begin() { fbo_.begin(); }
    void end() { fbo_.end(); }
    void drawCanvas() {
        ofPushMatrix();
            ofTranslate(canvas_pos_);
            fbo_.draw(0,0);
        ofPopMatrix();
    }
    void drawCanvas(int x, int y) {fbo_.draw(x,y);}

private:
    glm::vec2 canvas_pos_;
    glm::vec2 view_size_ {1000,1000};
    glm::vec2 canvas_size_ {400,400};
    ofFbo fbo_;

    void calculate()
    {
        canvas_pos_.x = (view_size_.x - canvas_size_.x) / 2;
        canvas_pos_.y = (view_size_.y - canvas_size_.y) / 2;
    }

    void allocateFbo()
    {
        if( fbo_.isAllocated())
        {
            fbo_.clear();
        }

        fbo_.allocate(canvas_size_.x, canvas_size_.y, GL_RGBA);
    }
};

class NoiseFlowWormPainter : public SubSketchBase
{
public:
    void setup()
    {
        gui_.setup();

        ofEnableAntiAliasing();
        ofSetVerticalSync(true);
        ofSetBackgroundAuto(true);

        int w = ofGetWidth() * 0.85;
        int h = ofGetHeight() * 0.85;

        easel_.setViewSize(ofGetWidth(), ofGetHeight());
        easel_.setCanvasSize(w, h);

        for( int i = 0; i < 50; i++)
        {
            particles_.push_back( make_shared<ofxBasicParticle>(
                w * .5 + ofRandomf() * 400, h * .5 + ofRandomf() * 400,ofRandomf(), ofRandomf() ));
        }

    }

    void update()
    {
        for( auto& p : particles_)
        {
            float rotation = ofNoise( p->pos() * 0.005);
            //p->velocity() = glm::rotate( glm::vec2(0.2,0.1), rotation * 360);
            p->velocity() = glm::rotate( p->velocity(), rotation * 360);
            p->update(ofGetLastFrameTime());
        }
    }

    void draw()
    {
        // draw on the canvas (ofFbo)
        easel_.begin();
            // draw on canvas here
            //ofBackground(255);
            ofSetColor(ofColor().limeGreen, 128);
            ofFill();
            for( auto& p : particles_)
            {
                ofDrawCircle(p->pos(), 1 );
            }
        easel_.end();

        // draw the canvas (ofFbo), centered by default
        easel_.drawCanvas();

        // draw UI
        drawGui();
    }

    void windowResized(int w, int h) {
        easel_.setViewSize(w,h);
        easel_.setCanvasSize(w * 0.85, h * 0.85);
    }

private:
    Easel easel_;
    ofxImGui::Gui gui_;

    std::vector<shared_ptr<ofxBasicParticle>> particles_;

    void localSetup()
    {
        easel_.setViewSize(ofGetWidth(), ofGetHeight());
        easel_.setCanvasSize(ofGetHeight() * 0.85, ofGetHeight() * 0.85);
    }

    void drawGui()
    {
        gui_.begin();
        gui_.end();
    }
};

#endif // NOISEFLOWWORMPAINTER_H
