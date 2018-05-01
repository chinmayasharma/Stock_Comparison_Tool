#include "ofApp.h"
#include "data.h"
#include "utility.h"
#include "constants.h"

using std::string;
using std::transform;
using std::stod;
using std::cout;
using std::endl;

/**
 * Makes an API request to retrieve data from Alpha Vantage.
 */
bool ofApp::make_api_request(string symbol) {
    ofxJSONElement json;
    // URL to be parsed
    string url = generate_url(realtime, current_time_series, symbol);
    
    // Checks if URL was valid
    if (json.open(url))
    {
        ofLogNotice("ofApp::setup") << json.getRawString(true);
        all_stocks.push_back(parse(json, current_json_series));
        json.clear();
        
    } else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
    }
    return !json.getRawString().empty();
}

/**
 *
 */
void ofApp::setup(){
    
    ticker_one_color = default_color_one;
    ticker_two_color = default_color_two;
    
    range = default_range;
    current_time_series = daily_series;
    
    // instantiate and position the gui //
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    
    // input and color fields for ticker #1
    gui->addTextInput(ticker_one_label, ticker_one_example);
    gui->addColorPicker(color_picker_one_label, default_color_one);
    gui->addBreak();
    
    // input and color fields for ticker #2
    gui->addTextInput(ticker_two_label, ticker_two_example);
    gui->addColorPicker(color_picker_two_label, default_color_two);
    gui->addBreak();
    
    // drop down menu for comparison attributes
    gui->addDropdown(drop_down_attributes_label, attribute_options);
    
    // slider for range of time period
    gui->addToggle("realtime", false);
    gui->addSlider(range_slider_label, 0, 100);
    gui->addBreak();
    
    // compare and display buttons
    gui->addButton(compare_button_label);
    gui->addButton(display_button_label);
    gui->addBreak();
    
    // misc. utilities
    gui->addButton("screenshot");
    gui->addToggle("toggle fullscreen", false);
    
    // header to drag the gui and reposition GUI
    gui->addHeader(":: drag me to reposition ::");
    
    // footer allows you to expand and collapse GUI
    gui->addFooter();
    gui->setWidth(300);
    // once the gui has been assembled, register callbacks to listen for component specific events //
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onToggleEvent(this, &ofApp::onToggleEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->onTextInputEvent(this, &ofApp::onTextInputEvent);
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
    
    themes = {  new ofxDatGuiTheme(true)};
    tIndex = 0;
    
    mFullscreen = false;
    refreshWindow();
}

/**
 *
 */
void ofApp::draw()
{
    plot.defaultDraw();
}

/**
 *
 */
void ofApp::generate_plot() {
    
    // Prepare the points for the plot
    std::vector<std::vector<ofxGPoint>> all_points;
    
    std::vector<ofxGPoint> points1;
    
    all_points.push_back(points1);
    all_points.push_back(points1);
    
    // Set the plot title and the axis labels
    plot.setTitleText("Comparison Chart:   " +ticker_one+ "   VS   " +ticker_two);
    plot.getXAxis().setAxisLabelText("Time Period:   (0 - " + std::to_string(range) + " ) Days");
    plot.getYAxis().setAxisLabelText("Comparison Attribute:   " + attribute);
    
    for(int i = 0; i < all_stocks.size(); i++)  {
        for (int j = 0; j < range; j++) {
            
            switch (data_map[attribute]) {
                case 0:
                    all_points[i].emplace_back(j, all_stocks[i][j].get_open());
                    break;
                    
                case 1:
                    all_points[i].emplace_back(j, all_stocks[i][j].get_high());
                    break;
                    
                case 2:
                    all_points[i].emplace_back(j, all_stocks[i][j].get_low());
                    break;
                    
                case 3:
                    all_points[i].emplace_back(j, all_stocks[i][j].get_close());
                    break;
                    
                case 4:
                    all_points[i].emplace_back(j, all_stocks[i][j].get_volume());
                    break;
            }
        }
    }
    
    // Set the plot position on the screen
    plot.setPos(50, 50);
    
    // Add the points
    for(int i = 0; i < all_stocks.size();i++)   {
        plot.addLayer(ticker_symbols[i], all_points[i]);
        plot.getLayer(ticker_symbols[i]).setPointColor(ticker_colors[i]);
    }
    
    plot.setDim(550,550);
    plot.activateZooming(1.1, OF_MOUSE_BUTTON_LEFT, OF_MOUSE_BUTTON_LEFT);
    plot.setFontsMakeContours(true);
}


/**
 *
 */
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    ticker_symbols.clear();
    
    if (e.target->is(compare_button_label)) {
        //timer.~ofTimer();
        if (!ticker_one.empty() && !ticker_two.empty() && !attribute.empty()) {
            ticker_symbols.push_back(ticker_one);
            ticker_symbols.push_back(ticker_two);
            ticker_colors.push_back(ticker_one_color);
            ticker_colors.push_back(ticker_two_color);
            
            should_compare = true;
        }
    }
    
    if (e.target->is(display_button_label)) {
        //timer.~ofTimer();
        if (!ticker_one.empty() && ticker_two.empty() && !attribute.empty()) {
            
            current_ticker_color = ticker_one_color;
            should_display = true;
        }
        
        if (ticker_one.empty() && !ticker_two.empty() && !attribute.empty()) {
            
            current_ticker_color = ticker_two_color;
            should_display = true;
        }
    }
    
    if (e.target->is("screenshot")) {
        ofBeginSaveScreenAsPDF("screenshot-" + ofGetTimestampString() + ".pdf");
        ofEndSaveScreenAsPDF();
    }
    
}

