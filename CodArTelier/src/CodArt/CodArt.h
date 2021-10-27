#ifndef CODART_H
#define CODART_H

#include "ofMain.h"
#include "Canvas.h"
#include "DrawerBase.h"

namespace CodArTelier
{
    class CodArt{
    public:
        CodArt() {
        }

    private:
        shared_ptr<Canvas> canvas_;
        shared_ptr<DrawerBase> rawer_;
    };
}

#endif // CODART_H
