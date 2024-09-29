#include "../../Library/Header.h"

class Date
{
    private:
        int day, month, year;
    public:
        // Constructors & Destructors
        Date(int day = 1, int month = 1, int year = 1900);
        Date(const Date &date);
        ~Date();

        // Setters
        void setDay(const int& day);
        void setMonth(const int& month);
        void setYear(const int& year);

        // Getters
        int getDay() const;
        int getMonth() const;
        int getYear() const;

        void inputDate();
        void printDate() const;
        bool isValidDate() const;
        bool isCurrentDate() const;
};