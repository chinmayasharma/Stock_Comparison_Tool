//
//  constants.h
//  final_project
//
//  Created by Chinmaya Sharma on 4/28/18.
//

#ifndef constants_h
#define constants_h

#include "ofMain.h"
#include <string>
#include <map>
using std::string;


/**
 * JSON related constants.
 */

// JSON attribute parsing labels
extern string json_time_series_daily_label;
extern string json_time_series_intraday_label;

extern string json_open_attribute_label;
extern string json_high_attribute_label;
extern string json_low_attribute_label;
extern string json_close_attribute_label;
extern string json_volume_attribute_label;

// JSON url components
extern string initial_url_component;
extern string daily_series;
extern string intra_day_series;
extern string url_symbol_component;
extern string url_api_key_component;

 extern std::map<std::string, std::string> _map;

/**
 * GUI related constants.
 */

// buttons labels
extern string display_button_label;
extern string screenshot_button_label;
extern string exit_button_label;

//text input labels
extern string ticker_one_label;
extern string ticker_one_example;

extern string ticker_two_label;
extern string ticker_two_example;

// color picker labels
extern string color_picker_one_label;
extern string color_picker_two_label;

extern ofColor default_color_one;
extern ofColor default_color_two;

// slider labels

extern string range_slider_label;
extern int max_size;
extern int default_range;

// drop down meny labels

extern string drop_down_attributes_label;

// drop down menu selection attributes
extern string drop_down_open_attribute;
extern string drop_down_high_attribute;
extern string drop_down_low_attribute;
extern string drop_down_close_attribute;
extern string drop_down_volume_attribute;

extern std::vector<string> attribute_options;

extern std::map<std::string, int> data_map;

#endif /* constants_h */
