#ifndef CANVAS_H
#define CANVAS_H

#include "ofMain.h"
#include "CanvasSettings.h"

namespace CodArTelier
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
