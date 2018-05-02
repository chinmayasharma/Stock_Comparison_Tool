#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/constants.h"
#include "../src/utility.h"
#include <vector>
#include <map>

/**
 * **************************************************************************************************************
 * URL generation tools Processing Tests
 * **************************************************************************************************************
 */

TEST_CASE("URL Generation Test") {
    SECTION("Standard URL Tests") {

        SECTION("Standard URL - valid") {
            REQUIRE (
                    "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&apikey=UJP0F3I7MQPJM9WR" ==
                    generate_url(false, daily_series, "MSFT"));
        }
        SECTION("Standard URL - invalid ticker") {
            REQUIRE (
                    "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&apikey=UJP0F3I7MQPJM9WR" ==
                    generate_url(false, daily_series, "ABCDEFGHI"));
        }
        SECTION("Standard URL - invalid time series") {
            REQUIRE (
                    "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=MSFT&apikey=UJP0F3I7MQPJM9WR" ==
                    generate_url(false, intra_day_series, "MSFT"));
        }
        SECTION("Standard URL - invalid boolean realtime") {
            REQUIRE (
                    "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&interval=1min&apikey=UJP0F3I7MQPJM9WR" ==
                    generate_url(true, daily_series, "MSFT"));
        }
    }
    SECTION("Realtime URL Tests") {

        SECTION("Realtime URL - valid") {
            REQUIRE (
                    "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=MSFT&interval=1min&apikey=UJP0F3I7MQPJM9WR" ==
                    generate_url(true, intra_day_series, "MSFT"));
        }
        SECTION("Realtime URL - invalid ticker") {
            REQUIRE (
                    "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=ABCDEFGHI&interval=1min&apikey=UJP0F3I7MQPJM9WR" ==
                    generate_url(true, intra_day_series, "ABCDEFGHI"));
        }
        SECTION("Realtime URL - invalid time series") {
            REQUIRE (
                    "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&interval=1min&apikey=UJP0F3I7MQPJM9WR" ==
                    generate_url(true, daily_series, "MSFT"));
        }
        SECTION("Realtime URL - invalid boolean realtime") {
            REQUIRE (
                    "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=MSFT&apikey=UJP0F3I7MQPJM9WR" ==
                    generate_url(false, intra_day_series, "MSFT"));
        }
    }
}