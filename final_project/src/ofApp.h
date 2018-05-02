#pragma once

#include "ofMain.h"
#include "data.h"
#include "ofxJSON.h"
#include "ofxGrafica.h"
#include "ofxDatGui.h"
#include "time_controller.h"


class ofApp: public ofBaseApp
{
    
private:
    
    std::vector<std::string> ticker_symbols;
    std::vector<ofColor> ticker_colors;
    std::vector<std::vector<Data>> all_stocks;
    
    string ticker_one;
    string ticker_two;
    string current_ticker;
    
    string attribute;
    string current_time_series;
    string current_json_series;
    
    ofColor ticker_one_color;
    ofColor ticker_two_color;
    ofColor current_ticker_color;
    
    long range;
    
    bool should_display;
    bool realtime;
    
    uint tIndex;
    vector<ofxDatGuiTheme*> themes;
    
    ofxGPlot plot;
    ofxDatGui* gui;
    ofImage screenshot;
    
    TimeController time_controller;
    
    
public:
    
    void setup();
    void draw();
    void update();
    
    void initial_values();
    void gui_listeners();
    void fill_ticker_vectors();
    
    bool make_api_request(std::string symbol);
    
    void additional_setup();
    void generate_plot();
    void annotate_plot();
    
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
