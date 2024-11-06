boiling: boiling.cpp
	g++ boiling.cpp -o boiling -std=c++11

debug:
	g++ -g boiling.cpp -std=c++11 -Wall -Wextra --pedantic
	
test:
	python scripts/test.py boiling.cpp --print
	
m:
	./boiling City-State-Altitude-1.csv
