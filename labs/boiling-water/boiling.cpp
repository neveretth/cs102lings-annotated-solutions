#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

double elevation_to_boiling_point(const double elevation) {
    double boiling_point = 0.0;
    double pressure = 29.921 * pow((1 - (0.0000068753 * elevation)), 5.2559);
    
    boiling_point = 49.161 * log(pressure) + 44.932;

    return boiling_point;
}

int main(int argc, char **argv) {

    if (argc == 1) {
       cerr << "usage: ./boiling filename" << endl; 
       return 1;
    }
    
    ifstream fin(argv[1]);
    if(!fin.is_open()) {
       cerr << "File failed to open." << endl; 
       return 1;
    }

    string header_line;
    getline(fin, header_line);
  
    string line;
    vector <string> cities;
    vector <int> elevs;
    int i = 1;
    
    cout << "Boiling Point at Altitude Calculator" << endl;
            
    while (getline(fin, line)) {
        istringstream sstr(line);
        string temp;
        
        getline(sstr, temp, ',');
        cities.push_back(temp);
        getline(sstr, temp, ',');
        

        getline(sstr, temp, ',');
        elevs.push_back(stoi(temp));
        
        i++;
        cout << i-1 << ". " << cities[i-2] << endl;
    }
    
    cout << "Enter city number: ";
    cin >> i;
    
    cout << "The boiling point at " << cities[i-1] << " is " << elevation_to_boiling_point(elevs[i-1]) << " degrees Fahrenheit." << endl;

    fin.close();
    return 0;
}
