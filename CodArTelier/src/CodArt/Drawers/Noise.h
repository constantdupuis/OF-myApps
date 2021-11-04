#ifndef NOISE_H
#define NOISE_H

//#include "ofMain.h"
#include "../DrawerBase.h"
#include "../../lib/ofxValueGrid.h"
#include "../../lib/ofxBronianMotion.h"
#include "ofxImGui.h"

namespace CodArTelier
{
    namespace Drawer
    {
        ///
        /// \brief The Noise class
        ///
        class Noise : public DrawerBase
        {
        public:
            Noise() {

            }

            void Update()
            {
                if (!is_drawing_) return;
                animation_ += animation_speed_;
            }

            void Draw() {
                if (!is_drawing_) return;

                ofBackground( 60 );
                for( auto& c : value_grid_->cells() ){
                    auto a = bronian_motion_.get(c->left(), c->top(), animation_);
                    //ofSetColor( ofColor(ofColor().orangeRed ), a*255);
                    ofSetColor(255 * a);
                    ofDrawRectangle(c->left(),c->top(), c->width(), c->height());
                }
            }

            void DrawUI()
            {
                ImGui::Text(" grid settings");
                auto current_col_nbr = grid_col_nbr_;
                auto current_row_nbr = grid_row_nbr_;
                ImGui::InputInt(" col nbr", &current_col_nbr);
                ImGui::InputInt(" row nbr", &current_row_nbr);
                if( current_col_nbr != grid_col_nbr_ || current_row_nbr != grid_row_nbr_)
                {
                    grid_col_nbr_ = current_col_nbr;
                    grid_row_nbr_ = current_row_nbr;
                    CanvasResized();
                }

                ImGui::Spacing();
                ImGui::Text(" animation");
                ImGui::SliderFloat(" animation speed", &animation_speed_, 0.1, 50.0);
                ImGui::Spacing();
                if (isDrawing())
                {
                    if (ImGui::Button("stop"))
                    {
                        Stop();
                    }
                }
                else
                {
                    if (ImGui::Button("start"))
                    {
                        Start();
                    }
                }
                ImGui::Spacing();
                
                ImGui::Spacing();
                ImGui::Text(" bfm settigns");
                ImGui::SliderInt(" octaves number", &bronian_motion_.octavesNbr(), 1, 10);
                ImGui::SliderFloat(" frequency", &bronian_motion_.frequency(), 0.001, 0.01);
                ImGui::SliderFloat(" frequency multiplier", &bronian_motion_.frequencyMultiplier(), 0.5, 4.0);
            }

            void CanvasResized()
            {
                if( value_grid_)
                {
                    value_grid_.reset();
                }

                value_grid_ = make_shared<ofxValueGrid<ofxValueGridCell>>(grid_col_nbr_,grid_row_nbr_, canvas_size_.x, canvas_size_.y);
            }

        private:
            float animation_ = 0.0f;
            float animation_speed_ = 1.0f;
            ofxBronianMotion bronian_motion_;
            shared_ptr<ofxValueGrid<ofxValueGridCell>> value_grid_;
            int grid_col_nbr_ = 10;
            int grid_row_nbr_ = 10;
        };


        ///
        /// \brief The NoiseInfoFactory class
        ///
        class NoiseInfoNFactory : public DrawerInfoAndFactoryBase
        {
        public:
            NoiseInfoNFactory(){
                name_ = "Simple Perlin Noise";
                description_ = "Simple démo du Perlin Noise avec la possibilité d'ajouter des harmoniques (Factal Bronian Motion).";
            }

            shared_ptr<DrawerBase> Build(){
                return make_shared<Noise>();
            }

        };

        
    }
}

#endif // NOISE_H
