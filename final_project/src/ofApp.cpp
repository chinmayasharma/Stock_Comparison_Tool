#include "ofApp.h"
#include "stock.h"

using std::string;
using std::transform;
using std::stoi;

std::vector<string> ticker_symbols;
std::vector<Stock> stocks;



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
    
   

        ofDrawBitmapString(json, 20,40);

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


