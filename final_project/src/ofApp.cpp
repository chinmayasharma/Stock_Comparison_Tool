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
        
        Data stock_value(stod(open_value), stod(high_value), stod(low_value), stod(close_value), stod(volume_value));
        
        stocks.push_back(stock_value);
    }
    all_stocks.push_back(stocks);
    stocks.clear();
}

/**
 *
 */
void ofApp::setup(){
    
    should_compare = false;
    range = 50;
    
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
    gui->addButton("display");
    gui->addBreak();
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
    mFullscreen = false;
    refreshWindow();
    
}

/**
 *
 */
void ofApp::draw()
{
    //ofBeginSaveScreenAsPDF("screenshot-" + ofGetTimestampString() + ".pdf", false);
    //if (should_update) {
    //graph.draw();
    //}
    //if (should_update)  {
    plot.defaultDraw();
    
    //ofEndSaveScreenAsPDF();
    //all_stocks.clear();
    //should_update = false;
    //}
}

/**
 *
 */
void ofApp::generate_comparison_plot(std::vector<std::vector<Data>> stock_data) {
    // Prepare the points for the plot
    std::vector<ofxGPoint> points1;
    std::vector<ofxGPoint> points2;
    
    // Set the plot title and the axis labels
    plot.setTitleText("Comparison Chart:   " +ticker_one+ "   VS   " +ticker_two);
    plot.getXAxis().setAxisLabelText("Time Period:   (0 - " + std::to_string(range) + " ) Days");
    plot.getYAxis().setAxisLabelText("Comparison Attribute:   " + attribute);
    
    for (int j = 0; j < range; j++) {
        vector<float> values;
        
        
        //for (int i = 0; i < 2; i++) {
        switch (data_map[attribute]) {
            case 0:
                points1.emplace_back(j, stock_data[0][j].get_open());
                points2.emplace_back(j, stock_data[1][j].get_open());
                break;
                
            case 1:
                points1.emplace_back(j, stock_data[0][j].get_high());
                points2.emplace_back(j, stock_data[1][j].get_high());
                break;
                
            case 2:
                points1.emplace_back(j, stock_data[0][j].get_low());
                points2.emplace_back(j, stock_data[1][j].get_low());
                break;
                
            case 3:
                points1.emplace_back(j, stock_data[0][j].get_close());
                points2.emplace_back(j, stock_data[1][j].get_close());
                break;
                
            case 4:
                points1.emplace_back(j, stock_data[0][j].get_volume());
                points2.emplace_back(j, stock_data[1][j].get_volume());
                break;
        }
    }
    
    // Set the plot position on the screen
    plot.setPos(25, 25);
    
    // Add the points
    plot.addLayer(ticker_one, points1);
    plot.addLayer(ticker_two, points2);
    
    plot.setFontsMakeContours(true);
    
}

/**
 *
 */
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target->is("compare")) {
        
        if (!ticker_one.empty() && !ticker_two.empty() && !attribute.empty()) {
            should_compare = true;
        }
    }
    
    if (e.target->is("display")) {
        
        if (((!ticker_one.empty() && ticker_two.empty()) || (ticker_one.empty() && !ticker_two.empty())) && !attribute.empty()) {
            should_display = true;
        }
    }
    
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
        
        range = (int)(e.scale * 100);
        cout << "reached " << range << endl;
    }
}

/**
 *
 */
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    if (e.target->is("** ticker #1")) {
        ticker_one = e.target->getText();
        std::transform(ticker_one.begin(), ticker_one.end(), ticker_one.begin(), ::toupper);
        
        cout << ticker_one << endl;
    }
    if (e.target->is("** ticker #2")) {
        ticker_two = e.target->getText();
        std::transform(ticker_two.begin(), ticker_two.end(), ticker_two.begin(), ::toupper);
        
        cout << ticker_two << endl;
    }
}

/**
 *
 */
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    attribute = e.target->getLabel();
    
    cout << "onDropdownEvent: " << e.target->getLabel() << " Selected" << endl;
}

/**
 *
 */
void ofApp::update() {
    
    if(should_compare)   {
        ofxGPlot new_plot;
        plot = new_plot;
        all_stocks.clear();
        make_api_request(ticker_one);
        make_api_request(ticker_two);
        generate_comparison_plot(all_stocks);
        should_compare = false;
    }
    
    
}

/**
 *
 */
void ofApp::keyPressed(int key)
{
    if (key == 32){
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
        ofSetWindowShape(1024, 768);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1024/2), 0);
    }
}
