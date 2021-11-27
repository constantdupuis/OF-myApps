#pragma once

#include "../DrawerBase.h"
#include "../../lib/ofxValueGrid.h"
#include "../../lib/ofxBronianMotion.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"
namespace CodArTelier
{
    namespace Drawer
    {
        class PFlowFeathers : public DrawerBase {
        public:
            PFlowFeathers(string id) : DrawerBase(id) {
                bronian_motion_.setOctavesNbr(1);
                bronian_motion_.setFrequency(0.002f);
                bronian_motion_.setFrequencyMultiplier(2.0f);
            }

            void Setup() {

            }

            void Update()
            {
                if (!is_drawing_) return;
                animation_ += animation_speed_;
            }

            void Draw() {
                if (!is_drawing_) return;
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofBackground(20);
                float a;
                for (auto& c : value_grid_->cells()) {
                    a = bronian_motion_.fbm(c->left(), c->top(), animation_);

                    ofPushMatrix();

                    ofTranslate(translate_.x + c->pointX(), translate_.y + c->pointY());
                    ofRotateDeg(a*360);
                    ofScale(5);

                    ofFill();
                    ofSetColor(a * 255, alpha_);

                    if( use_ellipse_)
                        ofDrawEllipse(0, 0, c->width()*2., c->height() * 0.4);
                    else
                        ofDrawRectangle(0, 0, c->width()*2., c->height() * 0.4);

//                    ofNoFill();
//                    ofSetColor(255-(a * 255), 255);
//                    if( use_ellipse_)
//                        ofDrawEllipse(0, 0, c->width()*2., c->height() * 0.4);
//                    else
//                        ofDrawRectangle(0, 0, c->width()*2., c->height() * 0.4);

                    ofPopMatrix();
                }
            }

            void CanvasResized()
            {
                if (value_grid_)
                {
                    value_grid_.reset();
                }

                auto inside_width = canvas_size_.x * margin_;
                auto inside_height = canvas_size_.y * margin_;
                translate_.x = (canvas_size_.x - inside_width) / 2.0f;
                translate_.y = (canvas_size_.y - inside_height) / 2.0f;

                value_grid_ = make_shared<ofxValueGrid<ofxValueGridCell>>(grid_col_nbr_, grid_row_nbr_, inside_width, inside_height);
            }

        private:
            float animation_ = 0.0f;
            float animation_speed_ = 0.5f;
            ofxBronianMotion bronian_motion_;
            shared_ptr<ofxValueGrid<ofxValueGridCell>> value_grid_;
            int grid_col_nbr_ = 50;
            int grid_row_nbr_ = 50;
            float margin_ = 0.80f;
            glm::vec2 translate_;
            bool use_ellipse_ = false;
            int alpha_ = 200;

        };

        ///
        /// \brief The NoiseInfoFactory class
        ///
        class PFlowFeathersInfoNFactory : public DrawerInfoAndFactoryBase
        {
        public:
            PFlowFeathersInfoNFactory() {
                id_ = "PFlowFeather";
                name_ = "Perlin Flow Feather";
                description_ = "Comme des plumes ....";
            }

            shared_ptr<DrawerBase> Build() {
                return make_shared<PFlowFeathers>(id_);
            }

        };
    }
}
