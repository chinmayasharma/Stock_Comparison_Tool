#include "ofMain.h"
#include "time_controller.h"

/**
 * Sets up time elapsed for the game.
 */
void TimeController::setup(float s) {
    start_time = s;
    interval_time = 60000;
}

/**
 * Controls whether graph should be replotted.
 */
bool TimeController::should_refresh() {
    if (ofGetElapsedTimeMillis() - start_time > interval_time) {
        start_time = ofGetElapsedTimeMillis();
        return true;
    }
    return false;
}
