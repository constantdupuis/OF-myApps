#pragma once

#include "SubSketchBase.h"
#include "ofxValueGrid.h"
#include "ofxImGui.h"

class PerlinFlowFeatherColor : public SubSketchBase
{
public:
    ///
    /// \brief setup
    ///
	void setup() {

        ofEnableAntiAliasing();
        ofSetVerticalSync(true);

        gradiantImage_.load("gradiant01.png");
        gradiantImageSize_.x = gradiantImage_.getWidth();
        gradiantImageSize_.y = gradiantImage_.getHeight();

        gui.setup();
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
        drawUI();
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
    bool animate_ = false;
    float animationSpeed_ = 0.5f;
    bool showImGuiDemoWin_ = false;

    ofImage gradiantImage_;
    glm::vec2 gradiantImageSize_;

    ofxImGui::Gui gui;

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
                    auto cx = (gradiantImageSize_.x * noiseCol00);
                    ofColor col = gradiantImage_.getColor( cx , gradiantImageSize_.y*.5);
                    ofSetColor(col);
                    ofDrawEllipse(0, 0, c->width()*2., c->height() * 0.4);
                    //ofDrawRectangle(0, 0, c->width()*2., c->height() * 0.4);

                    //ofNoFill();
                    //ofSetColor(255-(noiseCol00 * 255), 255);
                    //ofSetColor(255);
                    //ofDrawEllipse(0, 0, c->width()*2., c->height() * 0.4);
                    //ofDrawRectangle(0, 0, c->width()*2., c->height() * 0.4);

                    ofPopMatrix();
            }
            ofPopMatrix();
        fbo_->end();
    }

    void drawUI()
    {
        gui.begin();
        {
            ImGui::Text("Perlin Noise Flow");
            ImGui::Checkbox("animate", &animate_);
            ImGui::SliderFloat("animation speed", &animationSpeed_, 0.0f, 1.0f);
            ImGui::Checkbox("ImGui Demo Window", &showImGuiDemoWin_);
            if( showImGuiDemoWin_) ImGui::ShowDemoWindow(&showImGuiDemoWin_);
        }
        gui.end();
    }
};

