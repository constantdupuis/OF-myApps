#ifndef DRAWERBASE_H
#define DRAWERBASE_H

#include "ofMain.h"
#include "ofxXmlSettings.h"

namespace CodArTelier
{
    class DrawerBase {
    public:
        DrawerBase()
        {
            id_ = "none";
        }
        DrawerBase( string id) {
            id_ = id;
        }

        virtual void Setup() {}
        virtual void Update() {}
        virtual void Draw() {}
        virtual void Reset() {}
        virtual void CanvasResized() {}
        virtual void DrawUI() {}
        virtual void keyPressed(int key) {}
        virtual void PushSettings(ofxXmlSettings& settings) {}
        //virtual void PopSettings(ofxXmlSettings& settings) {}
        virtual bool ConfigureFromXmlSettings(ofxXmlSettings& settings) { 
            ofLogFatalError("DrawerBase") << "You forgot to override ConfigureFromXmlSettings!";
            return false; 
        }

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

        const string& Id() {return id_;}

    protected:
        glm::vec2 canvas_size_;
        bool is_drawing_ = true;
        string id_;
        //DrawerInfoAndFactoryBase
    private:

        
    };

    // -------------------------------------------------------------------
    // DrawerInfoAndFactoryBase
    // -------------------------------------------------------------------
    class DrawerInfoAndFactoryBase {
    public:
        DrawerInfoAndFactoryBase()
        {
            id_ = "_to_define_";
            name_ = "_to_define_";
            description_ = "_to_define_";
        }

        const string& Id() { return id_;}
        const string& Name() { return name_; }
        const string& Description() { return description_; }
        virtual shared_ptr<DrawerBase> Build() = 0;

    protected:
        string id_;
        string name_;
        string description_;
    private:
    
    };

    
}

#endif // DRAWERBASE_H
