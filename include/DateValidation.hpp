#ifndef DATE_VALIDATION_H
#define DATE_VALIDATION_H
#include <string>
#include <cctype>

// Accept real Gregorian calendar dates in MM/DD/YYYY format.
inline bool isValidDate(const std::string& date)
{
    if (date.size() != 10 || date[2] != '/' || date[5] != '/') return false;
    for (int i = 0; i < 10; ++i)
        if (i != 2 && i != 5 && !std::isdigit(static_cast<unsigned char>(date[i]))) return false;
    int month = std::stoi(date.substr(0, 2));
    int day = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (leap) days[1] = 29;
    return day <= days[month - 1];
}
#endif
