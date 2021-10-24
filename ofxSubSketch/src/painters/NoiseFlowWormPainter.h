#ifndef NOISEFLOWWORMPAINTER_H
#define NOISEFLOWWORMPAINTER_H

#include "../SubSketchBase.h"
#include "ofxImGui.h"
#include "ofxValueGrid.h"
#include "ofxBasicParticle.h"
#include "glm/gtx/rotate_vector.hpp"
#include "../lib/helpers.h"


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

    const ofRectangle& getCanvasRect() { return canvas_rect_;}

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
        canvas_rect_.setSize(canvas_width, canvas_height);
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

    const ofFbo& fbo() { return fbo_;}

private:
    glm::vec2 canvas_pos_;
    glm::vec2 view_size_ {1000,1000};
    glm::vec2 canvas_size_ {400,400};
    ofRectangle canvas_rect_ = ofRectangle(0.0,0.0, 400,400);
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
    NoiseFlowWormPainter()
    {
        resetRandomSeed();
    }

    void setup()
    {
        ofSetEscapeQuitsApp(false);

        // ofLog will write in a log file, it will be created in data folder
        ofSetLogLevel(OF_LOG_VERBOSE);
        ofLogToFile("app.log");

        ofSetWindowTitle("Perlin Noise Force Field");

        gui_.setup();

        ofEnableAntiAliasing();
        //ofSetVerticalSync(true);
        ofSetBackgroundAuto(true);
        ofBackground(60);

        backgroundf_[0] = (float)background_.r/(float)255;
        backgroundf_[1] = (float)background_.g/(float)255;
        backgroundf_[2] = (float)background_.b/(float)255;

        int w = ofGetWidth() * 0.85;
        int h = ofGetHeight() * 0.85;

        easel_.setViewSize(ofGetWidth(), ofGetHeight());
        easel_.setCanvasSize(w, h);

        for( int i = 0; i < 5000; i++)
        {
            particles_.push_back( make_shared<ofxBasicParticle>(
                w * ofRandomuf(), h * ofRandomuf(), 0.0f, 0.0f ));
        }

        easel_.begin();
        ofSetColor(background_);
        ofFill();
        ofDrawRectangle(0,0, easel_.getCanvasWidth(), easel_.getCanvasHeight());
        easel_.end();

    }

    void update()
    {
        if( !drawing_) return;
        for( auto& p : particles_)
        {
            if( !easel_.getCanvasRect().inside(p->pos()))
            {
                p->pos() = glm::vec2(easel_.getCanvasWidth() * ofRandomuf(), easel_.getCanvasHeight() * ofRandomuf());
                p->velocity() = glm::vec2(0.0,0.0);
            }

            float rotation = ofNoise( (p->pos() + noise_shift_) * 0.001);

            //p->velocity() = glm::rotate( glm::vec2(0.2,0.1), rotation * 360);

            //p->velocity() = glm::rotate( p->velocity(), rotation * 360);

            rotation *= glm::two_pi<float>();
            p->velocity().x = glm::cos(rotation);
            p->velocity().y = glm::sin(rotation);

            p->update();
        }
    }

    void draw()
    {
        if( drawing_)
        {
            // draw on the canvas (ofFbo)
            easel_.begin();
                glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                // draw on canvas here
                //ofSetColor(139, 91, 8, 255);
                ofSetColor(draw_color_);
                //ofFill();
                for( auto& p : particles_)
                {
                    ofDrawCircle(p->pos(), 1.0 );
                }

            easel_.end();
        }
        // draw the canvas (ofFbo), centered by default
        //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        easel_.drawCanvas();

        ofEnableAlphaBlending();
        // draw UI
        drawGui();
    }

    void windowResized(int w, int h) {
        easel_.setViewSize(w,h);
        easel_.setCanvasSize(w * 0.85, h * 0.85);

        easel_.begin();
        ofSetColor(background_);
        ofFill();
        ofDrawRectangle(0,0, easel_.getCanvasWidth(), easel_.getCanvasHeight());
        easel_.end();
    }

private:
    Easel easel_;
    ofxImGui::Gui gui_;
    glm::vec2 noise_shift_;
    bool drawing_ = false;
    float backgroundf_[3] = {0.5f, 0.5f, 0.5f};
    ofColor background_ = ofColor(233, 203, 133);
    ofColor draw_color_ = ofColor( ofColor().black, 10);
    std::vector<shared_ptr<ofxBasicParticle>> particles_;

    void localSetup()
    {
        easel_.setViewSize(ofGetWidth(), ofGetHeight());
        easel_.setCanvasSize(ofGetHeight() * 0.85, ofGetHeight() * 0.85);
    }

    void drawGui()
    {
        gui_.begin();
            ImGui::Begin("PNoise FField");
            if(ImGui::CollapsingHeader("Canvas", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::ColorEdit3(" background", backgroundf_);
                background_.r = backgroundf_[0] * 255;
                background_.g = backgroundf_[1] * 255;
                background_.b = backgroundf_[2] * 255;
                if( ImGui::Button("Clear"))
                {
                    easel_.begin();
                    ofSetColor(background_);
                    ofFill();
                    ofDrawRectangle(0,0, easel_.getCanvasWidth(), easel_.getCanvasHeight());
                    easel_.end();

                    for( auto& p : particles_)
                    {
                        p->pos() = glm::vec2(easel_.getCanvasWidth() * ofRandomuf(), easel_.getCanvasHeight() * ofRandomuf());
                        p->velocity() = glm::vec2(0.0,0.0);
                    }

                    resetRandomSeed();
                }

                if( ImGui::Button("Save"))
                {
                    string fn = GenDateFileName();
                    SaveFbo( easel_.fbo(), "render/" + fn + ".png");
                }
            }

            if(ImGui::CollapsingHeader("Drawer", ImGuiTreeNodeFlags_DefaultOpen))
            {
                if( !drawing_)
                {
                    if( ImGui::Button("Start drawing") )
                        drawing_ = true;
                }
                else{
                    if( ImGui::Button("Stop drawing"))
                        drawing_ = false;
                }
            }

            ImGui::End();
        gui_.end();
    }

    void resetRandomSeed()
    {
        noise_shift_ = glm::vec2( ofRandomuf() * 1000, ofRandomuf() * 1000);
    }
};

#endif // NOISEFLOWWORMPAINTER_H
