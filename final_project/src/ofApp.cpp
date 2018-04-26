#include "ofApp.h"

using std::string;
using std::transform;
using std::stol;
using std::stod;


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
        
        Data stock_value = *new Data(stod(open_value), stod(high_value), stod(low_value), stod(close_value), stol(volume_value));
        
        stocks.push_back(stock_value);
    }
    all_stocks.push_back(stocks);
}

void ofApp::setup(){
    user_input();
    make_api_request(ticker_symbols[0]);
    make_api_request(ticker_symbols[1]);
    generate_plot(30, all_stocks);
}

void ofApp::draw()
{
    //ofBeginSaveScreenAsPDF("screenshot-" + ofGetTimestampString() + ".pdf", false);
    for(int i =0; i < 2; i++)   {
        if (i == 0) {
            all_plots[0].defaultDraw();
        }
        else{
            //all_plots[i].defaultDraw();
        }
    }
    
    //ofEndSaveScreenAsPDF();
}

void ofApp::user_input()   {
    
    string ticker;
    
    for (int i = 0; i < 2; i++) {
        string ticker;
        cout << "Enter ticker symbol: ";
        cin >> ticker;
        
        transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);
        ticker_symbols.push_back(ticker);
    }
}

void ofApp::generate_plot(int range, std::vector<std::vector<Data>> stock_data) {
    
    // Prepare the points for the plot
    int nPoints = range;
    vector<ofxGPoint> points;
    
    for (int i = 0; i < 2; i++)  {
        
        // Set the plot title and the axis labels
        if (i == 0)  {
            plot.setTitleText("A very simple example");
            plot.getXAxis().setAxisLabelText("x axis");
            plot.getYAxis().setAxisLabelText("y axis");
        }
        
        for (int j = 0; j < nPoints; j++) {
            points.emplace_back(j, stock_data[i][j].get_low());
        }
        // Set the plot position on the screen
        plot.setPos(25, 25);
        
       
        // Add the points
        plot.setPoints(points);
        plot.setFontsMakeContours(true);
        all_plots.push_back(plot);
    }
}
