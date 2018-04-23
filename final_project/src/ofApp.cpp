#include "ofApp.h"
#include "data.h"

using std::string;
using std::transform;
using std::stol;
using std::stod;

std::vector<string> ticker_symbols;
std::vector<Data> stocks;

/**
 * Makes an API request to retrieve data from Alpha Vantage.
 */
void ofApp::make_api_request(string symbol) {
    
    string url = "https://www.alphavantage.co/query?function=TIME_SERIES_MONTHLY&symbol=" +symbol+"&apikey=UJP0F3I7MQPJM9WR";
    
    bool parsingSuccessful = json.open(url);
    
    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << json.getRawString(true);
    } else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
    }
}

/**
 * Parses data from website and creates Stock objects.
 */
void ofApp::parse() {
    
    // accesses all elements in the JSON array
    for (auto value : json["Monthly Time Series"])
    {
        string open_value = value["1. open"].asString();
        string high_value = value["2. high"].asString();
        string low_value = value["3. low"].asString();
        string close_value = value["4. close"].asString();
        string volume_value = value["5. volume"].asString();
        
        Data stock_value = *new Data(stod(open_value), stod(high_value), stod(low_value), stod(close_value), stol(volume_value));
        
        stocks.push_back(stock_value);
    }
}

void ofApp::setup(){
    user_input();
    make_api_request(ticker_symbols[0]);
    parse();
    
    
    ofSetBackgroundColor(150);
    
    
    // Prepare the points for the plot
    int nPoints = 100;
    vector<ofxGPoint> points;
    
    for (int i = 0; i < nPoints; ++i) {
        points.emplace_back(i, stocks[i].get_low());
    }
    
    // Set the plot position on the screen
    plot.setPos(25, 25);
    
    // Set the plot title and the axis labels
    plot.setTitleText("A very simple example");
    plot.getXAxis().setAxisLabelText("x axis");
    plot.getYAxis().setAxisLabelText("y axis");
    
    // Add the points
    plot.setPoints(points);
    plot.setFontsMakeContours(true);
}

void ofApp::draw()
{
    //ofBeginSaveScreenAsPDF("screenshot-" + ofGetTimestampString() + ".pdf", false);
    plot.defaultDraw();
    //ofEndSaveScreenAsPDF();
}

void ofApp::user_input()   {
    
    string total_companies_str;
    
    
    for (int i = 0; i < 1; i++) {
        string ticker;
        cout << "Enter ticker symbol: ";
        cin >> ticker;
        
        transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);
        ticker_symbols.push_back(ticker);
    }
}



