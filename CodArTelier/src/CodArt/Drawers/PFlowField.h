#pragma once

#include "../DrawerBase.h"
#include "../../lib/ofxBronianMotion.h"
#include "../../lib/ofxBasicParticle.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"

namespace CodArTelier
{
    namespace Drawer
    {
        ///
        /// \brief The Noise class
        ///
        class PFlowField : public DrawerBase
        {
        public:
            PFlowField(string id) : DrawerBase(id) {}

            void Setup();
            void Update();
            void Draw();
            void DrawUI();
            void CanvasResized();
            void PushSettings(ofxXmlSettings& settings);
            bool ConfigureFromXmlSettings(ofxXmlSettings& settings);
            ofParameterGroup& getParameters();

        private:
            enum class FbmMode { normal = 0, turbulence, ridge };
            FbmMode fbm_mode_ = FbmMode::normal;
            float animation_ = 0.0f;
            float animation_speed_ = 1.0f;
            ofxBronianMotion bronian_motion_;
            bool clear_ = false;

            vector<shared_ptr<ofxBasicParticle>> particles_;

            ofParameter<int> particle_nbr_ {5000};
            ofParameter<ofFloatColor> background_color_;
            ofParameter<ofFloatColor> pen_color_;
            ofParameter<int> pen_width_ {1};
            ofParameter<float> angle_factor_ {1.0f};
            ofParameter<float> velocity_factor_ {1.0f};

            ofParameterGroup fbm_parameters_ {"Fbm"};
            ofParameter<float> fbm_freq_ {0.001};
            ofParameter<int> fbm_octaves_nbr_ {1};

            void init_particles();
            void fbmOctavesChanged( int & octaves_nbr);
            void fbmFreqChanged( float & freq );
            void clearCanvas();
        };


        ///
        /// \brief The NoiseInfoFactory class
        ///
        class PFlowFieldInfoNFactory : public DrawerInfoAndFactoryBase
        {
        public:
            PFlowFieldInfoNFactory() {
                id_ = "PFlowField";
                name_ = "Perlin Noise flow field";
                description_ = "Perlin noise or Fbm flow field";
            }

            shared_ptr<DrawerBase> Build() {
                return make_shared<PFlowField>(id_);
            }

        };


    }
}


