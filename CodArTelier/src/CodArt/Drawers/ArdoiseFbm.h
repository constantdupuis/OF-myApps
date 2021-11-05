#ifndef NOISE_H
#define NOISE_H

//#include "ofMain.h"
#include "../DrawerBase.h"
#include "../../lib/ofxValueGrid.h"
#include "../../lib/ofxBronianMotion.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"

namespace CodArTelier
{
    namespace Drawer
    {
        ///
        /// \brief The Noise class
        ///
        class ArdoiseFbm : public DrawerBase
        {
        public:
            ArdoiseFbm() {

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
                    float a;
                    if (fbm_mode_ == FbmMode::normal)
                        a = bronian_motion_.fbm(c->left(), c->top(), animation_);
                    else if (fbm_mode_ == FbmMode::turbulence)
                        a = bronian_motion_.fbmTurbulence(c->left(), c->top(), animation_);
                    else if (fbm_mode_ == FbmMode::ridge)
                        a = bronian_motion_.fbmRidge(c->left(), c->top(), animation_);
                    else
                    {
                        // TODO
                    }

                    if (a > 1.0f) a = 1.0f;
                    
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

                ImGui::Spacing();
                ImGui::Text(" draw mode");
                int fm = static_cast<int>(fbm_mode_);
                ImGui::RadioButton(" normal", &fm, 0); ImGui::SameLine();
                ImGui::RadioButton(" turbulence", &fm, 1); ImGui::SameLine();
                ImGui::RadioButton(" ridge", &fm, 2);
                fbm_mode_ = static_cast<FbmMode>(fm);
            }

            void CanvasResized()
            {
                if( value_grid_)
                {
                    value_grid_.reset();
                }

                value_grid_ = make_shared<ofxValueGrid<ofxValueGridCell>>(grid_col_nbr_,grid_row_nbr_, canvas_size_.x, canvas_size_.y);
            }

            void PushSettings(ofxXmlSettings& settings) {
            }
            void PopSettings(ofxXmlSettings& settings) {
            }

        private:
            enum class FbmMode {normal = 0, turbulence, ridge};
            FbmMode fbm_mode_ = FbmMode::normal;
            float animation_ = 0.0f;
            float animation_speed_ = 1.0f;
            ofxBronianMotion bronian_motion_;
            shared_ptr<ofxValueGrid<ofxValueGridCell>> value_grid_;
            int grid_col_nbr_ = 150;
            int grid_row_nbr_ = 150;
        };


        ///
        /// \brief The NoiseInfoFactory class
        ///
        class ArdoiseFbmInfoNFactory : public DrawerInfoAndFactoryBase
        {
        public:
            ArdoiseFbmInfoNFactory(){
                id_ = "ArdoiseFbm";
                name_ = "Ardoise Fbm";
                description_ = "Adrdoise pour jouer avec le Fractal Bronian Motion";
            }

            shared_ptr<DrawerBase> Build(){
                return make_shared<ArdoiseFbm>();
            }

        };

        
    }
}

#endif // NOISE_H
