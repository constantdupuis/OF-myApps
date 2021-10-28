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

        void Stop()
        {
        }

        void Release()
        {
        }

        void SetDrawer(shared_ptr<DrawerBase> drawer)
        {
            drawer_ = drawer;
        }


        void keyPressed(int key) { if (drawer_) drawer_->keyPressed(key); }

    private:
        Canvas canvas_;
        shared_ptr<DrawerBase> drawer_;
    };
}

#endif // CODART_H
