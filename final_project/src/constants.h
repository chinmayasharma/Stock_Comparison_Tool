//
//  constants.h
//  final_project
//
//  Created by Chinmaya Sharma on 4/28/18.
//

#ifndef constants_h
#define constants_h

#include <string>

using std::string;


/**
 * JSON related constants.
 */

// JSON attribute parsing labels
string json_time_series_label = "Time Series (Daily)";
string json_open_attribute_label = "1. open";
string json_high_attribute_label = "2. high";
string json_low_attribute_label = "3. low";
string json_close_attribute_label = "4. close";
string json_volume_attribute_label = "5. volume";

// JSON url components
string initial_url_component = "https://www.alphavantage.co/query?function=";
string url_symbol_component = "&symbol=";
string url_api_key_component = "&apikey=UJP0F3I7MQPJM9WR";


/**
 * GUI related constants.
 */

// buttons labels
string compare_button_label = "                                  c o m p a r e";
string display_button_label = "                                  d i s p l a y";

//text input labels
string ticker_one_label = "**  ticker #1";
string ticker_one_example = "# eg.   AAPL #";

string ticker_two_label = "**  ticker #2";
string ticker_two_example = "# eg.   MSFT #";

// color picker labels
string color_picker_one_label = "**  color #1";
string color_picker_two_label = "**  color #2";

ofColor default_color_one = ofColor::fromHex(0x45B8AC);
ofColor default_color_two = ofColor::fromHex(0x5B5EA6);

// slider labels

string range_slider_label = "** range";
int default_range = 50;

// drop down meny labels

string drop_down_attributes_label = "select attribute";

// drop down menu selection attributes
string drop_down_open_attribute = "OPENING PRICES";
string drop_down_high_attribute = "HIGHEST PRICES";
string drop_down_low_attribute = "LOWEST PRICES";
string drop_down_close_attribute = "CLOSING PRICES";
string drop_down_volume_attribute = "TRADE VOLUME";

std::vector<string> attribute_options = {drop_down_open_attribute,
    drop_down_high_attribute,
    drop_down_low_attribute,
    drop_down_close_attribute,
    drop_down_volume_attribute};

static std::map<std::string, int> data_map = {{drop_down_open_attribute, 0},
    {drop_down_high_attribute, 1},
    {drop_down_low_attribute, 2},
    {drop_down_close_attribute, 3},
    {drop_down_volume_attribute, 4}};

#endif /* constants_h */