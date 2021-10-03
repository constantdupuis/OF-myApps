#include "ofxGridValueCell.h"

template<class DATA>
ofxGridValueCell<DATA>::ofxGridValueCell( int col)
{
    col_ = col;
}

//template<class CELL_DATA, int N>
//void ofxGridValueCells<CELL_DATA, N>::init()
//{
//    for( int i =0; i < N; i++)
//    {
//        cells_.push_back( make_shared<ofxGridValueCell<CELL_DATAF>>(i) );
//    }
//}
