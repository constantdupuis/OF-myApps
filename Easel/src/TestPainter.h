#ifndef TESTPAINTER_H
#define TESTPAINTER_H

#include "ofMain.h"
#include "ofxCanvasPainterBase.h"

class TestPainter : public ofxCanvasPainterBase
{
public:
    void setup( const ofxCanvasInfos& cNfo ) override
    {
        canvasInfos_ = cNfo;
    }

    void update() override
    {
        animation_ += 1.0f * ofGetLastFrameTime();
    }

    void draw() override
    {
        auto v = glm::sin( animation_ );
        v = (v+1.0f)*.5f;
        ofSetColor(255*v);
        ofDrawRectangle(0,0,canvasInfos_.width,canvasInfos_.height);
    }
private:
    float animation_ = 0.0f;
};

#endif // TESTPAINTER_H
