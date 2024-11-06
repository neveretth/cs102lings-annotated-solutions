#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
using namespace std;

struct date {
    int month;
    int day;
    int year;
};

struct report {
    string number;
    int month;
    int day;
    int year;
    int speed;
    int speed_limit;
    char road_type;
};

const string THREE_LETTER_MONTHS[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
};

const double INTERSTATE_MULTIPLIER = 5.2243;
const double HIGHWAY_MULTIPLIER = 9.4312;
const double RESIDENTIAL_MULTIPLIER = 17.2537;
const double DEFAULT_MULTIPLIER = 12.916;

double get_multiplier(char type) {
    switch (type) {
        case 'i':
            return INTERSTATE_MULTIPLIER;
        case 'h':
            return HIGHWAY_MULTIPLIER;
        case 'r':
            return RESIDENTIAL_MULTIPLIER;
        default:
            return DEFAULT_MULTIPLIER;
    }
}

ifstream get_ifstream(string file_prompt) {
    char buf[64];
    string user_input;
    snprintf(buf, 64, "Enter a %s file: ", file_prompt.c_str());
    cout << buf;
    cin >> user_input;
    ifstream fin;
    fin.open(user_input);
    if (!fin.is_open()) {
        snprintf(buf, 64, "Unable to open %s.", user_input.c_str());
        cerr << buf << endl;
        exit(1);
    }
    return fin;
}

ofstream get_ofstream(string file_prompt) {
    char buf[64];
    string user_input;
    snprintf(buf, 64, "Enter a %s file: ", file_prompt.c_str());
    cout << buf;
    cin >> user_input;
    ofstream fout;
    fout.open(user_input);
    if (!fout.is_open()) {
        snprintf(buf, 64, "Unable to open %s.", user_input.c_str());
        cerr << buf << endl;
        exit(1);
    }
    return fout;
}

date get_date(string prompt) {
    char buf[64];
    date user_input;
    string fix = "";
    
    if (prompt == "end") fix += "  ";
    snprintf(buf, 64, "Enter report %s %s %s%s", prompt.c_str(), "date",
            fix.c_str(), "(mm dd yyyy): ");
    cout << buf;
    cin >> user_input.month >> user_input.day >> user_input.year;
    if (!cin.good()) {

        snprintf(buf, 64, "Failed to parse date!");
        cerr << buf << endl;
        exit(1);
    }
    return user_input;
}

const int MONTH_DAYS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int serialize_date(int month, int day, int year) {

    int days_from_months = 0;
    for (int i = 0; i < month - 1; i++) {
        days_from_months += MONTH_DAYS[i];
    }
    return (year * 365) + days_from_months + day;
}

double get_fine(report report_entry) {
    double fine = (report_entry.speed - report_entry.speed_limit) *
        get_multiplier(tolower(report_entry.road_type));
    if (fine <= 0) return 0;
    return fine;
}

report validate_date(report report_entry) {
    if (report_entry.year < 1000) report_entry.year += 2000;
    return report_entry;
}

int main() {

    ifstream ticket_file;
    ofstream report_file;

    date report_start_date;
    date report_end_date;
    ticket_file = get_ifstream("ticket");
    report_file = get_ofstream("report");

    report_start_date = get_date("start");
    report_end_date = get_date("end");
    char ticket_report_buf[256];
    report report_entry;

    while (ticket_file >> report_entry.number >> report_entry.month >>
            report_entry.day >> report_entry.year >> report_entry.speed >>
            report_entry.speed_limit >> report_entry.road_type) {

        report_entry = validate_date(report_entry);

        if (serialize_date(report_entry.month, report_entry.day, report_entry.year)
                < serialize_date(report_start_date.month, report_start_date.day,
                    report_start_date.year)) continue;
        if (serialize_date(report_entry.month, report_entry.day, report_entry.year)
                > serialize_date(report_end_date.month, report_end_date.day, report_end_date.year))
            continue;
        snprintf(ticket_report_buf, 256, "%02d-%s-%4d %s    $ %8.2f\n",
                report_entry.day, THREE_LETTER_MONTHS[report_entry.month - 1].c_str(),
                report_entry.year, report_entry.number.c_str(), get_fine(report_entry));
        report_file << ticket_report_buf;
    }
    ticket_file.close();
    report_file.close();
    return 0;
}
