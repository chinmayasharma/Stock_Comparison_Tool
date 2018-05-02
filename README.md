
# Nexus: Stock Performance Comparison Platform 💰💰

---

### About: 

Nexus is a stock market data plotting application. It can retrieve realtime data (only when the market is open i.e. 9:30 - 4PM ET), and historical data of up to 100 days. The platform was primarily written in C++, using OpenFrameworks libraries. 

Although the platform was initially written for Mac OSX, it is compatible with Windows and Linux as well. The platform is compatible with Enable typographer option to see result.

---

### How to build - Mac OSX

1) Download openframeworks from their [website](http://openframeworks.cc/download/)

2) Download or clone the the project from [Github](https://github.com/uiuc-sp18-cs126/final-project-chinmayasharma.git)

3) Place the entire project folder in myApps directory in OpenFrameworks.

4) Open the project by clicking the nexus.xcodeproj file on a Mac. 

5) Use the dropdown menu Product -> Build or by simultaneously pressing ⌘+B (CMD+B) 

---
### How to use:
To use the application, the user must do the following:
1) Specify up to two valid ticker symbols in the text input fields

2) Pick colors from the Color Picker

3) Chose an attribute from the dropdown menu

4) Provide a range to the slider (optional)

5) Click realtime if desired

6) Press the DISPLAY button

Additionally, the user can zoom in and out of the graph plotting using mouse keys, and can take screenshots of the page at any given time.

---
### How it works:
Tasks in the application are executed in the following order:
1) When the user makes a change to the existing state of the GUI, e.g. adds text to the text input fields, the values are instantaneously stored in corresponding variables.

2) After the user hits enter, if the inputs are valid, conditions for the update function are set to true. 

3) A URL is generated, based on the ticker symbols entered by the user and whether he/ she clicked realtime or not

3) API requests are made to the Alpha Vantage, based on the number and symbol of tickers that the user entered. Subsequent requests are contingent to the previous request returning true 

4) Stock objects are created from the data and stored in an array that is then passed onto the plot as points. Additionally, the plot is customized and annotated based on previously entered user data.

5) The plot is then drawn on the screen. If realtime was clicked, the plot will be refreshed every minute with updated values.

---
![Nexus - Single](https://cdn1.imggmi.com/uploads/2018/5/2/cc36832a00656b1fdd1064e598d60188-full.png)


![Nexus - Dual](https://cdn1.imggmi.com/uploads/2018/5/2/2ec78c5eb99df8dbb839430fd977f1a5-full.png)
