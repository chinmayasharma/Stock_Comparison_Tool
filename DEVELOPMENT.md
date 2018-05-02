## Week #1

Initially, I tried collecting data from Yahoo Finance, but came across a number of issues. Thereafter, I explored a number of other APIs, including Google Finance, Bloomberg, etc., concluding that the Alpha Vantage API would best suit my project. 

Additionally, I was initially trying to use the CURL library, which I found to be a little complex to use. Figuring it out set me bback a few days, during which I came across ofxJson, which best suited my project needs.


## Week #2

Following feedback from the week's code review, I decided to implement a User Interface, instead the command line. For this, I explored a number of libraries, including ofxGUI and it's many derivatives. Eventually, I found ofxDatHGUI, which was ideal for my application. 

Another change that I made was the use of ofxGrafica instead of ofxPlotter, since I was having trouble plotting two series on the same plot. During this time, I also experimented with ofxGraph, but didn't find the plot it generated to be visually pleasing.

## Week #3

With the basic prototype in place, I worked on adding additional features to the application. Most importantly, I dealt with a feature that retreives data from the Alpha Vantage API in near-realtime (a delay of 60 seconds). Additionally, I improved the User Interface, wrote tests for non-openframeworks methods and added a working screenshot feature.
