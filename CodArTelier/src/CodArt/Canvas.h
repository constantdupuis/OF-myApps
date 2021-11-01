#ifndef CANVAS_H
#define CANVAS_H

#include "ofMain.h"
#include "CanvasSettings.h"

namespace CodArTelier
{
    class Canvas : public ofFbo
    {
    public:
        // create raw sized canvas
        Canvas(int width, int height) {
            allocate(width, height, GL_RGBA);
        }

        ~Canvas()
        {
         ofFbo::~ofFbo();
        }

    private:

    };
}

#endif // CANVAS_H
