//
//  utility.hpp
//  final_project
//
//  Created by Chinmaya Sharma on 4/30/18.
//

#ifndef utility_h
#define utility_h

#include "ofxJSON.h"
#include "data.h"
#include <vector>
#include <string>

using std::string;

std::string generate_url(bool isRealtime, string time_series, string ticker_name);
std::vector<Data> parse(ofxJSONElement retreived_json, string json_series);

#endif /* utility_hpp */
