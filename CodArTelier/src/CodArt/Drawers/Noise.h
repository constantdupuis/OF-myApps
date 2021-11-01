#ifndef NOISE_H
#define NOISE_H

#include "../DrawerBase.h"

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
            void Draw() {
                ofBackground( ofColor().limeGreen);
                ofSetColor( ofColor(ofColor().orangeRed ));
                ofDrawRectRounded(10,10, canvas_size_.x-20, canvas_size_.y-20, 5);
            }
        private:
        };


        ///
        /// \brief The NoiseInfoFactory class
        ///
        class NoiseInfoFactory : public DrawerInfoAndFactoryBase
        {
        public:
            NoiseInfoFactory(){
                name_ = "Simple Perlin Noise";
                description_ = "Simple démo du Perlin Noiser avec la possibilité d'ajouter des harmoniques (Factal Bronian Motion).";
            }

            shared_ptr<DrawerBase> Build(){
                return make_shared<Noise>();
            }

        };

        
    }
}

#endif // NOISE_H
