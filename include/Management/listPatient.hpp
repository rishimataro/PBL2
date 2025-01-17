#ifndef LISTPATIENT_H
#define LISTPATIENT_H

#include <Management/Patient.hpp>
#include <Template/LinkedList.hpp>
#include <Header/Header.hpp>
#include <cstdio>

enum class SearchField { ID, FullName, CCCD };

class listPatient : public LinkedList<Patient>
{
    public:
        //* Constructor & Destructor  
        listPatient();
        ~listPatient();

        // * Read & Write
        bool readListPatientFromFile();
        bool writeListPatientToFile(bool check); // lưu file tổng, check = true: lưu file tổng, check = false: lưu file lẻ

        //* Setter & Getter
        vector<Patient*> setPatientByGender(bool gender);
        vector<Patient*> setPatientByBirthRange(const string &startDate, const string &endDate);
        vector<Patient*> setAllPatient();

        //* Add
        void addPatient(const string& newFullName, const string& newPhone, const string& newDayOfBirth, const string& newCCCD, const string& newGender, const string& newAddress);
        
        //* Check
        int checkID(const string& ID);

        //* Delete
        bool removePatientByID(const string& ID);

        //* Update
        bool updatePatientByID(const string& ID, const string& newFullName, const string& newPhone, const string& newDayOfBirth, const string& newCCCD, const string& newGender, const string& newAddress);

        //* Search
        vector<Patient*> searchPatient(SearchField field, const string& value);
};

#endif