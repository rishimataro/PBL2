#pragma once
#include <Management/Date.hpp>
#include <Management/Patient.hpp>
#include <Library/Filelib.hpp>
#include <Library/Graphics.hpp>
#include <filesystem>
using namespace filesystem;


class Appoinment
{
    private:
        string ID;
        Date date;
        int time;//second
        string Patient_ID;
        string description;
    public:
        Appoinment();
        void setDate(Date date);
        void setTime(int time);
        void setPatientID(const Patient& patient);
        void setDescription(const string& description);
        //Chưa sử dụng!!!!!!!
        void readFromFile();
        bool setID();
        bool writeToFile();
        // void readFromFile(ifstream& file);
        ~Appoinment();
};

void printCalendar(int month, int year);
void AppoinmentUI();
