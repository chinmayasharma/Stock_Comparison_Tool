#include "stock.h"
#include <vector>
#include <iostream>

using std::string;
using std::move;

/**
 * Constructor for Stock obbjects
 */
Stock::Stock(string set_symbol, double set_open, double set_high, double set_low, double set_close, long set_volume) {
    this->symbol = set_symbol;
    this->open = set_open;
    this->high = set_high;
    this->low = set_low;
    this->close = set_close;
    this->volume = set_volume;
}

/**
 * Getter for Stock symbol
 */
string Stock::get_symbol(){
    return this->symbol;
}

/**
 * Getter for Stock Opening price
 */
double Stock::get_open(){
    return this->open;

}

/**
 * Getter for Stock High price
 */
double Stock::get_high(){
    return this->high;

}

/**
 * Getter for Stock Low price
 */
double Stock::get_low(){
    return this->low;

}

/**
 * Getter for Stock Closing price
 */
double Stock::get_close(){
    return this->close;

}

/**
 * Getter for Stock Volume traded
 */
long Stock::get_volume(){
    return this->volume;

}





