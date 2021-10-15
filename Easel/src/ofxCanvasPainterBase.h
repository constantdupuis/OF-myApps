#ifndef OFXCANVASPAINTERBASE_H
#define OFXCANVASPAINTERBASE_H

#include "ofMain.h"
#include "ofxCanvas.h"



class ofxCanvasPainterBase
{
public:
    ofxCanvasPainterBase(){}

    virtual void setup( const ofxCanvasInfos& cNfo ){}
    virtual void update( const ofxCanvasInfos& cNfo ){}
    virtual void draw( const ofxCanvasInfos& cNfo ){}

    virtual void keyPressed(int key){}
    virtual void keyReleased(int key){}
    virtual void mouseMoved(int x, int y ){}
    virtual void mouseDragged(int x, int y, int button){}
    virtual void mousePressed(int x, int y, int button){}
    virtual void mouseReleased(int x, int y, int button){}
    virtual void mouseEntered(int x, int y){}
    virtual void mouseExited(int x, int y){}
    virtual void windowResized(int w, int h){}
    virtual void gotMessage(ofMessage msg){}
    virtual void dragEvent(ofDragInfo dragInfo){}

private:

};

#endif // OFXCANVASPAINTERBASE_H
