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
        private:
        };

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
