# CS126 Project Proposal: Stock Performance Comparison Platform 💰💰
***
A miniature C++ platform that allows the user to specify stock ticker symbol to display and compare different stock performances for a number of attributes.
***
## Summary:
The proposed C++ application will allow users to specify one or two ticker symbols. If the user enters a single ticker, the lone ticker along with the chosen attibbute will be plotted. If the user enters two tickers, a comparison plot with the two tickers in addition to the chosen attribute will be plotted. 

The application will also have a near-realtime aspect to it, in which it will retreive data from the Alpha Vantage API  with a delay of 60 seconds. Additionally, the user will have the option of customizing the graph, and even saving it.
***

Although not exactly what I intend to do, the GIF below embodies the idea ebhind the project!
![](https://i.makeagif.com/media/7-14-2015/hO4TpB.gif)

## Libraries: 

1) I will be using ofxJson to retrieve hsitorical and realtime data from the Alpha Vantage API
2) Additionally, I will be using ofxGrafica to generate interactive graphs from the retreived data
3) Lastly, I will use ofxDatGUi to implement a User Interface to enhance user interaction with the platform

***
## Checkpoints for next 3 weeks:

__Week 1:__ Figure out and complete the data retrieving aspect of the application

__Week 2:__ Explore ofxGrafica and generate visuals from the previosuly retreived data.

__Week 3:__ Create a User Interface and polishing the design while adding a real time aspect to the project

***
### Relevant Personal Background:

1) Previously worked with retrieving APIs

2) A basic understanding of Financial Markets
