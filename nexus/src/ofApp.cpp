
#include "ofApp.h"
#include "data.h"
#include "utility.h"
#include "time_controller.h"
#include "constants.h"

using std::string;
using std::transform;
using std::stod;
using std::cout;
using std::endl;

/**
 * Sets initial values for variables.
 */
void ofApp::initial_values()    {
    ticker_one_color = default_color_one;
    ticker_two_color = default_color_two;
    
    range = default_range;
    current_time_series = daily_series;
}

/**
 * GUI listener calls.
 */
void ofApp::gui_listeners() {
    
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onToggleEvent(this, &ofApp::onToggleEvent);
    
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->onTextInputEvent(this, &ofApp::onTextInputEvent);
    
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
}


/**
 * Sets up GUI and initial state of variables.
 */
void ofApp::setup(){
    
    initial_values();
    
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
    
    // display button
    gui->addButton(display_button_label);
    gui->addBreak();
    
    // misc. utilities
    gui->addButton("screenshot");
    gui->addToggle("toggle fullscreen", false);
    gui->addButton(exit_button_label);
    
    // header to drag the gui and reposition GUI
    gui->addHeader(":: drag me to reposition ::");
    
    // footer allows you to expand and collapse GUI
    gui->addFooter();
    gui->setWidth(300);
    // once the gui has been assembled, register callbacks to listen for component specific events //
    
    // sets all GUI listeners
    gui_listeners();
    
    themes = {  new ofxDatGuiTheme(true)};
    tIndex = 0;
    
    mFullscreen = false;
    refreshWindow();
}

/**
 * Draws plot.
 */
void ofApp::draw()
{
    plot.defaultDraw();
}


/**
 * Sets up variable values necessary for update.
 */
void ofApp::additional_setup()  {
    
    ofxGPlot new_plot;
    plot = new_plot;
    all_stocks.clear();
    
    if(realtime)    {
        current_time_series = intra_day_series;
        current_json_series = json_time_series_intraday_label;
        range = max_size;
    }
    else{
        current_time_series = daily_series;
        current_json_series = json_time_series_daily_label;
    }
}

/**
 * Updates Plot depending on existing conditions.
 */
void ofApp::update() {
    
    if((ticker_symbols.size() == 2) && should_display)   {
        additional_setup();
        
        if(make_api_request(ticker_symbols[0]))    {
            if(make_api_request(ticker_symbols[1]))    {
                generate_plot();
            }
        }
    }
    
    if ((ticker_symbols.size() == 1) && should_display) {
        additional_setup();
        
        if(make_api_request(current_ticker))    {
            generate_plot();
        }
    }
    should_display = false;

    if (realtime)   {
        if(time_controller.should_refresh()){
        should_display = true;
        }
    }
    
}

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
        //pushes stock vector to a 2D vector
        all_stocks.push_back(parse(json, current_json_series));
        json.clear();
        
    } else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
    }
    return !json.getRawString().empty();
}

/**
 * Generates points to be plotted and annotates plot.
 */
