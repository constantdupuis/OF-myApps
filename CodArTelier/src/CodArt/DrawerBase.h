#ifndef DRAWERBASE_H
#define DRAWERBASE_H

#include "ofMain.h"

namespace CodArTelier
{
    class DrawerBase {
    public:
        DrawerBase() {

        }

        virtual void update() {}
        virtual void draw() {}
        virtual void reset() {}

        virtual void keyPressed(int key) {}

        void start()
        {
            is_drawing_ = true;
        }

        void stop()
        {
            is_drawing_ = true;
        }

        bool isDrawing() { return is_drawing_; }

    private:
        bool is_drawing_ = true;
    };

    class DrawerInfoAndFactoryBase {
    public:
        DrawerInfoAndFactoryBase()
        {
            name_ = "_to_define_";
            description_ = "_to_define_";
        }

        const string& Name() { return name_; }
        const string& Description() { return description_; }
        virtual shared_ptr<DrawerBase> Build() = 0;

    protected:
        string name_;
        string description_;
    private:
    
    };

    
}

#endif // DRAWERBASE_H
