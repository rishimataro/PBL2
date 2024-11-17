#pragma once
#include "Header.hpp"
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
        bool status = 1;
        bool isProcessed = 0;
    public:
        Appoinment();
        void copy(const Appoinment& app);
        Appoinment(Patient& patient, const Date& date, int time, const string& description);
        bool UpdateStatus(const bool& Status = 1, const bool& isProcessed = 0);
        void setDate(Date date);
        void setTime(int time);
        void setPatientID(const Patient& patient);
        void setDescription(const string& description);
        //Chưa sử dụng!!!!!!!
        void readFromFile();
        void setID(const string& ID);
        void setStatus(bool status) { this->status = status; };
        void setIsProcessed(bool isProcessed) { this->isProcessed = isProcessed; };
        bool setID();
        string getID() const { return ID; };
        Date getDate() const { return date; };
        int getTime() const { return time; };
        string getDescription() const { return description; };
        string getPatientID() const { return Patient_ID; };
        bool getStatus() const { return status; };
        bool getIsProcessed() const { return isProcessed; };
        bool writeToFile();
        void ThemLichKham(const std::string& hieuLuc = "1", const std::string& trangThai = "0");
        Appoinment& operator=(const Appoinment& app);
        // void readFromFile(ifstream& file);
        ~Appoinment();
    private:
        void DocFileLich(std::map<std::string, std::vector<std::string>>& lichKham);
        void GhiFileLich(const std::map<std::string, std::vector<std::string>>& lichKham);
};
vector<Appoinment> searchAppoinments(const Patient& patient);
string GioKham(int time_slot);
void printCalendar(int month, int year);
void AppoinmentUI();
