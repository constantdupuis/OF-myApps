#ifndef CELLWITHSIZEANDCOLOR_H
#define CELLWITHSIZEANDCOLOR_H

#include "ofxValueGrid.h"

class CellWithSizeAndColor : public ofxValueGridCell
{
public:
    ofColor color_;
    float size_;
    CellWithSizeAndColor(int col, int row, float mapx, float mapy) : ofxValueGridCell {col, row, mapx, mapy}
    {
        color_ = ofColor().fromHsb(ofRandom(255),ofRandom(255),ofRandom(255), ofRandom(10,200));
        size_ = ofRandom(15,65);
    }
};

#endif // CELLWITHSIZEANDCOLOR_H
