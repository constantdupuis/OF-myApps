#ifndef OFXBRONIANMOTION_H
#define OFXBRONIANMOTION_H

#include "ofMain.h"

class ofxBronianMotion
{
public:
    //ofxBronianMotion() {}

    ofxBronianMotion( int octaves = 2, float frequency = 0.005f, float frequencyMultiplier = 2.0f ) {
        octaves_ = octaves;
        frequency_ = frequency;
        frequencyMultiplier_ = frequencyMultiplier;
    }

    float get( float x, float y, float z)
    {
        float divider = 2.0f;
        float freq = frequency_;
        float val = 0.0f;
        for( int i = 0; i < octaves_; i++)
        {
            val += ofNoise(glm::vec3(x*freq,y*freq,z*freq)) / divider;
            divider *= 2.0;
            freq *= frequencyMultiplier_;
        }

        return val;
    }

    int setOctavesNbr( int octaves_nbr)
    {
        int prev = octaves_;
        octaves_ = octaves_nbr;
        return prev;
    }

    float setFrequency(float frequency)
    {
        float prev = frequency_;
        frequency_ = frequency;
        return prev;
    }

    float setFrequencyMultiplier( float freq_multiplier)
    {
        float prev = frequencyMultiplier_;
        frequencyMultiplier_ = freq_multiplier;
        return prev;
    }

private:
    int octaves_ = 2;
    float frequency_ = 0.005f;
    float frequencyMultiplier_ = 2.0f;
};

#endif // OFXBRONIANMOTION_H
