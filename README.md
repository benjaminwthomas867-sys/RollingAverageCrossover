# RollingAverageCrossover
A program that takes in the data of a stock, etf etc. and prints the days when the smaller rolling average moves above the higher rolling average to indicate short term momentum is stronger than the long term trend.

I built this as a beginner project to teach myself some c++, not absolutely perfect, but pretty good, will have a go at optimising it at some point, just to see how quick I can get it to run.

The main.cpp is the c++ file and the ftse100_data.csv is an example data file.

**note that any headings in the data files (e.g. "Open, High, Low" etc.) must be removed before use, otherwise, will crash when trying to put the data into a vector. This can be bypassed by removing the "return 1;" commands from line 56 and 63**

The original data headers in the csv file were: date,open,high,low,close,volume, so for all data files, the data must be formatted in the csv in this way.

Future plan is to upgrade with yfinance: https://github.com/puddup/yfinance-cpp/blob/main/demo/quotes.cpp and look at efficiency.
