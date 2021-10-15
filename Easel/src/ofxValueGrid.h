#ifndef OFXVALUEGRID_H
#define OFXVALUEGRID_H

#include "ofMain.h"

class ofxValueGridCell
{
    public:

        ofxValueGridCell(int col, int row,
                         float left, float top,
                         float width, float height,
                         float point_x, float point_y,
                         float norm_left, float norm_top,
                         float norm_width, float norm_height,
                         float norm_point_x, float norm_point_y) {
            col_ = col;
            row_ = row;
            left_ = left;
            top_ = top;
            width_ = width;
            height_ = height;
            point_x_ = point_x;
            point_y_ = point_y;
            norm_left_ = norm_left;
            norm_top_ = norm_top;
            norm_width_ = norm_width;
            norm_heigth_ = norm_width;
            norm_point_x_ = norm_point_x;
            norm_point_y_ = norm_point_y;

        }

        const int col() { return col_;}
        const int row() { return row_;}
        const float left() {return left_;}
        const float top() {return top_;}
        const float width() { return width_;}
        const float height() { return height_;}
        const float pointX() { return point_x_;}
        const float pointY() {return point_y_;}
        const float normLeft() {return norm_left_;}
        const float normTop() {return norm_top_;}
        const float normWidth() {return norm_width_;}
        const float normHeight() {return norm_heigth_;}
        const float normPointX() { return norm_point_x_;}
        const float normPointY() { return norm_point_y_;}

    private:
        int col_;
        int row_;
        float left_;
        float top_;
        float width_;
        float height_;
        float point_x_;
        float point_y_;
        float norm_left_;
        float norm_top_;
        float norm_width_;
        float norm_heigth_;
        float norm_point_x_;
        float norm_point_y_;
};

template<class CellT>
class ofxValueGrid
{
public:
    ofxValueGrid( int cols, int rows, 
                  float width, float height,
                  glm::vec2 posInCell = glm::vec2(0.5f, 0.5f))
    {
        cols_ = cols;
        rows_ = rows;
        width_ = width;
        height_ = height;
        posInCell_ = posInCell;

        float cellw = width_ / (cols_ + 1);
        float cellh = height_ / (rows_ + 1);

        for( int c = 0; c <= cols_; c++)
        {
            for( int r = 0; r <= rows_; r++)
                cells_.push_back( make_shared<ofxValueGridCell>( // row, col
                                                      c, r,
                                                      // cell top left
                                                      cellw * c, cellh * r,
                                                      // cell width and height
                                                      cellw, cellh,
                                                      // point x and y
                                                      (cellw * c) + (cellw * posInCell_.x), (cellh * r) + (cellh * posInCell_.y), // point x, y
                                                      // normalized (0-1) cell top and left
                                                      (cellw * c) / width_, (cellh * r) / height_,
                                                      // normalized (0-1) cell width and height
                                                      cellw / width_, cellh / height_,
                                                      // normalized (0-1) point x and y
                                                      ((cellw * c) + (cellw * posInCell_.x)) / width_,
                                                      ((cellh * r) + (cellh * posInCell_.y)) / height_));
        }
    }

    const int cols() {return cols_;}
    const int rows() {return rows_;}
    const float width() {return width_;}
    const float heigth() {return height_;}
    const glm::vec2 posInCell() { return posInCell_;}

    const std::vector<std::shared_ptr<ofxValueGridCell>>& cells() { return cells_;}

private:
    int cols_;
    int rows_;
    float width_;
    float height_;
    glm::vec2 posInCell_;
    std::vector<std::shared_ptr<ofxValueGridCell>> cells_;

};

#endif // OFXVALUEGRID_H
