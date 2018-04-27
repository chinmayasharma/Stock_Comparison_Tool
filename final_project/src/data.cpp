#include "data.h"
#include <vector>
#include <iostream>
#include <map>

using std::string;
using std::move;
using std::map;

/**
 * Constructor for Stock obbjects
 */
Data::Data(double set_open, double set_high, double set_low, double set_close, long set_volume) {
    this->open = set_open;
    this->high = set_high;
    this->low = set_low;
    this->close = set_close;
    this->volume = set_volume;
    
    
}

/**
 * Getter for Stock symbol
 */
string Data::get_symbol(){
    return this->symbol;
}

/**
 * Getter for Stock Opening price
 */
double Data::get_open(){
    return this->open;
    
}

/**
 * Getter for Stock High price
 */
double Data::get_high(){
    return this->high;
    
}

/**
 * Getter for Stock Low price
 */
double Data::get_low(){
    return this->low;
    
}

/**
 * Getter for Stock Closing price
 */
double Data::get_close(){
    return this->close;
    
}

/**
 * Getter for Stock Volume traded
 */
long Data::get_volume(){
    return this->volume;
    
}





