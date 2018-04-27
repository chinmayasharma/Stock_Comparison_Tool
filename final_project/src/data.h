#ifndef data_h
#define data_h

#include <stdio.h>
#include <vector>
#include <string>
#include <map>

using std::string;
static std::map<std::string, int> data_map = {{"open", 0},{"high",1},{"low",2},{"close",3},{"volume",4}};

class Data {
    
private:
    string symbol;
    double open;
    double high;
    double low;
    double close;
    double volume;
    
public:
    
    Data (double set_open,
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

#endif /* data_h */
