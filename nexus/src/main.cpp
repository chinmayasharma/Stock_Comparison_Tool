#include "ofApp.h"

int main() {
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofSetupOpenGL(500, 350, OF_WINDOW);
    ofSetBackgroundColor(152, 180, 212);
    ofRunApp(new ofApp());
}
