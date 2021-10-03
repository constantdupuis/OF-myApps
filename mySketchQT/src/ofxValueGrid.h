#ifndef OFXVALUEGRID_H
#define OFXVALUEGRID_H

#include "ofMain.h"

class ofxValueGridCell
{
    public:
        int col_;
        int row_;
        float mapx_;
        float mapy_;

        ofxValueGridCell(int col, int row, float mapx, float mapy) {
            col_ = col;
            row_ = row;
            mapx_ = mapx;
            mapy_ = mapy;
        }
    private:
};

template<class CellT>
class ofxValueGrid
{
public:
    ofxValueGrid( int cols, int rows, float mapx, float mapy,
                   glm::vec2 posInCell)
    {
        cols_ = cols;
        rows_ = rows;
        mapx_ = mapx;
        mapy_ = mapy;
        posInCell_ = posInCell;

        float cellw = mapx_ / (cols_ + 1);
        float cellh = mapy_ / (rows_ + 1);

        for( int c = 0; c <= cols_; c++)
        {
            for( int r = 0; r <= rows_; r++)
                cells_.push_back( make_shared<CellT>( c, r,
                    (cellw * c) + (cellw * posInCell_.x),
                    (cellh * r) + (cellh * posInCell_.y) ));
        }
    }

    void init()
    {
        for( int i = 0; i < cols_; i++)
        {
            cells_.push_back( make_shared<CellT>(i, i, i, i) );
        }
    }
    //ofxValueGrid2() {}

    int cols_;
    int rows_;
    float mapx_;
    float mapy_;
    glm::vec2 posInCell_;
    std::vector<std::shared_ptr<CellT>> cells_;

    const std::vector<std::shared_ptr<CellT>>& cells() { return cells_;}
};

#endif // OFXVALUEGRID_H
