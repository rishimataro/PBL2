#include "./Date.h"

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

// Getters
int Date::getDay() const { return this->day; }
int Date::getMonth() const { return this->month; }
int Date::getYear() const { return this->year; }

void Date::inputDate() {
    while(true) {
        char separator;
        cout << "Ngay sinh (dd/mm/yyyy): ";
        cin >> this->day >> separator >> this->month >> separator >> this->year;
        if(!this->isValidDate()) {
            cout << "Ngay khong hop le. Vui long nhap lai." << endl;
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

/* time_t timer;
tm * time;
time(&timer);
time = localtime(&timer);

date = time->tm_mday;
month = months[time->tm_mon];
day = days[time->tm_wday];
year = time->tm_year + BASE_YEAR; */

/* std::string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
std::string days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri",
                      "Sat"};
 
class Date{
    // Private Members
    private:
        std::string month;
        std::string day;
        int date;
        int year;
    // Public Members
    public:
        // Default Constructor
        Date() { 
                const int BASE_YEAR = 1900;
                time_t timer;
                tm * time;
                std::time(&timer);
                time = localtime(&timer);
                date = time->tm_mday;
                month = months[time->tm_mon];
                day = days[time->tm_wday];
                year = time->tm_year + BASE_YEAR;
        }
        void printDate(void) { 
            std::cout << "Current date " 
                      << this->month << " " << this->day << " "
                      << this->date  << " " << this->year;
        }
        // Destructor
        ~Date() {}
};
 
int main()
{
    Date d;
 
    d.printDate();
} */