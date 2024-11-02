#ifndef LISTPATIENT_H
#define LISTPATIENT_H

#include "./Single/Patient.h"
#include "../Template/LinkedList.cpp"
#include "../Library/Header.h"

enum class SearchField { ID, FullName, CCCD };

class listPatient : public LinkedList<Patient>
{
    public:
        //* Constructor & Destructor  
        listPatient();
        ~listPatient();

        //* Setter & Getter
        void setListPatientByFile();
        void saveListPatientToFile(); // lưu file tổng
        void savePatientToFile(int index); // lưu file lẻ

        //* Display
        void printPatientBySex(bool sex) const;
        void printPatientByBirthRange(const string &startDate, const string &endDate);
        void printAllPatient() const;

        //* Add
        void addPatient(const Patient &patient);
        
        //* Check
        int checkID(const string& ID);

        //* Delete
        void removePatientByID(const string& ID);

        //* Update
        void updatePatientByID(const string& ID);

        //* Search
        void searchPatient(SearchField field, const string& value);

        // LinkedList<Patient> searchPatientByID(const string& ID) const;
        // LinkedList<Patient> searchPatientByFullName(const string& fullName) const;
        // LinkedList<Patient> searchPatientByCCCD(const string& CCCD) const;
};

#endif