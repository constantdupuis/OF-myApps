#ifndef OFXEASEL_H
#define OFXEASEL_H

#include "ofxCanvas.h"
#include "ofxCanvasViewer.h"
#include "ofxImGui.h"

class ofxEasel {

public:
    ofxEasel( int canvas_width, int canvas_heigth, int view_width, int view_height, shared_ptr<ofxCanvasPainterBase> painter){
        canvas_ = make_shared<ofxCanvas>(canvas_width, canvas_heigth);
        viewer_ = make_shared<ofxCanvasViewer>(view_width, view_height, canvas_);
        painter_ = painter;

        canvas_width_ = canvas_width;
        canvas_height_ = canvas_heigth;
        view_width_ = view_width;
        view_height_ = view_height;

        painter_->setup(canvas_->getCanvasInfos());
    }

    ofxEasel( shared_ptr<ofxCanvas> canvas, shared_ptr<ofxCanvasPainterBase> painter, shared_ptr<ofxCanvasViewer> viewer ){
        canvas_ = canvas;
        painter_ = painter;
        viewer_ = viewer;

        canvas_width_ = canvas_->getCanvasInfos().width;
        canvas_height_ = canvas_->getCanvasInfos().height;
        view_width_ = viewer_->getWidth();
        view_height_ = viewer_->getHeight();

        painter_->setup(canvas_->getCanvasInfos());
    }

    void setCanvasSize(int width, int height)
    {
        canvas_->reallocate(width, height);
        painter_->canvasChanged(canvas_->getCanvasInfos());
        viewer_->fitToView();
    }

    float setViewSize(int width, int height)
    {
        return viewer_->setSize(width, height);
    }

    void setup()
    {

    }

    void update()
    {
        painter_->update();
    }

    void draw()
    {
        canvas_->begin();
        painter_->draw();
        canvas_->end();
        viewer_->draw();
    }

    void keyPressed(int key)
    {
        painter_->keyPressed(key);
    }

    void keyReleased(int key)
    {
        painter_->keyReleased(key);
    }

    void mouseMoved(int x, int y )
    {
        painter_->mouseMoved(x,y);
    }

    void mouseDragged(int x, int y, int button)
    {
        painter_->mouseDragged(x,y,button);
    }

    void mousePressed(int x, int y, int button){
        painter_->mousePressed(x,y,button);
    }

    void mouseReleased(int x, int y, int button)
    {
        painter_->mouseReleased(x,y,button);
    }

    void mouseEntered(int x, int y){
        painter_->mouseEntered(x,y);
    }

    void mouseExited(int x, int y){
        painter_->mouseExited(x,y);
    }

    void windowsResized( int w, int h)
    {
        viewer_->setSize(w, h);
        view_width_ = w;
        view_height_ = h;

    }

    void gotMessage(ofMessage msg){
        painter_->gotMessage(msg);
    }

    void dragEvent(ofDragInfo dragInfo){
        painter_->dragEvent(dragInfo);
    }

    void drawImGui()
    {
        if(ImGui::CollapsingHeader("Canvas", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::InputInt("canvas width", &canvas_width_);
            ImGui::InputInt("canvas height", &canvas_height_);
            if( ImGui::Button("apply"))
            {
                setCanvasSize(canvas_width_, canvas_height_);
            }
        }

        if (ImGui::CollapsingHeader("View", ImGuiTreeNodeFlags_DefaultOpen ))
        {
            ImGui::SliderInt("view width", &view_width_, 50, ofGetWidth());
            ImGui::SliderInt("view height", &view_height_, 50, ofGetHeight());
            if( ImGui::Button("apply"))
            {
                setViewSize(view_width_, view_height_);
            }
            ImGui::SliderInt("horizontal margin", &margin_x_, 0, 1000);
            ImGui::SliderInt("vertical magrin", &margin_y_, 0, 1000);

            getViewer()->setMargin(margin_x_, margin_y_);

            if( ImGui::Button("fit to screen"))
            {
                zoom_ = getViewer()->fitToView();
            }

            ImGui::SliderFloat("factor", &zoom_, 0.01f, 10.0);
            if( ImGui::Button("reset scale"))
            {
                zoom_ = getViewer()->resetScale();
            }

            zoom_ = getViewer()->setScale(zoom_);
        }

        if (ImGui::CollapsingHeader("Painter", ImGuiTreeNodeFlags_DefaultOpen ))
        {
            painter_->drawImGui();
        }


    }

    const shared_ptr<ofxCanvasViewer> getViewer() { return viewer_;}

private:
    shared_ptr<ofxCanvasViewer> viewer_;
    shared_ptr<ofxCanvasPainterBase> painter_;
    shared_ptr<ofxCanvas> canvas_;

    float zoom_ = 1.0f;
    int margin_x_ = 10.0f;
    int margin_y_ = 10.0f;

    int view_width_;
    int view_height_;

    int canvas_width_;
    int canvas_height_;

};

#endif // OFXEASEL_H
