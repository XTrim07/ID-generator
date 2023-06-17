#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <random>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

int gender;

string generateCNP() {
    //int year = rand() % 300 + 1800; // intre 1800 si 2099
    //int year = rand() % 100 + 1900; //intre 1900 si 1999
    int year = rand() % 25 + 1980; //intre 1980 si 2004
    int month = rand() % 12 + 1;
    int day = rand() % 31 + 1;
    if ((day > 0 && day < 32) && (month > 0 && month < 13) && (year > 1899 && year < 2000)) {
        gender = rand() % 2 + 1; //1 sau 2
    } else if ((day > 0 && day < 32) && (month > 0 && month < 13) && (year > 1799 && year < 1900)) {
        gender = rand() % 2 + 3; //3 sau 4
    } else if ((day > 0 && day < 32) && (month > 0 && month < 13) && (year > 1999 && year < 2100)) {
        gender = rand() % 2 + 5; //5 sau 6
    }
    cout << year << '\n';

    //last two digits of year
    stringstream ss;
    ss << setw(2) << setfill('0') << year % 100;
    string yearLastTwoDigits = ss.str();
    int serial = rand() % 999999 + 1;

    string cnp = to_string(gender) + yearLastTwoDigits + (month < 10 ? "0" : "") + to_string(month) + (day < 10 ? "0" : "") + to_string(day) + (serial < 100000 ? (serial < 10000 ? (serial < 1000 ? (serial < 100 ? (serial < 10 ? "00000" : "0000") : "000") : "00") : "0") : "") + to_string(serial);
    return cnp;
}

string chooseRandomSeries(const vector<string>& series) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, series.size() - 1);
    return series[dis(gen)];
}

string genderGenerate() {
    if (gender % 2) {
        return "M";
    }
    return "F";
}

string generateCode() {
    string code;
    // Generate first character (capital letter)
    char firstChar = 'A' + rand() % 26;
    code += firstChar;
    // Generate middle 3 characters (random capital letters or numbers)
    int numCount = 0;
    for (int i = 0; i < 3; ++i) {
        int randNum = rand() % 36;
        if (randNum < 26) {
            code += 'A' + randNum;
        } else {
            code += '0' + (randNum - 26);
            ++numCount;
        }
    }
    // Ensure at least one number
    if (numCount == 0) {
        int pos = rand() % 3 + 1;
        code[pos] = '0' + rand() % 10;
        ++numCount;
    }
    // 35% chance to add a second number
    if (numCount == 1 && rand() % 100 < 35) {
        int pos;
        do {
            pos = rand() % 3 + 1;
        } while (code[pos] >= '0' && code[pos] <= '9');
        code[pos] = '0' + rand() % 10;
    }
    // Generate last character (capital letter with 85% probability)
    int randNum = rand() % 100;
    if (randNum < 85) {
        char lastChar = 'A' + rand() % 26;
            code += lastChar;
    } else {
        char lastChar = '0' + rand() % 10;
        code += lastChar;
    }
    return code;
}

int main() {
    srand(time(0));
    string cnp = generateCNP();
    vector<string> seriesList = {"AX", "TR", "AR", "ZR", "XC", "ZC", "MM", "XM", "XB", "XT", "BV", "ZV", "XR", 
    "DP", "DR", "DT", "DX", "RD", "RR", "RT", "RX", "RK", "RZ*", "IF", "XZ", "KL", "KX", "CJ", "KT", "KZ", "DX", 
    "DZ", "HD", "XD", "VN", "GL", "ZL", "GG", "MX", "MZ", "IZ", "MH", "HR", "XH", "ZH", "NT", "NZ", "AS", "AZ", 
    "PH", "PX", "KS", "VX", "SM", "KV", "SB", "OT", "SZ", "SV", "XV", "TM", "TZ", "DD", "ZD", "GZ", "ZS", "MS", 
    "TC", "VS", "XS", "SX"};
    string series = chooseRandomSeries(seriesList);
    cout << series << '\n' << cnp << '\n' << genderGenerate() << '\n' << generateCode() << '\n';
    return 0;
}

//nr, valabilitatea, codurile de pe banda alba