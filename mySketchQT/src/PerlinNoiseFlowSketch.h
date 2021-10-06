#pragma once

#include "SubSketchBase.h"
#include "ofxValueGrid.h"
#include "PerlinFlowCellData.h"
#include "ofxColorGradient.h"
#include "ofxGui.h"

class PerlinNoiseFlowSketch : public SubSketchBase
{
public:
    ///
    /// \brief setup
    ///
	void setup() {
        gui_.setup();
        gui_.add(fullScreen_.setup("full screen", false));
        gui_.add(animate_.setup("animate", false));
        gui_.add(animationSpeed_.setup("aimation speed", 0.5, 0.01, 1.0));
        gui_.add( quit_.setup("exit"));
        setupResize();
	}
	
    ///
    /// \brief update
    ///
	void update() {
        if( animate_)
        {
            animation_ += ofGetLastFrameTime() * animationSpeed_;
            drawPerlinFlow();
        }
	}
	
    ///
    /// \brief draw
    ///
	void draw() {
        fbo_->draw(0, 0);
        gui_.draw();
	}

    ///
    /// \brief windowResized
    /// \param w
    /// \param h
    ///
	void windowResized(int w, int h) {
        setupResize();
	}

    ///
    void keyPressed(int key) {
        if( key == 'r')
        {
            animation_ += animationSpeed_;
            drawPerlinFlow();
        }
    }



private:
    shared_ptr<ofxValueGrid<ofxValueGridCell>> valueGrid_;

    unique_ptr<ofFbo> fbo_;

    float size_ = 0.0f;
    float animation_ = 0.0f;
    //float animationSpeed_= 0.5f;
    ofColor background_ = ofColor(60);
    glm::vec2 topLeft_;

    ofxPanel gui_;
    ofxToggle animate_;
    ofxFloatSlider animationSpeed_;
    ofxToggle fullScreen_;
    ofxButton quit_;

    ///
    /// \brief setupResize
    ///
    void setupResize()
    {
        valueGrid_.reset();
        auto ww = ofGetWidth();
        auto wh = ofGetHeight();
        size_ = ofGetHeight() * 0.7f;
        topLeft_ = glm::vec2((ww- size_)*.5, (wh - size_) *.5);

        valueGrid_ = make_shared<ofxValueGrid<ofxValueGridCell>>(55,55,size_,size_, glm::vec2(.5f,.5f));

        fbo_.reset();
        fbo_ = make_unique<ofFbo>();
        fbo_->allocate(ww, wh, GL_RGBA);

        drawPerlinFlow();
    }

    ///
    /// \brief drawPerlinFlow
    ///
    void drawPerlinFlow()
    {
        fbo_->begin();
            ofPushMatrix();

            ofSetCircleResolution(100);
            ofClear(background_);
            ofSetRectMode(OF_RECTMODE_CENTER);

            ofSetLineWidth(2);

            ofTranslate(topLeft_);
            for (const auto& c : valueGrid_->cells())
            {
                auto noiseCol00 = ofNoise(c->pointX() * 0.002, c->pointY() * 0.002, animation_ * 0.2) / 1.0;
                ofPushMatrix();

                    ofTranslate(c->pointX(), c->pointY());
                    ofRotateDeg(noiseCol00*360);
                    ofScale(2.0 + noiseCol00*10.0);

                    ofFill();
                    ofSetColor(noiseCol00 * 255, 255);
                    ofDrawEllipse(0, 0, c->width()*2., c->height() * 0.4);
                    //ofDrawRectangle(0, 0, c->width()*2., c->height() * 0.4);

                    ofNoFill();
                    ofSetColor(255-(noiseCol00 * 255), 255);
                    ofDrawEllipse(0, 0, c->width()*2., c->height() * 0.4);
                    //ofDrawRectangle(0, 0, c->width()*2., c->height() * 0.4);

                    ofPopMatrix();
            }
            ofPopMatrix();
        fbo_->end();
    }
};

