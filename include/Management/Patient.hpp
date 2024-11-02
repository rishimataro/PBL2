#ifndef PATIENT_H
#define PATIENT_H
#include <Header/Header.hpp>
#include <Management/Date.hpp>
#include <Library/Graphics.hpp>
class Patient
{
    private:
        string ID_patient;
        string fullName;
        string phone;
        Date dayOfBirth;
        string CCCD;
        bool gender; // 0: male, 1: female
        string address;
    public:
        //* Constructor & Destructor
        Patient(string ID_patient = "", string fullName = "", string phone = "", string dayOfBirthStr = "", string CCCD = "", bool sex = false, string address = "");
        Patient(const Patient &patient);
        ~Patient();

        //* Setter
        void setID_patient(string ID_patient);
        void setFullName(string fullName);
        void setPhone(string phone);
        void setDayOfBirth(Date dayOfBirth);
        void setCCCD(string CCCD);
        void setGender(bool gender);
        void setAddress(string address);

        //* Getter
        string getID_patient() const;
        string getFullName() const;
        string getPhone() const;
        Date getDayOfBirth() const;
        string getCCCD () const;
        bool getGender() const;
        string getGenderToString() const;
        string getAddress() const;

        //* Function
        // Nhập 1 bệnh nhân
        void inputPatient();
        // In thông tin 1 bệnh nhân
        void printPatientHorizontal();
        // Lưu 1 bệnh nhân vào file
        void saveAllPatient(fstream& f);
        void savePatient(fstream& f);
        // Lấy 1 bệnh nhân từ file
        void setPatient(const string& line);
};

#endif