#ifndef BRONIANMOTIONPAINTER_H
#define BRONIANMOTIONPAINTER_H

#include "ofMain.h"
#include "ofxCanvasPainterBase.h"
#include "ofxValueGrid.h"
#include "ofxBronianMotion.h"
#include "gtc/noise.hpp"

class BronianMotionPainter : public ofxCanvasPainterBase
{
public:
    void setup( const ofxCanvasInfos& cNfo ) override
    {
        valueGrid_ = make_shared<ofxValueGrid<ofxValueGridCell>>( 200, 200, cNfo.width, cNfo.height);
        //ofSetColor(0,250,200);
    }

    void update( const ofxCanvasInfos& cNfo ) override
    {
        animation_ += .2f * ofGetLastFrameTime();
    }

    void draw( const ofxCanvasInfos& cNfo ) override
    {
        for (const auto& c : valueGrid_->cells())
        {
            auto n =  bfm.get(10.f + c->left(), 50.f + c->top(), animation_);
            ofSetColor( 255 * n );
            ofDrawRectangle(c->left(),c->top(),c->width(),c->height());
        }
    }
private:
    shared_ptr<ofxValueGrid<ofxValueGridCell>> valueGrid_;
    ofxBronianMotion bfm = ofxBronianMotion(6, 0.003);
    float animation_ = 0.0f;
};

#endif // BRONIANMOTIONPAINTER_H
