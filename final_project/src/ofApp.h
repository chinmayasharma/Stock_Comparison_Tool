#pragma once


#include "ofMain.h"
#include "ofxJSON.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();
    void make_api_request(std::string symbol);
    void parse();
    
    ofxJSONElement json;
    
};
