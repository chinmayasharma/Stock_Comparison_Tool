#pragma once

#include "ofMain.h"
#include "data.h"
#include "ofxJSON.h"
#include "ofxGrafica.h"
#include "ofxDatGui.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();
    void user_input();
    void make_api_request(std::string symbol);
    void parse();
    void generate_plot(std::vector<std::vector<Data>> stock_data);

    ofxJSONElement json;
    std::vector<ofxGPlot> all_plots;
    
    std::vector<string> ticker_symbols;
    string ticker_one;
    string ticker_two;
    std::vector<std::vector<Data>> all_stocks;
    std::vector<Data> stocks;
    
    ofxGPlot plot;
    ofxGPlot plot_two;

    int range;
    int attribute_index;
    string comparison_attribute;
    
    void update();
    
    ofxDatGui* gui;
    bool mFullscreen;
    void refreshWindow();
    void toggleFullscreen();
    
    void keyPressed(int key);
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onToggleEvent(ofxDatGuiToggleEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
    uint tIndex;
    vector<ofxDatGuiTheme*> themes;
    

    
};
