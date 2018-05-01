#include "ofMain.h"
#include "time_controller.h"

/**
 *
 */
void TimeController::setup(float s) {
    start_time = s;
    interval_time = 70000;
}

/**
 *
 */
bool TimeController::should_refresh() {
    if (ofGetElapsedTimeMillis() - start_time > interval_time) {
        start_time = ofGetElapsedTimeMillis();
        return true;
    }
    return false;
}
