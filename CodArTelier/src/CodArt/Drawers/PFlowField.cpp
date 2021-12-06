#include "PFlowField.h"

namespace CodArTelier
{
    namespace Drawer
    {
        /// 
        /// P U B L I C
        /// 
        /// 
        void PFlowField::Setup()
        {
            bronian_motion_.setOctavesNbr(1);

            init_particles();
        }

        void PFlowField::Update()
        {
            if (!is_drawing_) return;
            animation_ += animation_speed_;

        }

        void PFlowField::Draw() {
            if (!is_drawing_) return;

            ofFill();
            ofSetColor(ofColor().yellowGreen);
            ofDrawRectangle(0,0, canvas_size_.x, canvas_size_.y);
            ofSetColor(100);

            for( const auto& p : particles_ )
            {
                // reborn out of the canvas particles
                if( p->pos())
                // update particle data
                // update particle position
                // dra particle
                ofDrawCircle( p->pos(), 2 );
            }
        }

        void PFlowField::DrawUI()
        {

        }

        void PFlowField::CanvasResized()
        {

        }

        void PFlowField::PushSettings(ofxXmlSettings& settings) {

        }

        bool PFlowField::ConfigureFromXmlSettings(ofxXmlSettings& settings) {

            return true;
        }

        /// 
        /// P R I V A T E
        /// 
        /// 
        void PFlowField::init_particles()
        {
            int x = 0;
            int y = 0;
            particles_.clear();
            for (int i = 0; i < particle_nbr_; i++)
            {
                x = ofRandom(canvas_size_.x);
                y = ofRandom(canvas_size_.y);
                particles_.push_back( make_shared<ofxBasicParticle>(x,y));
            }
        }
    }
}
