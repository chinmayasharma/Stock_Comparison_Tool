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

    Stock ();

    void get_name();
    
    void print();
};

#endif /* stock_hpp */
