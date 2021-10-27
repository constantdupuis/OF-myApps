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
                name_ = "Noise Simple";
                description_ = "Simple CODART pour jouer avec le Perlin Noise";
            }
        private:
        };
    }
}

#endif // NOISE_H
