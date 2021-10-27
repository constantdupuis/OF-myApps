#ifndef CANVAS_H
#define CANVAS_H

#include "ofMain.h"
#include "CanvasSettings.h"

namespace CorArtelier
{
    class Canvas : public ofFbo
    {
    public:
        Canvas() {

        }

        void allocate()
        {

        }

        CanvasSettings& settings()
        { return settings_;}

    private:
        CanvasSettings settings_;
    };
}

#endif // CANVAS_H
