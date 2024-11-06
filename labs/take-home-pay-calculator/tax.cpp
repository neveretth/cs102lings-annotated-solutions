#include <iomanip> 
#include <iostream>

using namespace std;

const double MINIMUM_WAGE = 15080;
const double RATE1 = 0.10;
const double BRACKET2 = 10276;
const double RATE2 = 0.12;
const double BRACKET3 = 41776;
const double RATE3 = 0.22;
const double BRACKET4 = 89076;
const double RATE4 = 0.24;
const double BRACKET5 = 170051;
const double RATE5 = 0.32;
const double BRACKET6 = 215951;
const double RATE6 = 0.35;
const double BRACKET7 = 539901;
const double RATE7 = 0.37;
const double MEDICARE_RATE = 0.0145;
const double SOCSEC_RATE = 0.062;

double get_income_tax(double salary) {
    if (salary >= BRACKET7) return ((salary - BRACKET7 + 1) * RATE7) + get_income_tax(BRACKET7 - 1);
    if (salary >= BRACKET6) return ((salary - BRACKET6 + 1) * RATE6) + get_income_tax(BRACKET6 - 1);
    if (salary >= BRACKET5) return ((salary - BRACKET5 + 1) * RATE5) + get_income_tax(BRACKET5 - 1);
    if (salary >= BRACKET4) return ((salary - BRACKET4 + 1) * RATE4) + get_income_tax(BRACKET4 - 1);
    if (salary >= BRACKET3) return ((salary - BRACKET3 + 1) * RATE3) + get_income_tax(BRACKET3 - 1);
    if (salary >= BRACKET2) return ((salary - BRACKET2 + 1) * RATE2) + get_income_tax(BRACKET2 - 1);
    else return salary * RATE1;
}

double get_medicare_tax(double salary) {
    return salary * MEDICARE_RATE;
}

double get_socsec_tax(double salary) {
    return salary * SOCSEC_RATE;
}


int main() {
    double salary;
    
    cout << "Enter a salary: $";
    cin >> salary;

    if (salary < MINIMUM_WAGE) {
        cerr << "This is less than minimum wage for a yearly salary." << endl;
        return 1; 
    }

    double income_tax = get_income_tax(salary);
    double medicare_tax = get_medicare_tax(salary);
    double socsec_tax = get_socsec_tax(salary);
    double take_home = salary - income_tax - medicare_tax - socsec_tax;

    cout << fixed << setprecision(2);
    cout << ("-----------------------------------") << endl;
    
    cout << left << setw(25) << setfill(' ') << "Yearly Salary:";
    cout << "$";
    cout << right << setw(9) << setfill(' ') << salary << endl;
        
    cout << left << setw(25) << setfill(' ') << "Social Security Tax:";
    cout << "$";
    cout << right << setw(9) << setfill(' ') << socsec_tax << endl;
    
    cout << left << setw(25) << setfill(' ') << "Medicare Tax:";
    cout << "$";
    cout << right << setw(9) << setfill(' ') << medicare_tax << endl;
    
    cout << left << setw(25) << setfill(' ') << "Income Tax:";
    cout << "$";
    cout << right << setw(9) << setfill(' ') << income_tax << endl;
    
    cout << ("-----------------------------------") << endl;
    
    cout << left << setw(25) << setfill(' ') << "Take Home Salary:";
    cout << "$";
    cout << right << setw(9) << setfill(' ') << take_home << endl;
    
    cout << left << setw(25) << setfill(' ') << "Monthly Take Home Pay:";
    cout << "$";
    cout << right << setw(9) << setfill(' ') << take_home / 12 << endl;

    return 0;
}
