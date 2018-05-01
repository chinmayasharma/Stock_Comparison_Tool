
#ifndef time_controller_hpp
#define time_controller_hpp

#include <stdio.h>
class TimeController {

private:
    float start_time;
    float interval_time;

public:
    void setup(float e);
    bool should_refresh();
};
#endif /* time_controller_h */
