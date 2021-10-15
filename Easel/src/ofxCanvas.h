#ifndef OFXCANVAS_H
#define OFXCANVAS_H

#include "ofMain.h"

struct ofxCanvasInfos
{
    int width;
    int height;
};

class ofxCanvas : public ofFbo{
public:

    ofxCanvas()
    {
        localAllocate(400, 400, GL_RGBA);
    }

    ofxCanvas(int width, int height)
    {
        localAllocate(width, height, GL_RGBA);
    }

    ofxCanvas(int width, int height, int internalFormat)
    {
        localAllocate(width, height, internalFormat);
    }

    void reallocate(int width, int height, int internalFormat)
    {
        if( isAllocated() )
        {
            clear();
        }
        localAllocate(width, height, internalFormat);
    }

    const ofxCanvasInfos& getCanvasInfos() { return canvasInfos_; }

private:
    ofxCanvasInfos canvasInfos_;

    void localAllocate(int width, int height, int internalFormat)
    {
        allocate(width, height, internalFormat);
        canvasInfos_.width = width;
        canvasInfos_.height = height;
    }
};

#endif // OFXCANVAS_H
