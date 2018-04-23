#include "ofApp.h"
#include "data.h"

using std::string;
using std::transform;
using std::stol;
using std::stod;

std::vector<string> ticker_symbols;
std::vector<Data> stocks;

void make_api_request(string symbol) {
    
}

void ofApp::setup()
{
    string url = "https://www.alphavantage.co/query?function=TIME_SERIES_MONTHLY&symbol=MSFT&apikey=demo";
    
    bool parsingSuccessful = json.open(url);
    
    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << json.getRawString(true);
    } else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
    }
}

void ofApp::draw()
{
    ofBackground(0);
    ofSetColor(255);
    for (auto value : json["Monthly Time Series"])
    {
        //string date = json["Monthly Time Series"][i].asString();
        string open_value = value["1. open"].asString();
        string high_value = value["2. high"].asString();
        string low_value = value["3. low"].asString();
        string close_value = value["4. close"].asString();
        string volume_value = value["5. volume"].asString();
        
        Data stock_value = *new Data(stod(open_value), stod(high_value), stod(low_value), stod(close_value), stol(volume_value));
        
        stocks.push_back(stock_value);


        ofDrawBitmapString(stod(open_value), 20, 40);
    }
    
}

void user_input()   {
    
    string total_companies_str;
    
    cout << "How many companies would you like to analyze: ";
    int total_companies = 0;
    
    while (total_companies <= 0) {
        try {
            cin >> total_companies_str;
            total_companies = stoi(total_companies_str);
            
            if (total_companies <= 0 ) {
                cout << "Invalid number. Enter any number greater than 0: ";
            }
            
        } catch (std::exception e) {
            cout << "Invalid number. Enter any number greater than 0: ";
        }
    }
    
    for (int i = 0; i < total_companies; i++) {
        string ticker;
        cout << "Enter ticker symbol: ";
        cin >> ticker;
        
        transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);
        ticker_symbols.push_back(ticker);
    }
    
}


