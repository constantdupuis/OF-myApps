#pragma once

#include "SubSketchBase.h"
#include "ofxValueGrid.h"
#include "ofxImGui.h"

/*

Inspirations

https://thebookofshaders.com/13/

*/

class BronianMotionGrid : public SubSketchBase
{
public:
    ///
    /// \brief setup
    ///
    void setup() {

        ofEnableAntiAliasing();
        ofSetVerticalSync(true);

        gui.setup();
        setupResize();
    }

    ///
    /// \brief update
    ///
    void update() {
        if (animate_)
        {
            animation_ += ofGetLastFrameTime() * animationSpeed_;
            drawFrame();
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
        if (key == 'r')
        {
            animation_ += animationSpeed_;
            drawFrame();
        }
    }



private:
    shared_ptr<ofxValueGrid<ofxValueGridCell>> valueGrid_;

    unique_ptr<ofFbo> fbo_;

    float size_ = 0.0f;
    float animation_ = 10.0f;
    bool animate_ = false;
    float animationSpeed_ = 5.0f;
    bool showImGuiDemoWin_ = false;

    ofColor background_ = ofColor(60);
    glm::vec2 topLeft_;
    
    ofxImGui::Gui gui;

    ///
    /// \brief setupResize
    ///
    void setupResize()
    {
        valueGrid_.reset();
        float ww = ofGetWidth();
        float wh = ofGetHeight();
        size_ = ofGetHeight() * 0.7f;
        topLeft_ = glm::vec2((ww - size_) * .5, (wh - size_) * .5);

        valueGrid_ = make_shared<ofxValueGrid<ofxValueGridCell>>(250, 250, size_, size_, glm::vec2(.5, .5));

        fbo_.reset();
        fbo_ = make_unique<ofFbo>();
        fbo_->allocate(ww, wh, GL_RGBA);

        drawFrame();
    }

    ///
    /// \brief drawPerlinFlow
    ///
    void drawFrame()
    {
        fbo_->begin();
        ofPushMatrix();

        ofClear(background_);
        ofTranslate(topLeft_);

        for (const auto& c : valueGrid_->cells())
        {
            ofPushMatrix();

            auto noiseCol0 = ofNoise(c->pointX() * 0.01, c->pointY() * 0.01, animation_ * 0.1) / 2.0;
            auto noiseCol1 = ofNoise(c->pointX() * 0.02, c->pointY() * 0.02, animation_ * 0.2) / 4.0;
            auto noiseCol2 = ofNoise(c->pointX() * 0.04, c->pointY() * 0.04, animation_ * 0.4) / 8.0;
            auto noiseCol3 = ofNoise(c->pointX() * 0.08, c->pointY() * 0.08, animation_ * 0.8) / 16.0;

            ofSetColor((noiseCol0 + noiseCol1 + noiseCol2 + noiseCol3) * 255);

            ofDrawRectangle(c->pointX(), c->pointY(), c->width(), c->height());

            ofPopMatrix();
        }
        ofPopMatrix();
        fbo_->end();
    }

    void drawUI()
    {
        gui.begin();
        {
            ImGui::Text("Brownian Motion");
            ImGui::Checkbox("animate", &animate_);
            ImGui::SliderFloat("animation speed", &animationSpeed_, 0.0f, 10.0f);
            ImGui::Checkbox("ImGui Demo Window", &showImGuiDemoWin_);
            if (showImGuiDemoWin_) ImGui::ShowDemoWindow(&showImGuiDemoWin_);
        }
        gui.end();
    }
};

