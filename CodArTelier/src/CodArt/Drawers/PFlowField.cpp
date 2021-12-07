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
            parameters_.setName("PNoise Flow");
            parameters_.add(background_color_.set("background color", ofColor(255)));
            parameters_.add(pen_color_.set("pen color", ofColor(0,0,0,2)));
            parameters_.add(angle_factor_.set("angle factor", 1.0, 0.01, 7.0) );
            parameters_.add(velocity_factor_.set("velocity factor", 1.0, 0.01, 5.0) );

            fbm_freq_.addListener(this, &PFlowField::fbmFreqChanged);
            fbm_octaves_nbr_.addListener(this, &PFlowField::fbmOctavesChanged);

            fbm_parameters_.add( fbm_freq_.set("freq", 0.001, 0.0001, 0.01));
            fbm_parameters_.add( fbm_octaves_nbr_.set("octaves", 1, 1, 10));
            parameters_.add(fbm_parameters_);

            bronian_motion_.setOctavesNbr(fbm_octaves_nbr_);
            bronian_motion_.setFrequency(fbm_freq_);

            // create initial particles batch
            init_particles();

            // default canvas background
            clearCanvas();
        }

        void PFlowField::Update()
        {
            if (!is_drawing_) return;
            animation_ += animation_speed_;

        }

        void PFlowField::Draw() {

            if(clear_)
            {
               clear_ = false;
               clearCanvas();
            }

            if (!is_drawing_) return;

            int x = 0;
            int y = 0;
            ofFill();
            ofSetColor(pen_color_.get());
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
                rotation *= glm::two_pi<float>() * angle_factor_;
                p->velocity().x = glm::cos(rotation) * velocity_factor_;
                p->velocity().y = glm::sin(rotation) * velocity_factor_;
                p->update();

                // Draw it

                ofDrawCircle( p->pos(), 1 );
            }
        }

        void PFlowField::DrawUI()
        {
            if( is_drawing_)
            {
                if( ImGui::Button("Stop Drawing"))
                {
                    is_drawing_ = false;
                }
            }
            else
            {
                if( ImGui::Button("Start Drawing"))
                {
                    is_drawing_ = true;
                }
            }
            if( ImGui::Button("Reset Canvas"))
            {
                clear_ = true;
            }
            if( ImGui::Button("Reset Partiles"))
            {
                init_particles();
            }
            if( ImGui::Button("Reset Parameters"))
            {
                angle_factor_ = 1.0f;
                velocity_factor_ = 1.0f;
                fbm_freq_ = 0.001f;
                fbm_octaves_nbr_ = 1;
            }
        }

        void PFlowField::CanvasResized()
        {

        }

        void PFlowField::PushSettings(ofxXmlSettings& settings) {

        }

        bool PFlowField::ConfigureFromXmlSettings(ofxXmlSettings& settings) {

            return true;
        }

        ofParameterGroup& PFlowField::getParameters()
        {
            return parameters_;
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

        void PFlowField::fbmOctavesChanged( int & octaves_nbr)
        {
            bronian_motion_.setOctavesNbr(octaves_nbr);
        }

        void PFlowField::fbmFreqChanged( float & freq ){
            bronian_motion_.setFrequency(freq);
        }

        void PFlowField::clearCanvas()
        {
            ofFill();
            ofSetColor(background_color_.get());
            ofDrawRectangle(0, 0, canvas_size_.x, canvas_size_.y);
            ofSetColor(background_color_.get());
            ofDrawRectangle(0, 0, canvas_size_.x, canvas_size_.y);
        }
    }
}
