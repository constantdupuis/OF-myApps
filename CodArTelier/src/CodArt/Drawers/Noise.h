#ifndef NOISE_H
#define NOISE_H

#include "../DrawerBase.h"

namespace CodArTelier
{
    namespace Drawer
    {
        class Noise : public DrawerBase
        {
        public:
            Noise() {
            }
            void Draw() {

            }
        private:
        };

        class NoiseInfoFactory : public DrawerInfoAndFactoryBase
        {
        public:
            NoiseInfoFactory(){
                name_ = "Simple Perlin Noise";
                description_ = "Simple d�mo du Perlin Noiser avec la possibilit� d'ajouter des harmoniques (Factal Bronian Motion).";
            }

            shared_ptr<DrawerBase> Build(){
                return make_shared<Noise>();
            }

        };

        
    }
}

#endif // NOISE_H
