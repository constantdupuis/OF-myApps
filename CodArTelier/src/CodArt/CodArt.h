#ifndef CODART_H
#define CODART_H

#include "ofMain.h"
#include "Canvas.h"

namespace CorArtelier
{
    class CodArt{
    public:
        CodArt() {
        }

    private:
        shared_ptr<Canvas> canvas_;
    };
}

#endif // CODART_H
