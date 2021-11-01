#ifndef CODART_H
#define CODART_H

#include "ofMain.h"
#include "Canvas.h"
#include "DrawerBase.h"

namespace CodArTelier
{
    class CodArt{
    public:

        CodArt(shared_ptr<DrawerBase> drawer, int width, int heigth)
        {
            drawer_ = drawer;
            canvas_settings_.size_mode = CanvasSizeMode::Raw;
            canvas_settings_.raw.width = width;
            canvas_settings_.raw.height = heigth;
            canvas_ = make_shared<Canvas>(width, heigth);
        }

        CodArt(shared_ptr<DrawerBase> drawer, float percent_width, float percent_heigth, bool resize_when_view_change = false)
        {
            drawer_ = drawer;
            canvas_settings_.size_mode = CanvasSizeMode::ViewPercentage;
            canvas_settings_.view_percentage.width = percent_width;
            canvas_settings_.view_percentage.height = percent_heigth;
            canvas_settings_.view_percentage.square_canvas = false;
            canvas_settings_.view_percentage.resize_when_view_change = resize_when_view_change;

            auto w = ofGetWidth() * percent_width;
            auto h = ofGetHeight() * percent_heigth;

            canvas_ = make_shared<Canvas>(w, h);

            translate_.x = (ofGetWidth() - w ) / 2;
            translate_.y = (ofGetHeight() - h ) / 2;
        }

        CodArt(shared_ptr<DrawerBase> drawer, float percent_heigth, bool resize_when_view_change = false)
        {
            drawer_ = drawer;
            canvas_settings_.size_mode = CanvasSizeMode::ViewPercentage;
            canvas_settings_.view_percentage.width = percent_heigth;
            canvas_settings_.view_percentage.height = percent_heigth;
            canvas_settings_.view_percentage.square_canvas = true;
            canvas_settings_.view_percentage.resize_when_view_change = resize_when_view_change;

            auto h = ofGetHeight() * percent_heigth;

            canvas_ = make_shared<Canvas>(h, h);

            translate_.x = (ofGetWidth() - h ) / 2;
            translate_.y = (ofGetHeight() - h ) / 2;
        }

        void Start() 
        {
            drawer_->Start();
        }

        void Stop()
        {
            drawer_->Stop();
        }

        void Update()
        {
            drawer_->Update();
        }

        void Draw()
        {
            // Allow drawer to draw on canvas
            canvas_->begin();
            drawer_->Draw();
            canvas_->end();

            // draw canvas to screen
            ofPushMatrix();
            ofTranslate( translate_);
            canvas_->draw(0,0);
            ofPopMatrix();
        }

        void Release()
        {
        }

//        void SetDrawer(shared_ptr<DrawerBase> drawer)
//        {
//            drawer_ = drawer;
//        }

//        void SetCanvas(shared_ptr <Canvas> canvas)
//        {
//            canvas_ = canvas;
//        }


        void keyPressed(int key) { if (drawer_) drawer_->keyPressed(key); }

    private:
        shared_ptr<Canvas> canvas_;
        shared_ptr<DrawerBase> drawer_;
        CanvasSettings canvas_settings_;
        glm::vec2 translate_;
    };
}

#endif // CODART_H
