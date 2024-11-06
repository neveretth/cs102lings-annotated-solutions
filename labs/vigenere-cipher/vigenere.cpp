#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const size_t ALPHABET_SIZE = 26;

class VigenereCipher {
  private:
    string mKey;
    char mTable[ALPHABET_SIZE][ALPHABET_SIZE];

    string makeKeystream(const string message) const;

    static string fileToString(const string inputFile);
    static void stringToFile(const string message, const string outputFile);

  public:
    // Public methods
    VigenereCipher(const string key); // Constructor
    void encrypt(const string inputFile, const string outputFile) const;
    void decrypt(const string inputFile, const string outputFile) const;
    void print() const;
};

string VigenereCipher::fileToString(const string inputFile) {
    ifstream fin(inputFile);
    string message;
    char character;

    if (!fin.is_open()) {
        cerr << "Input file " << inputFile << " unable to open." << endl;
        exit(1);
    }

    while (fin.get(character)) {
        message.push_back(character);
    }

    fin.close();

    return message;
}

void VigenereCipher::stringToFile(const string message,
                                  const string outputFile) {
    ofstream fout(outputFile);

    if (!fout.is_open()) {
        cerr << "Output file " << outputFile << " unable to open." << endl;
        exit(1);
    }

    fout << message;

    fout.close();
}

void VigenereCipher::print() const {
    cerr << "Key: " << mKey << endl;
    cerr << "Table:" << endl;
    for (size_t i = 0; i < ALPHABET_SIZE; i++) {
        for (size_t j = 0; j < ALPHABET_SIZE; j++) {
            cerr << " " << mTable[i][j] << " ";
        }
        cerr << endl;
    }
}

string VigenereCipher::makeKeystream(const string message) const {
    string keystream;
    size_t keyIndex = 0;

    for (size_t i = 0; i < message.size(); i++) {
        if (islower(message[i])) {
            keystream += mKey[keyIndex % mKey.size()];
            keyIndex++;
        } else {
            keystream += message[i];
        }
    }

    cout << "Keystream: " << keystream << endl;

    return keystream;
}

void VigenereCipher::encrypt(const string inputFile,
                             const string outputFile) const {
    
    string message = fileToString(inputFile);
    const string keystream = makeKeystream(message);

    for (size_t i = 0; i < message.size(); i++) {
        if (islower(message[i])) {
            message[i] = mTable[keystream[i] - 97][message[i] - 97];
        }
    }
    
    stringToFile(message, outputFile);
}

void VigenereCipher::decrypt(const string inputFile,
                             const string outputFile) const {
    string message = fileToString(inputFile);
    const string keystream = makeKeystream(message);

    for (size_t i = 0; i < message.size(); i++) {
        if (islower(message[i])) {
            for (size_t n = 0; n < ALPHABET_SIZE; n++) {
                if (mTable[n][keystream[i] - 97] == message[i]) {
                    message[i] = mTable[n][0];
                    break;
                }
            }
        }
    }
    
    stringToFile(message, outputFile);
}

VigenereCipher::VigenereCipher(const string key) {
    mKey = key;

    for (size_t i = 0; i < ALPHABET_SIZE; i++) {
        size_t k = 0;
        for (size_t n = i; n < ALPHABET_SIZE; n++) {
            mTable[i][k] = 97 + n;
            k++;
        }
        for (size_t n = 0; n < i; n++) {
            mTable[i][k] = 97 + n;
            k++;
        }
    }
}

int main(int argc, char **argv) {

    if (argc != 5) {
        cerr << "usage: ./vigenere inputFile outputFile key [e/d]" << endl;
        return 1;
    }

    const string inputFile = argv[1];
    const string outputFile = argv[2];
    const string key = argv[3];
    const string operation = argv[4];

    VigenereCipher cipher(key);

    if (operation == "e") {
        cipher.encrypt(inputFile, outputFile);
    }
    if (operation == "d") {
        cipher.decrypt(inputFile, outputFile);
    }

    return 0;
}
