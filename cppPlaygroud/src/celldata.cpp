#include "celldata.h"

CellData::CellData()
{
    color_ = ofColor().fromHsb( ofRandom(255), ofRandom(255), ofRandom(255));
}
