#ifndef DRAWERBASE_H
#define DRAWERBASE_H

#include "ofMain.h"

namespace CodArTelier
{
    class DrawerBase {
    public:
        DrawerBase() {

        }

        virtual void Update() {}
        virtual void Draw() {}
        virtual void Reset() {}

        virtual void keyPressed(int key) {}

        void Start()
        {
            is_drawing_ = true;
        }

        void Stop()
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
        ofRectangle canvas_rect_;
    private:
    
    };

    
}

#endif // DRAWERBASE_H
