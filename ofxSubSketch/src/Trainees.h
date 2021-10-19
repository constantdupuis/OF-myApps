#pragma once

#include "ofMain.h"
#include "SubSketchBase.h"
#include "ofxBasicParticle.h"
#include "ofxImGui.h"
#include "glm/gtc/noise.hpp"

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

    float& size() { return size_; }

    void draw()
    {
        ofSetColor(color_);
        ofDrawCircle(pos_.x, pos_.y, size_);
    }

    void glisse()
    {

    }

private:
    ofColor color_ = ofColor(0,50,100, 20);
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

        drawArea_.x = 1000;
        drawArea_.y = 800;
        setupResize();

        fbo_.reset();
        fbo_ = make_unique<ofFbo>();
        fbo_->allocate(drawArea_.x, drawArea_.y, GL_RGBA);

        //fbo_->begin();
        ofSetBackgroundColor(background_);
        //fbo_->end();

        goute_count_ = 60;

        float space = drawArea_.x / (goute_count_+1);
        
        for( int i = 0; i < goute_count_; i++)
        {
            auto g = make_shared<Goute>(space/2 +(space * i), space * 0.5f, space * 0.5f);
            g->velocity().y = 0.1f;
            goutes_.push_back( g );
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

        }
    }

    ///
    /// \brief draw
    ///
    void draw() {

        if( animate_)
        {
            drawFrame();
        }

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
    /// \brief updateFrame
    ///
    void updateFrame()
    {

    }

    ///
    /// \brief drawPerlinFlow
    ///
    void drawFrame()
    {
        fbo_->begin();

        for( const auto& g : goutes_ )
        {
            auto noise = glm::simplex( glm::vec2( g->x() * perlinResolution, animation_));
            auto noise01 = (noise+1.0) / 2.0;

            ofSetColor(noise01 * 255);
            
            auto size = g->size() * 2.0;
            ofDrawRectangle( g->x() - size/2 , 0, size, 50  );

            ofPushMatrix();
                ofTranslate(0, 55);

                g->velocity().y += noise*0.25f;

                if( g->velocity().y < 0.01f ) g->velocity().y = 0.01f;
                if( g->velocity().y > 0.5f ) g->velocity().y = 0.5f;

                g->update(ofGetLastFrameTime());
                g->draw();

            ofPopMatrix();
        }
        fbo_->end();
    }

    void drawUI()
    {
        gui.begin();
        {
            ImGui::Text("Trainées");
            ImGui::Checkbox("animate", &animate_);
            ImGui::SliderFloat("animation speed", &animationSpeed_, 0.0f, 1.5f);
            ImGui::SliderFloat("perlin resolution", &perlinResolution, 0.0001f, 0.01f);
            ImGui::Checkbox("ImGui Demo Window", &showImGuiDemoWin_);
            if (showImGuiDemoWin_) ImGui::ShowDemoWindow(&showImGuiDemoWin_);
        }
        gui.end();
    }

    unique_ptr<ofFbo> fbo_;

    float size_ = 0.0f;
    float animation_ = 0.0f;
    bool animate_ = true;
    float animationSpeed_ = 0.044f;
    float perlinResolution = 0.003f;

    bool showImGuiDemoWin_ = false;

    ofColor background_ = ofColor(255);
    glm::vec2 topLeft_;
    glm::vec2 drawArea_;

    ofxImGui::Gui gui;

    std::vector<shared_ptr<Goute>> goutes_;
    int goute_count_ = 60;
 
};