/**
 *
 */
void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
    if (e.target->is("realtime")) {
        realtime = !realtime;
    }
    
    if (e.target->is("toggle fullscreen")) {
        toggleFullscreen();
    }
}

/**
 *
 */
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    if (e.target->is(range_slider_label)) {
        range = (int)(e.scale*100);
    }
}

/**
 *
 */
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    //
    if (e.target->is(ticker_one_label)) {
        ticker_one = e.target->getText();
        std::transform(ticker_one.begin(), ticker_one.end(), ticker_one.begin(), ::toupper);
        
        if (!ticker_one.empty())    {
            current_ticker = ticker_one;
        }
        
    }
    
    //
    if (e.target->is(ticker_two_label)) {
        ticker_two = e.target->getText();
        std::transform(ticker_two.begin(), ticker_two.end(), ticker_two.begin(), ::toupper);
        
        if (!ticker_two.empty())    {
            current_ticker = ticker_two;
        }
    }
}

/**
 *
 */
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    attribute = e.target->getLabel();
}

/**
 *
 */
void ofApp::update() {
    
    //
    if(should_compare)   {
        ofxGPlot new_plot;
        plot = new_plot;
        all_stocks.clear();
        
        additional_setup();
        
        if(make_api_request(ticker_one))    {
            if(make_api_request(ticker_two))    {
                generate_plot();
            }
        }
        should_compare = false;
        
    }
    
    //
    if (should_display) {
        ofxGPlot new_plot;
        plot = new_plot;
        all_stocks.clear();
        
        additional_setup();
       
        if(make_api_request(current_ticker))    {
            generate_plot();
        }
        
        should_display = false;
    }
}

/**
 *
 */
void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)    {
    if (e.target->is(color_picker_one_label)) {
        ticker_one_color = e.color;
    }
    
    if (e.target->is(color_picker_two_label)){
        ticker_two_color = e.color;
    }
}

/**
 *
 */
void ofApp::toggleFullscreen()
{
    mFullscreen = !mFullscreen;
    gui->getToggle("toggle fullscreen")->setChecked(mFullscreen);
    refreshWindow();
}

/**
 *
 */
void ofApp::refreshWindow()
{
    ofSetFullscreen(mFullscreen);
    if (!mFullscreen) {
        ofSetWindowShape(1024, 768);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1024/2), 0);
    }
}

void ofApp::additional_setup()  {
    
    if(realtime)    {
        current_time_series = intra_day_series;
        current_json_series = json_time_series_intraday_label;
    }
    else{
        current_time_series = daily_series;
        current_json_series = json_time_series_daily_label;
    }
}
