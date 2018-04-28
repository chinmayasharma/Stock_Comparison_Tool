#ifndef data_h
#define data_h

#include <stdio.h>
#include <vector>
#include <string>
#include <map>

using std::string;

class Data {
    
private:
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
          double set_volume);
    
    double get_open();
    double get_high();
    double get_low();
    double get_close();
    double get_volume();
    
    void print();

};

#endif /* data_h */
