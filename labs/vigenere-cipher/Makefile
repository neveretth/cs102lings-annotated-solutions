vigenere: vigenere.cpp
	g++ vigenere.cpp -o vigenere -std=c++11
	
e:
	./vigenere plaintext.txt encrypted.txt keystr e
	
d:
	./vigenere encrypted.txt output.txt keystr d

debug:
	g++ -g vigenere.cpp -std=c++11 -Wall -Wextra --pedantic
	
test:
	python scripts/test.py vigenere.cpp --print
