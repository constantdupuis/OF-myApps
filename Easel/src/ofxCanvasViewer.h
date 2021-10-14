#ifndef OFXCANVASVIEWER_H
#define OFXCANVASVIEWER_H

#include "ofxCanvas.h"

class ofxCanvasViewer {
public:

    ofxCanvasViewer() {}

    ofxCanvasViewer(int width, int height, ofxCanvas& canvas)
    {
        width_ = width;
        height_ = height;
        canvas_ = canvas;
        calculate();
    }

    float setSize(int width, int height)
    {
        width_ = width;
        height_ = height;
        calculate();
        return scale_;
    }

    float fitToView()
    {
        if( canvas_.widht() > canvas_.height())
        {
            scale_ = (float)(width_ - margin_.x * 2.0) / (float)canvas_.widht();
        }
        else
        {
            scale_ = (float)(height_ - margin_.y * 2.0) / (float)canvas_.height();
        }
        calculate();
        return scale_;
    }

    void setMargin( int x, int y)
    {
        margin_.x = x;
        margin_.y = y;
    }

    float setScale( float scale)
    {
        if( scale == scale_) return scale_;
        scale_ = scale;
        calculate();

        return scale_;
    }

    float resetScale()
    {
        scale_ = 1.0f;
        calculate();
        return scale_;
    }

    float getScale()
    {
        return scale_;
    }

    void draw()
    {
        ofPushMatrix();
          ofTranslate( topLeft_ );
          ofScale( scale_ );
          canvas_.fbo().draw( 0.0f, 0.0f );
        ofPopMatrix();
    }

    void setCanvas( ofxCanvas& canvas)
    {
        canvas_ = canvas;
    }

private:
    int width_;
    int height_;
    glm::vec2 topLeft_;
    glm::vec2 margin_ = glm::vec2(10.0f, 10.0f);
    float scale_;

    ofxCanvas canvas_;

    void calculate()
    {
        topLeft_.x = (width_-(canvas_.widht()*scale_))/2.0f;
        topLeft_.y = (height_-(canvas_.height()*scale_))/2.0f;
    }
};

#endif // OFXCANVASVIEWER_H
