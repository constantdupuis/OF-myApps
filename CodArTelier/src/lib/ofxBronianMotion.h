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
        float amplitude = 0.5f;
        float freq = frequency_;
        float val = 0.0f;

        if( octaves_ == 1) amplitude = 1.0f;

        for( int i = 0; i < octaves_; i++)
        {
            val += ofNoise(glm::vec3(x*freq,y*freq,z*freq)) * amplitude;
            amplitude *= 0.5f;
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
    int& octavesNbr()
    {
        return octaves_;
    }

    float setFrequency(float frequency)
    {
        float prev = frequency_;
        frequency_ = frequency;
        return prev;
    }

    float& frequency()
    {
        return frequency_;
    }

    float setFrequencyMultiplier( float freq_multiplier)
    {
        float prev = frequencyMultiplier_;
        frequencyMultiplier_ = freq_multiplier;
        return prev;
    }

    float& frequencyMultiplier()
    {
        return frequencyMultiplier_;
    }

private:
    int octaves_ = 2;
    float frequency_ = 0.005f;
    float frequencyMultiplier_ = 2.0f;
};

#endif // OFXBRONIANMOTION_H
