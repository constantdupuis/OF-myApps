#ifndef CODART_H
#define CODART_H

#include "ofMain.h"
#include "ofxImGui.h"
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

        bool Setup(shared_ptr<DrawerBase>& drawer, CanvasSettings canvas_settings)
        {
            bool ret = true;
            drawer_ = drawer;
            canvas_settings_ = canvas_settings;

            if (canvas_settings_.size_mode == CANVAS_SIZE_MODE_RAW)
            {
                // TODO : Calculate a scale if needed
                canvas_ = make_shared<Canvas>(canvas_settings_.raw.width, canvas_settings_.raw.height);
                drawer_->setCanvasSize(glm::vec2(canvas_settings_.raw.width, canvas_settings_.raw.height));
                CalculateViewParams(canvas_settings_.raw.width, canvas_settings_.raw.height);
            }
            else if (canvas_settings_.size_mode == CANVAS_SIZE_MODE_PAPER_FORMAT)
            {
                // TODO : paper format
                ret = false;
            }
            else if (canvas_settings_.size_mode == CANVAS_SIZE_MODE_VIEW_PERCENT)
            {
                int w, h;
                if( canvas_settings_.view_percentage.square_canvas )
                {
                    w = (int)((float)ofGetHeight() * (canvas_settings_.view_percentage.height / 100.0));
                    h = (int)((float)ofGetHeight() * (canvas_settings_.view_percentage.height / 100.0));
                }
                else
                {
                    w = (int)((float)ofGetWidth() * (canvas_settings_.view_percentage.width / 100.0));
                    h = (int)((float)ofGetHeight() * (canvas_settings_.view_percentage.height / 100.0));
                }

                CalculateViewParams(w,h);

//                translate_.x = (ofGetWidth() - w) / 2;
//                translate_.y = (ofGetHeight() - h) / 2;

//                if (!canvas_settings_.view_percentage.resize_when_view_change)
//                {
//                    canvas_calculated_size_.x = w;
//                    canvas_calculated_size_.y = h;
//                }

                canvas_ = make_shared<Canvas>(w, h);
                drawer_->setCanvasSize(glm::vec2(w, h));
            }
            else 
            {
                // TODO : error message
                ret = false;
            }
            return ret;
        }
      
