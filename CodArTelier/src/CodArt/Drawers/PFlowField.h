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

        private:
            enum class FbmMode { normal = 0, turbulence, ridge };
            FbmMode fbm_mode_ = FbmMode::normal;
            float animation_ = 0.0f;
            float animation_speed_ = 1.0f;
            ofxBronianMotion bronian_motion_;

            int particle_nbr_ = 200;
            vector<shared_ptr<ofxBasicParticle>> particles_;

            void fill_particles();
        };


        ///
        /// \brief The NoiseInfoFactory class
        ///
        class PFlowFieldInfoNFactory : public DrawerInfoAndFactoryBase
        {
        public:
            PFlowFieldInfoNFactory() {
                id_ = "ArdoiseFbm";
                name_ = "Ardoise Fbm";
                description_ = "Adrdoise pour jouer avec le Fractal Bronian Motion";
            }

            shared_ptr<DrawerBase> Build() {
                return make_shared<PFlowField>(id_);
            }

        };


    }
}


