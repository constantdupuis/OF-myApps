#ifndef OFXEASEL_H
#define OFXEASEL_H

#include "ofxCanvas.h"
#include "ofxCanvasViewer.h"

/*

    Canvas : la ou ce fait le dessins
        taille en pixel x,y
        toujours un fxFbo
        saveToFile ()

    CanvasPainterBase(Canvas) : ce qui dessine sur le canvas
        animé ou fix
        setup
        update
        draw
        start/pause-resume/stop

    CanvasViewer(canvas) : la ou on affiche le canvas
        taille en pixel x,y
        Canvas toujours centrer
        Canvas zoom
        dessine le Canvas à chaque frame d'OF

*/

class ofxEasel {

public:

    ofxEasel(){}
    ofxEasel( shared_ptr<ofxCanvas> canvas, shared_ptr<ofxCanvasPainterBase> painter, shared_ptr<ofxCanvasViewer> viewer ){
        canvas_ = canvas;
        painter_ = painter;
        viewer_ = viewer;
    }

    void setup()
    {
        painter_->setup(canvas_->getCanvasInfos());
    }

    void update()
    {
        painter_->update(canvas_->getCanvasInfos());
    }

    void draw()
    {
        canvas_->begin();
        painter_->draw(canvas_->getCanvasInfos());
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
        painter_->windowResized(w,h);
    }

    void gotMessage(ofMessage msg){
        painter_->gotMessage(msg);
    }

    void dragEvent(ofDragInfo dragInfo){
        painter_->dragEvent(dragInfo);
    }

    const shared_ptr<ofxCanvasViewer> getViewer() { return viewer_;}

private:
    shared_ptr<ofxCanvasViewer> viewer_;
    shared_ptr<ofxCanvasPainterBase> painter_;
    shared_ptr<ofxCanvas> canvas_;
};

#endif // OFXEASEL_H
