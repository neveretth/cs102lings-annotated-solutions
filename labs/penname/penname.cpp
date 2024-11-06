#include <iostream>

using namespace std;

int main() {
    string first_name;
    string middle_name;
    int age;
    int street_number;
    string street_name;
    string street_type;
    string city;

    cout << "Enter your first and middle names: ";
    cin >> first_name >> middle_name;
    cout << "Enter your age: ";
    cin >> age;
    cout << "Enter your street number, name, and type: ";
    cin >> street_number >> street_name >> street_type;
    cout << "Enter your city of birth: ";
    cin >> city;
    
    cout << endl;

    cout << "Your penname name is " << city << " " << street_name << "."<< endl;
    cout << "You will write as a " << (street_number % age) * 3 << " year old." << endl;
    cout << "Your address is " << ((age * 425) / street_number) << " " << middle_name << " " << street_type << "." << endl;
}
