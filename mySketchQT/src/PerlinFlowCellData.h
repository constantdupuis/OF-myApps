#pragma once

#include "ofMain.h"

class PerlinFlowCellData : public ofxValueGridCell {
    
    ofColor color_;
    float size_;

    PerlinFlowCellData(int col, int row,
        float left, float top,
        float width, float height,
        float point_x, float point_y,
        float norm_left, float norm_right,
        float norm_width, float norm_height,
        float norm_point_x, float norm_point_y) :
        ofxValueGridCell{ col, row, left, top,
                          width, height, point_x, point_y,
                          norm_left, norm_right, norm_width, norm_height,
                          norm_point_x, norm_point_y }
    {
        color_ = ofColor().fromHsb(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(10, 200));
        size_ = ofRandom(15, 65);
    }
};