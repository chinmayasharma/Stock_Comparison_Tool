#pragma once

#include "ofMain.h"
#include "data.h"
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
    void generate_plot(int range, std::vector<std::vector<Data>> stock_data);

    ofxJSONElement json;
    std::vector<ofxGPlot> all_plots;
    
    std::vector<string> ticker_symbols;
    std::vector<std::vector<Data>> all_stocks;
    std::vector<Data> stocks;
    
    ofxGPlot plot;
    ofxGPlot plot_two;

};
