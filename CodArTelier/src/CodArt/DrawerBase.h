#ifndef DRAWERBASE_H
#define DRAWERBASE_H

#include "ofMain.h"

namespace CodArTelier
{
    class DrawerBase{
    public:
        DrawerBase() {
            name_ = "_to_define_";
            description_ = "_to_define_";
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
        string name() { return name_;}

    protected:
        string name_;
        string description_;
    private:
        bool is_drawing_ = true;
    };
}

#endif // DRAWERBASE_H
