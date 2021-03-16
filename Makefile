launch: run
	/mnt/c/Program\ Files\ \(x86\)/Google/Chrome/Application/chrome.exe test.html

run: build
	./csv2chart test.csv

build:
	g++ csv2chart.cc -g -o csv2chart
