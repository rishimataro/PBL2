#ifndef DATE_H
#define DATE_H
#include <Header/Header.h>

class Date
{
    private:
        int day, month, year;
    public:
        // Constructors & Destructors
        Date(int day = 1, int month = 1, int year = 1900);
        Date(const Date& date);
        ~Date();
        // Setters
        void setDay(const int& day);
        void setMonth(const int& month);
        void setYear(const int& year);
        void setDate(const string& date);

        // Getters
        int getDay() const;
        int getMonth() const;
        int getYear() const;
        string getDate() const;

        void inputDate();
        void printDate() const;
        bool isValidDate() const;
        bool isCurrentDate() const;

        void setCurrentDate();
};

bool isLeapYear(int year);
int getDaysInMonth(int month, int year);
int getStartDayOfMonth(int month, int year);
#endif