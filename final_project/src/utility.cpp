//
//  utility.cpp
//  final_project
//
//  Created by Chinmaya Sharma on 4/30/18.
//

#include "utility.h"
#include "data.h"
#include "constants.h"
/**
 * Parses data from website and creates Stock objects.
 */
std::vector<Data> parse(ofxJSONElement retreived_json, string json_series) {
    
    std::vector<Data> temp_stocks;
    
    for (auto value : retreived_json[json_series])
    {
        Data stock_value(stod(value[json_open_attribute_label].asString()),
                         stod(value[json_high_attribute_label].asString()),
                         stod(value[json_low_attribute_label].asString()),
                         stod(value[json_close_attribute_label].asString()),
                         stod(value[json_volume_attribute_label].asString()));
        temp_stocks.push_back(stock_value);
    }
    cout << temp_stocks.size() << endl;
    return temp_stocks;
}

/**
 *
 */
std::string generate_url(bool isRealtime, string time_series, string ticker_name)  {
    
    if(isRealtime)    {
        return initial_url_component + time_series + url_symbol_component + ticker_name+ "&interval=1min" +url_api_key_component;
    }
    else{
        return initial_url_component + time_series + url_symbol_component + ticker_name+ url_api_key_component;
    }
}
