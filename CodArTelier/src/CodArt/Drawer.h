#ifndef DRAWER_H
#define DRAWER_H

#include "ofMain.h"

namespace CorArtelier
{
    class BrawerBase{
    public:
        BrawerBase() {

        }

        virtual void update(){}
        virtual void draw(){}
        virtual void reset() {}

        void start()
        {
            is_drawing_ = true;
        }

        void stop()
        {
            is_drawing_ = true;
        }

        bool isDrawing() { return is_drawing_;}

    private:
        bool is_drawing_ = true;
    };
}

#endif // DRAWER_H
