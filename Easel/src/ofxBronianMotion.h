#ifndef OFXBRONIANMOTION_H
#define OFXBRONIANMOTION_H

#include "ofMain.h"
#include "gtc/noise.hpp"

class ofxBronianMotion
{
public:
    ofxBronianMotion() {}

    ofxBronianMotion( int octaves, float frequency, float frequencyMultiplier = 2.0f ) {
        octaves_ = octaves;
        frequence_ = frequency;
        frequenceMultiplier_ = frequencyMultiplier;
    }

    float get( float x, float y, float z)
    {
        float divider = 2.0f;
        float freq = frequence_;
        float val = 0.0f;
        for( int i = 0; i < octaves_; i++)
        {
            val += ofNoise(glm::vec3(x*freq,y*freq,z*freq)) / divider;
            //val += glm::simplex( glm::vec3(x*res,y*res,z)) / divider;
            divider *= 2.0;
            freq *= frequenceMultiplier_;
        }

        // return a normalized value [0-1]
        //return (val+1.0f)*.5f;
        return val;
    }

private:
    int octaves_ = 2;
    float frequence_ = 0.005f;
    float frequenceMultiplier_ = 2.0f;
};

#endif // OFXBRONIANMOTION_H
