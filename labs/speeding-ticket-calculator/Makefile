speeding: speeding.cpp
	g++ speeding.cpp -o speeding -std=c++11

debug:
	g++ -g speeding.cpp -std=c++11 -Wall -Wextra --pedantic
	
test:
	python scripts/test.py speeding.cpp --print
	
fs:
	python scripts/test.py speeding.cpp --print --help
