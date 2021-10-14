#ifndef OFXCANVAS_H
#define OFXCANVAS_H

#include "ofMain.h"

class ofxCanvas {
public:

    ofxCanvas()
    {
        allocate(width_, height_, internalFormat_);
    }

    ofxCanvas(int width, int height, int internalFormat)
    {
        allocate(width, height, internalFormat);
    }

    void allocate(int width, int height, int internalFormat)
    {
        if( isAllocated_ )
        {
            fbo_.reset();
            isAllocated_ = false;
        }
        width_ = width;
        height_ = height;
        internalFormat_ = internalFormat;
        fbo_ = make_shared<ofFbo>();
        fbo_->allocate(width_, height_, internalFormat_);
        isAllocated_ = true;
    }

    void begin() { fbo_->begin();}
    void end() { fbo_->end();}

    bool isAllocated() { return isAllocated_;}
    int widht() { return width_;}
    int height() {return height_;}
    const ofFbo& fbo() {return *fbo_;}


private:
    bool isAllocated_ = false;
    int width_ = 200;
    int height_ = 200;
    int internalFormat_ = GL_RGBA;
    shared_ptr<ofFbo> fbo_;
};

#endif // OFXCANVAS_H
