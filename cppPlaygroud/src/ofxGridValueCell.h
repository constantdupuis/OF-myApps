#ifndef OFXGRIDVALUECELL_H
#define OFXGRIDVALUECELL_H

#include "ofMain.h"

template<class DATA>
class ofxGridValueCell
{
public:
    ofxGridValueCell( int col );

    DATA data_;

    int col_;

};

template<class CELL_DATA, int N>
class ofxGridValueCells
{
public:
    using cell_data_type = CELL_DATA;
    int count = N;
    void init()
    {
        for( int i =0; i < N; i++)
        {
            cells_.push_back( make_shared<ofxGridValueCell<CELL_DATA>>(i) );
        }
    }


    vector<shared_ptr<ofxGridValueCell<CELL_DATA>>> cells_;
};

#endif // OFXGRIDVALUECELL_H
