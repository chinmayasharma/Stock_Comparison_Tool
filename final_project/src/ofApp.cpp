#include "ofApp.h"
#include "data.h"
#include "constants.h"

using std::string;
using std::transform;
using std::stod;
using std::cout;
using std::endl;

/**
 * Makes an API request to retrieve data from Alpha Vantage.
 */
void ofApp::make_api_request(string symbol) {
    
    // URL to be parsed
    string url = initial_url_component + "TIME_SERIES_DAILY" + url_symbol_component + symbol+ url_api_key_component;
    
    // Checks if URL was valid
    parsing_successful = json.open(url);
    
    if (parsing_successful)
    {
        ofLogNotice("ofApp::setup") << json.getRawString(true);
        parse();
        json.clear();
        
    } else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
        should_compare = false;
        should_display = false;
    }
}

/**
 * Parses data from website and creates Stock objects.
 */
void ofApp::parse() {
    stocks.clear();
    
    if (should_compare || should_display)   {
        
        // accesses all elements in the JSON array
        for (auto value : json[json_time_series_label])
        {
            string open_value = value[json_open_attribute_label].asString();
            string high_value = value[json_high_attribute_label].asString();
            string low_value = value[json_low_attribute_label].asString();
            string close_value = value[json_close_attribute_label].asString();
            string volume_value = value[json_volume_attribute_label].asString();
            
            Data stock_value(stod(open_value), stod(high_value), stod(low_value), stod(close_value), stod(volume_value));
            stocks.push_back(stock_value);
        }
        
        if (should_compare) {
            all_stocks.push_back(stocks);
            stocks.clear();
        }
    }
}

/**
 *
 */
void ofApp::setup(){
    
    should_compare = false;
    should_display = false;
    
    ticker_one_color = default_color_one;
    ticker_two_color = default_color_two;
    
    range = default_range;
    
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
    gui->addSlider(range_slider_label, 0, 100);
    gui->addBreak();
    
    // compare and display buttons
    gui->addButton(compare_button_label);
    gui->addButton(display_button_label);
    gui->addBreak();
    
    // misc. utilities
    gui->addButton("screenshot");
    gui->addToggle("toggle fullscreen", true);
    
    // header to drag the gui and reposition GUI
    gui->addHeader(":: drag me to reposition ::");
    
    // footer allows you to expand and collapse GUI
    gui->addFooter();
    
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
    //ofBeginSaveScreenAsPDF("screenshot-" + ofGetTimestampString() + ".pdf", false);
    
    plot.defaultDraw();
    
    
}

/**
 *
 */
void ofApp::generate_comparison_plot() {
    
    if (should_compare) {
        // Prepare the points for the plot
        std::vector<ofxGPoint> points1;
        std::vector<ofxGPoint> points2;
        
        // Set the plot title and the axis labels
        plot.setTitleText("Comparison Chart:   " +ticker_one+ "   VS   " +ticker_two);
        plot.getXAxis().setAxisLabelText("Time Period:   (0 - " + std::to_string(range) + " ) Days");
        plot.getYAxis().setAxisLabelText("Comparison Attribute:   " + attribute);
        
        for (int j = 0; j < range; j++) {
            
            switch (data_map[attribute]) {
                case 0:
                    points1.emplace_back(j, all_stocks[0][j].get_open());
                    points2.emplace_back(j, all_stocks[1][j].get_open());
                    break;
                    
                case 1:
                    points1.emplace_back(j, all_stocks[0][j].get_high());
                    points2.emplace_back(j, all_stocks[1][j].get_high());
                    break;
                    
                case 2:
                    points1.emplace_back(j, all_stocks[0][j].get_low());
                    points2.emplace_back(j, all_stocks[1][j].get_low());
                    break;
                    
                case 3:
                    points1.emplace_back(j, all_stocks[0][j].get_close());
                    points2.emplace_back(j, all_stocks[1][j].get_close());
                    break;
                    
                case 4:
                    points1.emplace_back(j, all_stocks[0][j].get_volume());
                    points2.emplace_back(j, all_stocks[1][j].get_volume());
                    break;
            }
        }
        
        // Set the plot position on the screen
        plot.setPos(25, 25);
        
        // Add the points
        plot.addLayer(ticker_one, points1);
        plot.getLayer(ticker_one).setPointColor(ticker_one_color);
        
        plot.addLayer(ticker_two, points2);
        plot.getLayer(ticker_two).setPointColor(ticker_two_color);
        
        plot.setFontsMakeContours(true);
    }
}

/**
 *
 */
void ofApp::generate_display_plot() {
    
    if (should_display) {
        
        // Prepare the points for the plot
        std::vector<ofxGPoint> points1;
        
        // Set the plot title and the axis labels
        plot.setTitleText("Display Chart:   " +current_ticker);
        plot.getXAxis().setAxisLabelText("Time Period:   (0 - " + std::to_string(range) + " ) Days");
        plot.getYAxis().setAxisLabelText("Display Attribute:   " + attribute);
        
        for (int j = 0; j < range; j++) {
            
            switch (data_map[attribute]) {
                case 0:
                    points1.emplace_back(j, stocks[j].get_open());
                    break;
                    
                case 1:
                    points1.emplace_back(j, stocks[j].get_high());
                    break;
                    
                case 2:
                    points1.emplace_back(j, stocks[j].get_low());
                    break;
                    
                case 3:
                    points1.emplace_back(j, stocks[j].get_close());
                    break;
                    
                case 4:
                    points1.emplace_back(j, stocks[j].get_volume());
                    break;
            }
        }
        
        // Set the plot position on the screen
        plot.setPos(25, 25);
        
        // Add the points
        plot.addLayer(current_ticker, points1);
        plot.getLayer(current_ticker).setPointColor(current_ticker_color);
        
        plot.setFontsMakeContours(true);
    }
}


/**
 *
 */
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target->is(compare_button_label)) {
        
        if (!ticker_one.empty() && !ticker_two.empty() && !attribute.empty()) {
            should_compare = true;
        }
    }
    
    if (e.target->is(display_button_label)) {
        
        if (((!ticker_one.empty() && ticker_two.empty()) || (ticker_one.empty() && !ticker_two.empty())) && !attribute.empty()) {
            
            current_ticker_color = ticker_one_color;
            should_display = true;
        }
        
        if (((!ticker_one.empty() && ticker_two.empty()) || (ticker_one.empty() && !ticker_two.empty())) && !attribute.empty()) {
            
            current_ticker_color = ticker_two_color;
            should_display = true;
        }
    }
}

/**
 *
 */
void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
    if (e.target->is("toggle fullscreen")) toggleFullscreen();
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
        
        make_api_request(ticker_one);
        make_api_request(ticker_two);
        generate_comparison_plot();
        
        should_compare = false;
    }
    
    //
    if (should_display) {
        ofxGPlot new_plot;
        plot = new_plot;
        all_stocks.clear();
        
        make_api_request(current_ticker);
        generate_display_plot();
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
