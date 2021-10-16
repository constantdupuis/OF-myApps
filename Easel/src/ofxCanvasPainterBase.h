#ifndef OFXCANVASPAINTERBASE_H
#define OFXCANVASPAINTERBASE_H

#include "ofMain.h"
#include "ofxCanvas.h"



class ofxCanvasPainterBase
{
public:
    ofxCanvasPainterBase(){}

    virtual void setup( const ofxCanvasInfos& cNfo ){ canvasInfos_ = cNfo; }
    virtual void update(){}
    virtual void draw(){}

    virtual void drawImGui(){}

    virtual void keyPressed(int key){}
    virtual void keyReleased(int key){}
    virtual void mouseMoved(int x, int y ){}
    virtual void mouseDragged(int x, int y, int button){}
    virtual void mousePressed(int x, int y, int button){}
    virtual void mouseReleased(int x, int y, int button){}
    virtual void mouseEntered(int x, int y){}
    virtual void mouseExited(int x, int y){}
    virtual void canvasChanged(const ofxCanvasInfos& cNfo){ canvasInfos_ = cNfo; }
    virtual void gotMessage(ofMessage msg){}
    virtual void dragEvent(ofDragInfo dragInfo){}

protected:
    ofxCanvasInfos canvasInfos_;
};

#endif // OFXCANVASPAINTERBASE_H
