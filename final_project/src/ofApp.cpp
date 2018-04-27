#include "ofApp.h"
#include "data.h"

using std::string;
using std::transform;
using std::stod;
using std::cout;
using std::endl;

/**
 * Makes an API request to retrieve data from Alpha Vantage.
 */
void ofApp::make_api_request(string symbol) {
    
    string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" +symbol+"&apikey=UJP0F3I7MQPJM9WR";
    
    bool parsingSuccessful = json.open(url);
    
    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << json.getRawString(true);
        parse();
        json.clear();
        
    } else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
    }
}

/**
 * Parses data from website and creates Stock objects.
 */
void ofApp::parse() {
    
    // accesses all elements in the JSON array
    for (auto value : json["Time Series (Daily)"])
    {
        string open_value = value["1. open"].asString();
        string high_value = value["2. high"].asString();
        string low_value = value["3. low"].asString();
        string close_value = value["4. close"].asString();
        string volume_value = value["5. volume"].asString();
        
        Data stock_value = *new Data(stod(open_value), stod(high_value), stod(low_value), stod(close_value), stod(volume_value));
        
        stocks.push_back(stock_value);
    }
    all_stocks.push_back(stocks);
}

/**
 *
 */
void ofApp::setup(){
    
    // instantiate and position the gui //
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    
    // add some components //
    gui->addTextInput("** ticker #1", "# open frameworks #");
    gui->addTextInput("** ticker #2", "# open frameworks #");
    gui->addBreak();
    // add a dropdown menu //
    vector<string> opts = {"open", "low", "high", "close", "volume"};
    gui->addDropdown("select attribute", opts);
    gui->addSlider("** range", 0, 100);
    gui->addBreak();
    
    // and a couple of simple buttons //
    gui->addButton("compare");
    gui->addToggle("toggle fullscreen", true);
    
    // adding the optional header allows you to drag the gui around //
    gui->addHeader(":: drag me to reposition ::");
    
    // adding the optional footer allows you to collapse/expand the gui //
    gui->addFooter();
    
    // once the gui has been assembled, register callbacks to listen for component specific events //
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onToggleEvent(this, &ofApp::onToggleEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->onTextInputEvent(this, &ofApp::onTextInputEvent);
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    
    themes = {  new ofxDatGuiTheme(true)};
    tIndex = 0;
    
    // launch the app //
    mFullscreen = true;
    refreshWindow();
    
    //user_input();
    
    //generate_plot(30, all_stocks);
}

/**
 *
 */
void ofApp::draw()
{
    //ofBeginSaveScreenAsPDF("screenshot-" + ofGetTimestampString() + ".pdf", false);
    //for(int i =0; i < 2; i++)   {
    //  if (i == 0) {
    //        all_plots[0].defaultDraw();
    //}
    //else{
    //      //all_plots[i].defaultDraw();
    //}
    //}
    
    //ofEndSaveScreenAsPDF();
}

/**
 *
 */
void ofApp::generate_plot(std::vector<std::vector<Data>> stock_data) {
    
    // Prepare the points for the plot
    std::vector<ofxGPoint> points;
    
    for (int i = 0; i < 2; i++)  {
        
        // Set the plot title and the axis labels
        if (i == 0)  {
            plot.setTitleText("A very simple example");
            plot.getXAxis().setAxisLabelText("x axis");
            plot.getYAxis().setAxisLabelText("y axis");
        }
        
        for (int j = 0; j < range; j++) {
            
            switch (data_map[comparison_attribute]) {
                case 0:
                    points.emplace_back(j, stock_data[i][j].get_open());
                    break;
                case 1:
                    points.emplace_back(j, stock_data[i][j].get_high());
                    break;
                case 2:
                    points.emplace_back(j, stock_data[i][j].get_low());
                    break;
                case 3:
                    points.emplace_back(j, stock_data[i][j].get_close());
                    break;
                case 4:
                    points.emplace_back(j, stock_data[i][j].get_volume());
                    break;
            }
            
        }
        // Set the plot position on the screen
        plot.setPos(25, 25);
        
        // Add the points
        plot.setPoints(points);
        plot.setFontsMakeContours(true);
        all_plots.push_back(plot);
    }
}

/**
 *
 */
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "onButtonEvent: " << e.target->getLabel() << endl;
}

/**
 *
 */
void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
    if (e.target->is("toggle fullscreen")) toggleFullscreen();
    cout << "onToggleEvent: " << e.target->getLabel() << " " << e.checked << endl;
}

/**
 *
 */
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    if (e.target->is("** range")) {
        range = (int)e.scale;
        cout << "reached" << endl;
    }
}

/**
 *
 */
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    if (e.target->is("** ticker #1")) {
        ticker_one = e.target->getText();
        cout << "reached" << endl;
    }
    if (e.target->is("** ticker #2")) {
        ticker_two = e.target->getText();
        cout << "reached" << endl;
    }
}

/**
 *
 */
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    comparison_attribute = e.target->getLabel();
    
    cout << "onDropdownEvent: " << e.target->getLabel() << " Selected" << endl;
}

/**
 *
 */
void ofApp::update() {
    //make_api_request(ticker_symbols[0]);
    //make_api_request(ticker_symbols[1]);
}

/**
 *
 */
void ofApp::keyPressed(int key)
{
    if (key == 'f') {
        toggleFullscreen();
    }   else if (key == 32){
        tIndex = tIndex < themes.size()-1 ? tIndex+1 : 0;
        gui->setTheme(themes[tIndex]);
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
        ofSetWindowShape(1920, 1400);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1920/2), 0);
    }
}
