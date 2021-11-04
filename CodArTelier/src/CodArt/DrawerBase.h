#ifndef DRAWERBASE_H
#define DRAWERBASE_H

#include "ofMain.h"

namespace CodArTelier
{
    class DrawerBase {
    public:
        DrawerBase() {
        }

        virtual void Setup() {}
        virtual void Update() {}
        virtual void Draw() {}
        virtual void Reset() {}
        virtual void CanvasResized() {}

        virtual void DrawUI() {}

        virtual void keyPressed(int key) {}

        void Start()
        {
            is_drawing_ = true;
        }

        void Stop()
        {
            is_drawing_ = false;
        }

        bool isDrawing() { return is_drawing_; }

        void setCanvasSize( glm::vec2 canvas_size )
        {
            canvas_size_ = canvas_size;
            CanvasResized();
        }

    protected:
        glm::vec2 canvas_size_;
        bool is_drawing_ = true;
    private:
        
    };

    // -------------------------------------------------------------------
    // DrawerInfoAndFactoryBase
    // -------------------------------------------------------------------
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
