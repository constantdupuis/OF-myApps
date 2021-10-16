#ifndef OFXCANVASVIEWER_H
#define OFXCANVASVIEWER_H

#include "ofxCanvas.h"
#include "ofxCanvasPainterBase.h"

class ofxCanvasViewer {
public:

    ofxCanvasViewer() {}

    ofxCanvasViewer(int width, int height, shared_ptr<ofxCanvas> canvas)
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
        if( canvas_->getWidth() > canvas_->getHeight())
        {
            scale_ = (float)(width_ - margin_.x * 2.0) / (float)canvas_->getWidth();
        }
        else
        {
            scale_ = (float)(height_ - margin_.y * 2.0) / (float)canvas_->getHeight();
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
          canvas_->draw( 0.0f, 0.0f );
        ofPopMatrix();
    }

    void setCanvas( shared_ptr<ofxCanvas> canvas)
    {
        canvas_ = canvas;
        fitToView();
    }

    int getWidth() { return width_;}
    int getHeight() { return height_;}

private:
    int width_;
    int height_;
    glm::vec2 topLeft_;
    glm::vec2 margin_ = glm::vec2(10.0f, 10.0f);
    float scale_ = 1.0f;

    shared_ptr<ofxCanvas> canvas_;

    void calculate()
    {
        topLeft_.x = (width_-(canvas_->getWidth()*scale_))/2.0f;
        topLeft_.y = (height_-(canvas_->getHeight()*scale_))/2.0f;
    }
};

#endif // OFXCANVASVIEWER_H
