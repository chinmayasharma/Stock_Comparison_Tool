#ifndef stock_hpp
#define stock_hpp

#include <stdio.h>
#include <vector>
#include <string>

using std::string;

class Stock {
    
private:
    string symbol;
    double open;
    double high;
    double low;
    double close;
    long volume;
    
public:

    Stock (string set_symbol,
           double set_open,
           double set_high,
           double set_low,
           double set_close,
           long set_volume);

    string get_symbol();
    double get_open();
    double get_high();
    double get_low();
    double get_close();
    long get_volume();

    
    void print();
};

#endif /* stock_hpp */
