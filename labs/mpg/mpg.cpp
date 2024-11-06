#include <iostream>
#include <limits>
#include <string.h>
#include <stdio.h>

using namespace std;

double get_double_input(string type, string measure) {
    double value;
    while (true) {
        cout << "Enter " << type << "'s " << measure << ": ";
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return value;
        }
    }
}

string func(double car_miles, double car_gallons, double truck_miles, double truck_gallons) {
    while (1) {
        cout << "Enter command: ";
        string vehicle_type;
        cin >> vehicle_type;
        
        if (vehicle_type.find("car") != string::npos) {
            car_miles += get_double_input("car", "miles");
            car_gallons += get_double_input("car", "gallons");
            continue;
        }
        if (vehicle_type.find("truck") != string::npos) {
            truck_miles += get_double_input("truck", "miles");
            truck_gallons += get_double_input("truck", "gallons");
            continue;
        }
        if (vehicle_type.find("done") != string::npos) {
            break;
        }
        else {
            cout << "Unknown command." << endl;
        }
    }

    char buf[256];
    char temp[64];
    
    if (car_miles == 0) {
        snprintf(temp, 256, "Fleet has no cars.\n");
        strcat(buf, temp);
    } else {
        double car_avg_mpg = car_miles / car_gallons;
        snprintf(temp, 256, "Average car MPG = %.5f\n", car_avg_mpg);
        strcat(buf, temp);
    }
     
    if (truck_miles == 0) {
        snprintf(temp, 256, "Fleet has no trucks.\n");
        strcat(buf, temp);
    } else {
        double truck_avg_mpg = truck_miles / truck_gallons;
        snprintf(temp, 256, "Average truck MPG = %.5f\n", truck_avg_mpg);
        strcat(buf, temp);
    }
    return buf;
}

int main() {
    
    cout << func(0, 0, 0, 0);
    
    return 0;
}
