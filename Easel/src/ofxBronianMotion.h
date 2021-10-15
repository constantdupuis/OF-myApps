#ifndef OFXBRONIANMOTION_H
#define OFXBRONIANMOTION_H

#include "ofMain.h"
#include "gtc/noise.hpp"

class ofxBronianMotion
{
public:
    ofxBronianMotion() {}

    ofxBronianMotion( int octaves, float resolution ) {
        octaves_ = octaves;
        resolution_ = resolution;
    }

    float get( float x, float y, float z)
    {
        float divider = 2.0f;
        float res = resolution_;
        float val = 0.0f;
        for( int i = 0; i < octaves_; i++)
        {
            val += ofNoise(glm::vec3(x*res,y*res,z)) / divider;
            //val += glm::simplex( glm::vec3(x*res,y*res,z*res)) / divider;
            divider *= 2.0;
            res *= 2.0f;
        }

        // return a normalized value [0-1]
        //return (val+1.0f)*.5f;
        return val;
    }

private:
    int octaves_ = 2;
    float resolution_ = 0.005f;
};

#endif // OFXBRONIANMOTION_H
