#ifndef CODARTDOCUMENT_H
#define CODARTDOCUMENT_H

#include "ofMain.h"
#include "ofxXmlSettings.h"

struct CodArtDocument{
    string name = "";
    string filename = "";
    ofxXmlSettings settings;
    bool loaded = false;
    bool modified = false;

};

#endif // CODARTDOCUMENT_H