//        static shared_ptr<CodArt> SetupFromXmlSettings( ofxXmlSettings settings)
//        {
//              return nullptr;
//        }

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
            ofTranslate( translate_ );
            ofScale( scale_) ;
            canvas_->draw(0,0);
            ofPopMatrix();
        }

        void DrawUI()
        {
            char* cString = new char[256];

            strcpy(cString, name_.c_str());
            if (ImGui::InputText(" name", cString, 128))
            {
                name_ = cString;
            }

           /* strcpy(cString, description_.c_str());
            if (ImGui::InputTextMultiline(" description", cString, 256))
            {
                description_ = cString;
            }*/

            delete[] cString;

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::SliderFloat(" scale", &scale_, 0.1f, 2.0f);

            ImGui::Spacing();

            if(drawer_)
            {
                if (ImGui::CollapsingHeader("Drawer", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf))
                {
                    drawer_->DrawUI();
                }
            }
        }

        void Release()
        {
        }

        void keyPressed(int key) { if (drawer_) drawer_->keyPressed(key); }

        void windowResized(int w, int h){
            if( !drawer_) return;

            // TODO handle other Size Modes
            if( canvas_settings_.size_mode == CANVAS_SIZE_MODE_VIEW_PERCENT)
            {
                if( canvas_settings_.view_percentage.resize_when_view_change)
                {
                    if( canvas_settings_.view_percentage.square_canvas)
                    {
                        int h = (int)((float)ofGetHeight() * (canvas_settings_.view_percentage.height/100.0));
                        CalculateViewParams(h, h);
                        canvas_->Resize(h, h);
                        drawer_->setCanvasSize(glm::vec2(h,h));
                    }
                    else
                    {
                        int h = (int)((float)ofGetHeight() * (canvas_settings_.view_percentage.height/100.0));
                        int w = (int)((float)ofGetWidth() * (canvas_settings_.view_percentage.width/100.0));
                        CalculateViewParams(w, h);
                        canvas_->Resize(w, h);
                        drawer_->setCanvasSize(glm::vec2(w,h));
                    }
                }
                else
                {
                    CalculateViewParams(canvas_calculated_size_.x, canvas_calculated_size_.y);
                }
            }

            CalculateViewParams(canvas_calculated_size_.x, canvas_calculated_size_.y);
        }

        void CalculateViewParams( int canvas_w, int canvas_h)
        {
            canvas_calculated_size_.x = canvas_w;
            canvas_calculated_size_.y = canvas_h;
            auto view_w = ofGetWidth();
            auto view_h = ofGetHeight();

            if( canvas_calculated_size_.x < view_w && canvas_calculated_size_.y < view_h)
            {
                scale_ = 1.0f;
                translate_.x = (view_w - canvas_calculated_size_.x ) / 2;
                translate_.y = (view_h - canvas_calculated_size_.y ) / 2;
            }
            else
            {
                if( canvas_calculated_size_.x > canvas_calculated_size_.y)
                {
                    auto ratio = (float)(view_w-margin*2)/(float)canvas_calculated_size_.x;
                    auto scaled_w = canvas_calculated_size_.x * ratio;
                    auto scaled_h = canvas_calculated_size_.y * ratio;
                    scale_ = ratio;
                    translate_.x = (view_w - scaled_w ) / 2;
                    translate_.y = (view_h - scaled_h ) / 2;
                }
                else if( canvas_calculated_size_.x < canvas_calculated_size_.y)
                {
                    auto ratio = (float)(view_h-margin*2)/(float)canvas_calculated_size_.y;
                    auto scaled_w = canvas_calculated_size_.x * ratio;
                    auto scaled_h = canvas_calculated_size_.y * ratio;
                    scale_ = ratio;
                    translate_.x = (view_w - scaled_w ) / 2;
                    translate_.y = (view_h - scaled_h ) / 2;
                }
            }
        }

        /// <summary>
        /// Push current CodArt settings to ofxXmlSettings
        /// </summary>
        /// <param name="settings"></param>
        void PushConfigToXmlSettings(ofxXmlSettings& settings) {
            settings.addTag("codart");
            settings.pushTag("codart");

            settings.setValue("name", name_);
            settings.setValue("description", description_);

            settings.addTag("canvas");
            settings.pushTag("canvas");
            settings.setValue("size_mode", canvas_settings_.size_mode);
            if( canvas_settings_.size_mode == CANVAS_SIZE_MODE_RAW)
            {
                settings.setValue("raw:width", canvas_settings_.raw.width);
                settings.setValue("raw:height", canvas_settings_.raw.height);
            }
            else if(canvas_settings_.size_mode == CANVAS_SIZE_MODE_PAPER_FORMAT)
            {
                settings.setValue("paper", "not yet implemented");
            }
            else if(canvas_settings_.size_mode == CANVAS_SIZE_MODE_VIEW_PERCENT)
            {
                settings.setValue("view_percentage:square_canvas", canvas_settings_.view_percentage.square_canvas);
                settings.setValue("view_percentage:resize_when_view_change", canvas_settings_.view_percentage.resize_when_view_change);
                settings.setValue("view_percentage:width", canvas_settings_.view_percentage.width);
                settings.setValue("view_percentage:height", canvas_settings_.view_percentage.height);
            }
            else
            {
                ofLogError("PushSettings") << "Unkown canvas size mode [" << canvas_settings_.size_mode << "]";
            }
            settings.popTag();

            settings.addTag("drawer");
            settings.pushTag("drawer");
            settings.setValue("id",drawer_->Id());
            drawer_->PushSettings(settings);
            settings.popTag();
        }

        void PopSettings(ofxXmlSettings& settings) {

        }

        const string& getName()
        {
            return name_;
        }

        void setName( const string& name )
        {
            name_ = name;
        }

        const string& getDescription()
        {
            return description_;
        }

        void setDescription( const string& description )
        {
            description_ = description;
        }

    private:
        string name_;
        string description_;
       
        shared_ptr<Canvas> canvas_;
        shared_ptr<DrawerBase> drawer_;
        CanvasSettings canvas_settings_;

        float scale_;
        glm::vec2 translate_;
        glm::vec2 canvas_calculated_size_;
        const int margin = 10;
    };
}

#endif // CODART_H
