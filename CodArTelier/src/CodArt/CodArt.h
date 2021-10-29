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

        void Start() 
        {
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

        void SetCanvas(shared_ptr <Canvas> canvas)
        {
            canvas_ = canvas;
        }


        void keyPressed(int key) { if (drawer_) drawer_->keyPressed(key); }

    private:
        shared_ptr <Canvas> canvas_;
        shared_ptr<DrawerBase> drawer_;
    };
}

#endif // CODART_H
