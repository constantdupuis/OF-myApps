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

    Goute(float x, float y, float size) : ofxBasicParticle{ x, y }
    {
        size_ = size;
    }

    void draw()
    {
        ofSetColor(color_);
        ofDrawCircle(pos_.x, pos_.y, size_);
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

        drawArea_.x = 600;
        drawArea_.y = 400;
        setupResize();

        fbo_.reset();
        fbo_ = make_unique<ofFbo>();
        fbo_->allocate(drawArea_.x, drawArea_.y, GL_RGBA);

        //fbo_->begin();
        ofSetBackgroundColor(background_);
        //fbo_->end();

        goute_count_ = 60;

        float space = drawArea_.x / goute_count_;
        for( int i = 0; i < goute_count_; i++)
        {
            goutes_.push_back( make_shared<Goute>(space * i, space * 0.5f, space * 0.5f) );
        }

        drawFrame();

        gui.setup();

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
        ofPushMatrix();
            ofTranslate( topLeft_);
            fbo_->draw(0, 0);
        ofPopMatrix();

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
        topLeft_.x = (ofGetWidth() - drawArea_.x) * .5;
        topLeft_.y = (ofGetHeight() - drawArea_.y) * .5;

    }

    ///
    /// \brief drawPerlinFlow
    ///
    void drawFrame()
    {
        fbo_->begin();
        for( const auto& g : goutes_ )
        {
            g->draw();
        }
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

    ofColor background_ = ofColor(255);
    glm::vec2 topLeft_;
    glm::vec2 drawArea_;

    ofxImGui::Gui gui;

    std::vector<shared_ptr<Goute>> goutes_;
    int goute_count_ = 60;
 
};

