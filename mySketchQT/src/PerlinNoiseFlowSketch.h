#pragma once

#include "SubSketchBase.h"
#include "ofxValueGrid.h"
#include "PerlinFlowCellData.h"
#include "ofxColorGradient.h"

class PerlinNoiseFlowSketch : public SubSketchBase
{
public:
    ///
    /// \brief setup
    ///
	void setup() {
        setupResize();
	}
	
    ///
    /// \brief update
    ///
	void update() {
        //animation += ofGetLastFrameTime() * animationSpeed;
	}
	
    ///
    /// \brief draw
    ///
	void draw() {
        fbo_->draw((ofGetWidth()-size) * .5, (ofGetHeight()-size)*.5f);
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
            animation += animationSpeed;
            drawPerlinFlow();
        }
    }



private:
    shared_ptr<ofxValueGrid<ofxValueGridCell>> valueGrid_;

    unique_ptr<ofFbo> fbo_;

    float size = 0.0f;
    float animation = 0.0f;
    float animationSpeed= 0.01f;
    ofColor background_ = ofColor(60);

    ///
    /// \brief setupResize
    ///
    void setupResize()
    {
        valueGrid_.reset();
        size = ofGetHeight() * 0.8f;

        valueGrid_ = make_shared<ofxValueGrid<ofxValueGridCell>>(55,55,size,size, glm::vec2(.5f,.5f));

        fbo_.reset();
        fbo_ = make_unique<ofFbo>();
        fbo_->allocate(size, size, GL_RGBA);

        drawPerlinFlow();
    }

    ///
    /// \brief drawPerlinFlow
    ///
    void drawPerlinFlow()
    {
        fbo_->begin();
            ofClear(background_);
            ofSetRectMode(OF_RECTMODE_CENTER);

            ofSetLineWidth(2);

            for (const auto& c : valueGrid_->cells())
            {
                auto noiseCol00 = ofNoise(c->pointX() * 0.002, c->pointY() * 0.002, animation * 0.2) / 1.0;
                ofPushMatrix();

                    ofTranslate(c->pointX(), c->pointY());
                    ofRotateDeg(noiseCol00*360);
                    ofScale(2.0 + noiseCol00*8.0);

                    ofFill();
                    ofSetColor(noiseCol00 * 255, 255);
                    ofDrawRectangle(0, 0, c->width(), c->height() * 0.6);

                    ofNoFill();
                    ofSetColor(255-(noiseCol00 * 255), 255);
                    ofDrawRectangle(0, 0, c->width(), c->height() * 0.6);

                    ofPopMatrix();
            }
        fbo_->end();
    }
};

