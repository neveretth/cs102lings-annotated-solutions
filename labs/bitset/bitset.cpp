#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class BITSET {
    vector<int> mSets;

  public:
    BITSET();
    bool Test(int index) const;
    void Set(int index);
    void Clear(int index);
    int GetNumSets() const;
    int GetSet(int which_set) const;
};

string ToBinary(int bit_set, int spacing = 4);

int main() {
    BITSET sets;
    string command;
    int which;
    do {
        cout << "> ";
        if (!(cin >> command) || "q" == command) {
            break;
        }
        
        if ("t" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else {
                cout << sets.Test(which) << '\n';
            }
        } else if ("s" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else {
                sets.Set(which);
            }
        } else if ("g" == command) {
            int spacing;
            string line;
            getline(cin, line);
            istringstream sin{line};
            if (!(sin >> which)) {
                cout << "Invalid index\n";
            } else {
                if (!(sin >> spacing)) {
                    spacing = 4;
                }
                if (sets.GetNumSets() <= which) {
                    cout << ToBinary(0, spacing) << '\n';
                }
                else {
                    cout << ToBinary(sets.GetSet(which), spacing) << '\n';
                }
            }
        } else if ("c" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else {
                sets.Clear(which);
            }
        } else if ("n" == command) {
            if (sets.GetNumSets() == 0) {
                cout << "1" << endl;
            } else {
                cout << sets.GetNumSets() << endl;
            }
        }
        else {
            cout << "Unknown command '" << command << "'\n";
        }
    } while (true);
    return 0;
}

string ToBinary(int bit_set, int spacing) {
    string ret;
    for (int i = 31; i >= 0; i--) {
        if (bit_set & (1 << i)) {
            ret += '1';
        } else {
            ret += '0';
        }
        
        if ((32 - i) % spacing == 0 && i != 0) {
            ret += ' ';
        }
    }
    return ret;
}

BITSET::BITSET() : mSets(1, 0) {}

bool BITSET::Test(int index) const {
    int which_set = index / 32;
    int which_bit = index - (which_set * 32);
    if (which_set >= GetNumSets()) {
        return false;
    }
    return ((1 << which_bit) & mSets[which_set]) != 0;
}

void BITSET::Set(int index) {
    int which_set = index / 32;
    int which_bit = index - (which_set * 32);
    while (which_set >= GetNumSets()) {
        mSets.push_back(0);
    }
    mSets.at(which_set) = mSets.at(which_set) | (1 << which_bit);
}

void BITSET::Clear(int index) {
    int which_set = index / 32;
    int which_bit = index - (which_set * 32);
    if (which_set < GetNumSets()) {
        mSets.at(which_set) = mSets.at(which_set) & ~(1 << which_bit); 
        if (GetNumSets() - 1 == which_set) {
            while (mSets.at(which_set) == 0 && GetNumSets() > 1) {
                mSets.erase(mSets.begin() + which_set);
                which_set--;
            }
        }
    }
}

int BITSET::GetNumSets() const { return static_cast<int>(mSets.size()); }

int BITSET::GetSet(int which_set) const {
    if (GetNumSets() <= which_set) return 0;
    return mSets.at(which_set);
}
