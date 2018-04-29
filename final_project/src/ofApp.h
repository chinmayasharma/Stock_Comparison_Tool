#pragma once

#include "ofMain.h"
#include "data.h"
#include "ofxJSON.h"
#include "ofxGrafica.h"
#include "ofxDatGui.h"


class ofApp: public ofBaseApp, ofThread
{
public:
    
    void setup();
    void draw();
    void update();

    void make_api_request(std::string symbol);
    void parse();
    void generate_comparison_plot();
    void generate_display_plot();
    
    ofxJSONElement json;
    int json_values;
    int current_json_values;
    string ticker_one;
    string ticker_two;
    string current_ticker;
    
    string attribute;
    
    string current_time_series;
    string current_json_series;
    
    std::vector<std::vector<Data>> all_stocks;
    std::vector<Data> stocks;
    
    int range;
    
    ofColor ticker_one_color;
    ofColor ticker_two_color;
    ofColor current_ticker_color;
    
    bool parsing_successful;
    bool should_compare;
    bool should_display;
    
    bool realtime;
    
    uint tIndex;
    vector<ofxDatGuiTheme*> themes;
    
    ofxGPlot plot;
    ofxDatGui* gui;
    ofTimer timer;
    
    bool mFullscreen;
    void refreshWindow();
    void toggleFullscreen();
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onToggleEvent(ofxDatGuiToggleEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    
};
