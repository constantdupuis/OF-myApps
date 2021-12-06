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

            fill_particles();

            ofFill();
            ofSetColor(ofColor(255,255,255));
            ofDrawRectangle(0, 0, canvas_size_.x, canvas_size_.y);
        }

        void PFlowField::Update()
        {
            if (!is_drawing_) return;
            animation_ += animation_speed_;

        }

        void PFlowField::Draw() {
            if (!is_drawing_) return;

            int x = 0;
            int y = 0;
            ofFill();
            ofSetColor(ofColor(0,0,0,1));
            //ofSetColor(ofColor().red);

            for( auto& p : particles_ )
            {
                // Update particles
                if (p->pos().x < 0 || p->pos().x > canvas_size_.x || p->pos().y < 0 || p->pos().y > canvas_size_.y)
                {
                    x = ofRandom(canvas_size_.x);
                    y = ofRandom(canvas_size_.y);
                    p->pos().x = x;
                    p->pos().y = y;
                }

                // Update particles dir based on Fbm
                auto rotation = bronian_motion_.fbm( p->pos().x, p->pos().y, 12578.21);
                rotation *= glm::two_pi<float>();
                p->velocity().x = glm::cos(rotation);
                p->velocity().y = glm::sin(rotation);
                p->update();

                // Draw it

                ofDrawCircle( p->pos(), 1 );
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
                particles_.push_back( make_shared<ofxBasicParticle>(x,y) );
            }
        }
    }
}
