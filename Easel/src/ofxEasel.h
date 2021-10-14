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
        dessine le Canavas à chaque frame d'OF



*/

class ofxEasel {

public:

    enum class Type { Animated, Still };


    void startAnim();
    void pauseAnim();
    void resumeAnim();
    void stopAnim();

    void startStill();
    void pauseStill();
    void resumeStill();
    void stropStill();

private:
    Type type_ = Type::Still;

    void updateAnimationFrame();
    void drawAnimationFrame();

    void updateStillFrame();
    void drawStillFrame();

};

#endif // OFXEASEL_H