void ofApp::generate_plot() {
    
    // Prepare the points for the plot
    std::vector<std::vector<ofxGPoint>> all_points;
    
    std::vector<ofxGPoint> points;
    
    all_points.push_back(points);
    all_points.push_back(points);
    
    for (int i = 0; i < all_stocks.size(); i++)  {
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
    // Add points to the plot and sets color
    for (int i = 0; i < all_stocks.size(); i++)   {
        
        plot.addLayer(ticker_symbols[i], all_points[i]);
        plot.getLayer(ticker_symbols[i]).setPointColor(ticker_colors[i]);
    }
    // annotates plot
    annotate_plot();
}

/**
 * Annotates plot, setting size and axes.
 */
void ofApp::annotate_plot() {
    
    plot.setPos(50, 50);
    
    
    // Set the plot title and the axis labels
    if (ticker_symbols.size() > 1) {
        plot.setTitleText("Comparison Chart:   " +ticker_symbols[0]+ "   VS   " +ticker_symbols[1]);
    }
    else    {
        plot.setTitleText("Display Chart:   " +ticker_symbols[0]);
        
    }
    if (realtime)   {
        plot.getXAxis().setAxisLabelText("Time Period:   (0 - " + std::to_string(range) + " ) Most Recent Points");
        
    }
    else {
        plot.getXAxis().setAxisLabelText("Time Period:   (0 - " + std::to_string(range) + " ) Days");
    }
    
    // Set the plot position on the screen
    plot.getYAxis().setAxisLabelText("Attribute:   " + attribute);
    
    plot.setDim(550,550);
    plot.activateZooming(1.1, OF_MOUSE_BUTTON_LEFT, OF_MOUSE_BUTTON_LEFT);
    plot.setFontsMakeContours(true);
}

/**
 * Handles button press events.
 */
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    ticker_symbols.clear();
    ticker_colors.clear();
    
    // if DISPLAY button was pressed
    if (e.target->is(display_button_label)) {

        // ensures that necessary values are selected
        if (!ticker_one.empty() && !ticker_two.empty() && !attribute.empty()) {
            time_controller.setup(0);
            fill_ticker_vectors();
            should_display = true;
        }
        
        // ensures only one text input was filled
        if (!ticker_one.empty() && ticker_two.empty() && !attribute.empty()) {
            time_controller.setup(0);
            ticker_symbols.push_back(ticker_one);
            ticker_colors.push_back(ticker_one_color);
            should_display = true;
        }
        
        // ensures only one text input was filled
        if (ticker_one.empty() && !ticker_two.empty() && !attribute.empty()) {
            time_controller.setup(0);
            ticker_symbols.push_back(ticker_two);
            ticker_colors.push_back(ticker_two_color);
            should_display = true;
        }
    }
    
    // if SCREENSHOT button was pressed
    if (e.target->is("screenshot")) {
        
        screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        string fileName = "Screenshot: " + ofGetTimestampString() + ".png";
        screenshot.save(fileName);
    }
   
    // if QUIT APPLICATION button was pressed
    if (e.target->is(exit_button_label)) {
        
        ofExit();
    }
    
}

/**
 * Sets up ticker vectors.
 */
void ofApp::fill_ticker_vectors()   {
    
    ticker_symbols.push_back(ticker_one);
    ticker_symbols.push_back(ticker_two);
    
    ticker_colors.push_back(ticker_one_color);
    ticker_colors.push_back(ticker_two_color);
}

/**
 * Handles Toggle Events.
 */
void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
    // if REALTIME toggle was clicked
    if (e.target->is("realtime")) {
        realtime = !realtime;
    }
    
    // if TOGGLE FULLSCREEN was clicked
    if (e.target->is("toggle fullscreen")) {
        mFullscreen = !mFullscreen;
        gui->getToggle("toggle fullscreen")->setChecked(mFullscreen);
        refreshWindow();
    }
}

/**
 * Handles Slider Events.
 */
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    // if RANGE slider was moved
    if (e.target->is(range_slider_label)) {
        range = (int)(e.scale*100);
    }
}

/**
 * Handles Text Input Field Entries.
 */
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    // if LABEL #1 was edited
    if (e.target->is(ticker_one_label)) {
        
        ticker_one = e.target->getText();
        std::transform(ticker_one.begin(), ticker_one.end(), ticker_one.begin(), ::toupper);
        
        if (!ticker_one.empty())    {
            current_ticker = ticker_one;
        }
    }
    
    // if LABEL #2 was edited
    if (e.target->is(ticker_two_label)) {
        ticker_two = e.target->getText();
        std::transform(ticker_two.begin(), ticker_two.end(), ticker_two.begin(), ::toupper);
        
        if (!ticker_two.empty())    {
            current_ticker = ticker_two;
        }
    }
}

/**
 * Handles Drop Down Menu Events.
 */
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    attribute = e.target->getLabel();
}

/**
 * Handles Color Picker Events.
 */
void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)    {
    
    // if COLOR #1 is set
    if (e.target->is(color_picker_one_label)) {
        ticker_one_color = e.color;
    }
    
    // if COLOR #2 is set
    if (e.target->is(color_picker_two_label)){
        ticker_two_color = e.color;
    }
}

/**
 * Refreshed Window.
 */
void ofApp::refreshWindow()
{
    ofSetFullscreen(mFullscreen);
    if (!mFullscreen) {
        ofSetWindowShape(1024, 768);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1024/2), 0);
    }
}
