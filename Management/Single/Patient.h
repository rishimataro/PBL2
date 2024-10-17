#ifndef PATIENT_H
#define PATIENT_H
#include "../../Library/Header.h"
#include "./Date.h"

class Patient
{
    private:
        string ID_patient;
        string fullName;
        string phone;
        Date dayOfBirth;
        bool sex; // 0: male, 1: female
        string address;
    public:
        //* Constructor & Destructor
        Patient(string ID_patient = "", string fullName = "", string phone = "", Date dayOfBirth = Date(), bool sex = false, string address = "");
        Patient(const Patient &patient);
        ~Patient();

        //* Setter
        void setID_patient(string ID_patient);
        void setFullName(string fullName);
        void setPhone(string phone);
        void setDayOfBirth(Date dayOfBirth);
        void setSex(bool sex);
        void setAddress(string address);

        //* Getter
        string getID_patient() const;
        string getFullName() const;
        string getPhone() const;
        Date getDayOfBirth() const;
        bool getSex() const;
        string getAddress() const;

        //* Function
        // Nhập 1 bệnh nhân
        void inputPatient();
        // In thông tin 1 bệnh nhân
        void printPatient();
        // Lưu 1 bệnh nhân vào file
        void savePatient(fstream& f);
        // Lấy 1 bệnh nhân từ file
        void setPatient(fstream& f);
};

#endif