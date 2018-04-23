#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxGrafica.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();
    void user_input();
    void make_api_request(std::string symbol);
    void parse();
    
    ofxJSONElement json;
    ofxGPlot plot;
    
};
