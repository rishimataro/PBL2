#include <Management/Date.hpp>
// int safe_stoi(const std::string &str) {
//     try {
//         return std::stoi(str);
//     } catch (const std::invalid_argument& e) {
//         std::cerr << "Lỗi: Chuỗi không hợp lệ để chuyển đổi thành số nguyên: " << e.what() << std::endl;
//         return 0; // Giá trị mặc định hoặc xử lý lỗi
//     }
// }

// Constructors & Destructors
Date::Date(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

Date::Date(const Date &date) {
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
}

Date::~Date() { }

// Setters
void Date::setDay(const int& day) { this->day = day; }
void Date::setMonth(const int& month) { this->month = month; }
void Date::setYear(const int& year) { this->year = year; }
void Date::setDate(const string& date) {
    if (date == "") return;
    
    string day_str, month_str, year_str;
    size_t found = date.find('/');
    if (found != string::npos) {
        day_str = date.substr(0, found);
        size_t found2 = date.find('/', found + 1);
        if (found2 != string::npos) {
            month_str = date.substr(found + 1, found2 - found - 1);
            year_str = date.substr(found2 + 1);
        }
    }
    this->day = stoi(day_str);
    this->month = stoi(month_str);
    this->year = stoi(year_str);
}

// Getters
int Date::getDay() const { return this->day; }
int Date::getMonth() const { return this->month; }
int Date::getYear() const { return this->year; }
string Date::getDate() const {
    string day_str = to_string(this->day);
    string month_str = to_string(this->month);
    string year_str = to_string(this->year);
    string res;
    if(day_str.length() == 1) day_str = "0" + day_str;
    if(month_str.length() == 1) month_str = "0" + month_str;
    res = day_str + "/" + month_str + "/" + year_str;
    return res;
}

void Date::inputDate() {
    while(true) {
        char separator;
        cin >> this->day >> separator >> this->month >> separator >> this->year;
        if(!this->isValidDate()) {
            cout << "Ngày không hợp lệ. Vui lòng nhập lại!" << endl;
        }
        else break;
    }
}

void Date::printDate() const {
    cout << setfill('0') << setw(2) << this->day << "/" << setfill('0') << setw(2) << this->month << "/" << this->year << endl;
}

bool Date::isValidDate() const {
    if(this->year < BASE_YEAR) return false;
    if(this->month < 1 || this->month > 12) return false;

    if(this->day < 1 || this->day > 31) return false;
    if(this->day == 31 && (this->month == 2 || this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11)) return false;
    if(this->day > 29 && (this->month == 2)) return false;

    bool isLeap = (this->year % 4 == 0 && this->year % 100 != 0) || (this->year % 400 == 0);
    if (!isLeap && this->day == 29 && this->month == 2) 
        return false;

    return true;
}

bool Date::isCurrentDate() const {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int currentDay = ltm->tm_mday;
    int currentMonth = 1 + ltm->tm_mon;
    int currentYear = BASE_YEAR + ltm->tm_year;

    return (this->day == currentDay && this->month == currentMonth && this->year == currentYear);
}

Date& Date::operator=(const Date& date) {
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
    return *this;
}

bool Date::operator<=(const Date& other) const {
    if (this->year < other.year) return true;
    if (this->year > other.year) return false;

    if (this->month < other.month) return true;
    if (this->month > other.month) return false;

    return this->day <= other.day;
}

bool Date::operator>=(const Date& other) const {
    if (this->year > other.year) return true;
    if (this->year < other.year) return false;

    if (this->month > other.month) return true;
    if (this->month < other.month) return false;

    return this->day >= other.day;
}

bool Date::operator<(const Date& other) const {
    if (this->year < other.year) return true;
    if (this->year > other.year) return false;

    if (this->month < other.month) return true;
    if (this->month > other.month) return false;

    return this->day < other.day;
}

bool Date::operator>(const Date& other) const {
    if (this->year > other.year) return true;
    if (this->year < other.year) return false;

    if (this->month > other.month) return true;
    if (this->month < other.month) return false;

    return this->day > other.day;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int getDaysInMonth(int month, int year) {
    switch (month) {
        case 1: return 31;
        case 2: return isLeapYear(year) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}
int getStartDayOfMonth(int month, int year) {
    int d = 1, m = month, y = year;
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    return (d + (13 * (m + 1)) / 5 + y + (y / 4) - (y / 100) + (y / 400)) % 7;
}