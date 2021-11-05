#ifndef CODART_H
#define CODART_H

#include "ofMain.h"
#include "Canvas.h"
#include "DrawerBase.h"
#include "ofxXmlSettings.h"

namespace CodArTelier
{
    class CodArt{
    public:
        CodArt()
        {

        }

        void SetupRaw(shared_ptr<DrawerBase> drawer, int width, int heigth)
        {
            drawer_ = drawer;
            canvas_settings_.size_mode = CanvasSizeMode::Raw;
            canvas_settings_.raw.width = width;
            canvas_settings_.raw.height = heigth;

            canvas_ = make_shared<Canvas>(width, heigth);
            // TODO : handle case if canvas size is greater then view size
            drawer_->setCanvasSize(glm::vec2(width, heigth));
        }

        void SetupPercent(shared_ptr<DrawerBase> drawer, float percent_width, float percent_heigth, bool resize_when_view_change = false)
        {
            drawer_ = drawer;
            canvas_settings_.size_mode = CanvasSizeMode::ViewPercentage;
            canvas_settings_.view_percentage.width = percent_width;
            canvas_settings_.view_percentage.height = percent_heigth;
            canvas_settings_.view_percentage.square_canvas = false;
            canvas_settings_.view_percentage.resize_when_view_change = resize_when_view_change;

            int w = (int)((float)ofGetWidth() * (percent_width/100.0));
            int h = (int)((float)ofGetHeight() * (percent_heigth/100.0));

            if( !resize_when_view_change)
            {
                canvas_calculated_size_.x = w;
                canvas_calculated_size_.y = h;
            }

            canvas_ = make_shared<Canvas>(w, h);

            drawer_->setCanvasSize(glm::vec2(w, h));

            translate_.x = (ofGetWidth() - w ) / 2;
            translate_.y = (ofGetHeight() - h ) / 2;
        }

        void SetupPercentSquare(shared_ptr<DrawerBase> drawer, float percent_heigth, bool resize_when_view_change = false)
        {
            drawer_ = drawer;
            canvas_settings_.size_mode = CanvasSizeMode::ViewPercentage;
            canvas_settings_.view_percentage.width = percent_heigth;
            canvas_settings_.view_percentage.height = percent_heigth;
            canvas_settings_.view_percentage.square_canvas = true;
            canvas_settings_.view_percentage.resize_when_view_change = resize_when_view_change;

            int h = (int)((float)ofGetHeight() * (percent_heigth/100.0));

            if( !resize_when_view_change)
            {
                canvas_calculated_size_.x = h;
                canvas_calculated_size_.y = h;
            }

            canvas_ = make_shared<Canvas>(h, h);

            drawer_->setCanvasSize(glm::vec2(h, h));

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

        void DrawUI()
        {
            if( drawer_)
            {
                drawer_->DrawUI();
            }
        }

        void Release()
        {
        }

        void keyPressed(int key) { if (drawer_) drawer_->keyPressed(key); }

        void windowResized(int w, int h){
            if( !drawer_) return;

            if( canvas_settings_.size_mode == CanvasSizeMode::ViewPercentage)
            {
                if( canvas_settings_.view_percentage.resize_when_view_change)
                {
                    if( canvas_settings_.view_percentage.square_canvas)
                    {
                        int h = (int)((float)ofGetHeight() * (canvas_settings_.view_percentage.height/100.0));
                        translate_.x = (ofGetWidth() - h ) / 2;
                        translate_.y = (ofGetHeight() - h ) / 2;
                        canvas_->Resize(h, h);
                        drawer_->setCanvasSize(glm::vec2(h,h));
                    }
                    else
                    {
                        int h = (int)((float)ofGetHeight() * (canvas_settings_.view_percentage.height/100.0));
                        int w = (int)((float)ofGetWidth() * (canvas_settings_.view_percentage.width/100.0));
                        translate_.x = (ofGetWidth() - w ) / 2;
                        translate_.y = (ofGetHeight() - h ) / 2;
                        canvas_->Resize(w, h);
                        drawer_->setCanvasSize(glm::vec2(w,h));
                    }

                }
                else
                {
                    translate_.x = (ofGetWidth() - canvas_calculated_size_.x ) / 2;
                    translate_.y = (ofGetHeight() - canvas_calculated_size_.y ) / 2;
                }
            }
        }

        /// <summary>
        /// Push current CodArt settings to ofxXmlSettings
        /// </summary>
        /// <param name="settings"></param>
        void PushSettings(ofxXmlSettings& settings) {
            settings.setValue("codart:canvas:size_mode", (int)canvas_settings_.size_mode);
            settings.setValue("codart:canvas:raw:width", canvas_settings_.raw.width);
            settings.setValue("codart:canvas:raw:height", canvas_settings_.raw.height);
            settings.setValue("codart:canvas:view_percentage:square_canvas", canvas_settings_.view_percentage.square_canvas);
            settings.setValue("codart:canvas:view_percentage:resize_when_view_change", canvas_settings_.view_percentage.resize_when_view_change);
            settings.setValue("codart:canvas:view_percentage:width", canvas_settings_.view_percentage.width);
            settings.setValue("codart:canvas:view_percentage:height", canvas_settings_.view_percentage.height);

            settings.setValue("codart:drawer:id", canvas_settings_.view_percentage.height);

        }

        void PopSettings(ofxXmlSettings& settings) {
        }

    private:
        shared_ptr<Canvas> canvas_;
        shared_ptr<DrawerBase> drawer_;
        CanvasSettings canvas_settings_;
        glm::vec2 translate_;
        glm::vec2 canvas_calculated_size_;
    };
}

#endif // CODART_H
