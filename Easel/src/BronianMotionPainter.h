#ifndef BRONIANMOTIONPAINTER_H
#define BRONIANMOTIONPAINTER_H

#include "ofMain.h"
#include "ofxCanvasPainterBase.h"
#include "ofxValueGrid.h"
#include "ofxBronianMotion.h"
#include "ofxImGui.h"

class BronianMotionPainter : public ofxCanvasPainterBase
{
public:
    BronianMotionPainter() {}

    void setup( const ofxCanvasInfos& cNfo ) override
    {
        ofxCanvasPainterBase::setup(cNfo); // base class method must be called
        setupGrid();
        setupBfm();
        //ofSetColor(0,250,200);
    }

    void canvasChanged(  const ofxCanvasInfos& cNfo  ) override
    {
        ofxCanvasPainterBase::canvasChanged(cNfo); // base class method must be called
        setupGrid();
    }

    void update() override
    {
        if( animate_) animation_ += animationSpeed_ * ofGetLastFrameTime();
    }

    void draw() override
    {
        for (const auto& c : valueGrid_->cells())
        {
            auto n =  bfm_->get(10.f + c->left(), 50.f + c->top(), animation_);
            ofSetColor( 255 * n );
            ofDrawRectangle(c->left(), c->top(), c->width(), c->height());
        }
    }

    void drawImGui() override
    {
        ImGui::Checkbox("animate", &animate_);
        ImGui::SliderFloat("animation speed", &animationSpeed_, 1.0f, 100.0f);
        ImGui::InputInt2("grid size", gridSize_);
        if(ImGui::Button("apply grid size"))
        {
            setupGrid();
        }
        ImGui::Text("Bronian Motion");
        ImGui::InputInt("octaves", &bfmOctaves_);
        ImGui::InputFloat("frequency", &bfmFrequency_);
        ImGui::InputFloat("frequency multiplier ", &bfmFrequencyMultilier_);
        if( ImGui::Button("apply bfm"))
        {
            setupBfm();
        }

    }
private:
    shared_ptr<ofxValueGrid<ofxValueGridCell>> valueGrid_;
    shared_ptr<ofxBronianMotion> bfm_; // = ofxBronianMotion(6, 0.003f, 2.0f);
    bool animate_ = true;
    float animation_ = 0.0f;
    float animationSpeed_ = 30.0f;
    int gridSize_[2] = {50,50};

    int bfmOctaves_ = 6;
    float bfmFrequency_ = 0.003f;
    float bfmFrequencyMultilier_ = 2.0f;

    void setupGrid()
    {
        valueGrid_.reset();
        valueGrid_ = make_shared<ofxValueGrid<ofxValueGridCell>>( gridSize_[0], gridSize_[1],
                                                                  canvasInfos_.width, canvasInfos_.height);
    }

    void setupBfm()
    {
        bfm_.reset();
        bfm_= make_shared<ofxBronianMotion>(bfmOctaves_, bfmFrequency_, bfmFrequencyMultilier_);
    }
};

#endif // BRONIANMOTIONPAINTER_H
