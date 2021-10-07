#pragma once

#include "ofMain.h"
#include "SubSketchBase.h"
#include "ofxBasicParticle.h"
#include "ofxImGui.h"

class Goute : public ofxBasicParticle
{
public:

    Goute() {}

    Goute(glm::vec2 pos) : ofxBasicParticle { pos }
    {}

    Goute(float x, float y) : ofxBasicParticle{ x, y }
    {}

    void draw()
    {
    }

private:
    ofColor color_ = ofColor(0,100,200, 128);
    float size_ = 5;

};

class Trainees : public SubSketchBase
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

    ///
   /// \brief setupResize
   ///
    void setupResize()
    {

        float ww = ofGetWidth();
        float wh = ofGetHeight();

        drawArea_.x = 600;
        drawArea_.y = 400;
        topLeft_.x = (ww - drawArea_.x) * .5;
        topLeft_.y = (wh - drawArea_.y) * .5;

    }

    ///
    /// \brief drawPerlinFlow
    ///
    void drawFrame()
    {
        fbo_->begin();
        
        ofPushMatrix();

        ofPopMatrix();

        fbo_->end();
    }

    void drawUI()
    {
        gui.begin();
        {
            ImGui::Text("Trainées");
            ImGui::Checkbox("animate", &animate_);
            ImGui::SliderFloat("animation speed", &animationSpeed_, 0.0f, 10.0f);
            ImGui::Checkbox("ImGui Demo Window", &showImGuiDemoWin_);
            if (showImGuiDemoWin_) ImGui::ShowDemoWindow(&showImGuiDemoWin_);
        }
        gui.end();
    }

    unique_ptr<ofFbo> fbo_;

    float size_ = 0.0f;
    float animation_ = 10.0f;
    bool animate_ = false;
    float animationSpeed_ = 5.0f;
    bool showImGuiDemoWin_ = false;

    ofColor background_ = ofColor(60);
    glm::vec2 topLeft_;
    glm::vec2 drawArea_;

    ofxImGui::Gui gui;

    std::vector<Goute> goutes_;
    int goute_count_ = 60;
 
};

