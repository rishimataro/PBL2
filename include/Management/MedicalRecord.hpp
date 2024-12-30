#ifndef MEDICALRECORD_HPP
#define MEDICALRECORD_HPP

#include <Header/Header.hpp>
#include <Management/Date.hpp>
#include <Management/Patient.hpp>
#include <Library/Graphics.hpp>
#include <Library/Filelib.hpp>
#include <filesystem>
using namespace filesystem;

class MedicalRecord {
    private:
        string ID_record; 
        string ID_patient;       
        string symptoms; // triệu chứng        
        string diagnosis; // chẩn đoán
        Date dateOfRecord;
        string advice;       

    public:
        MedicalRecord(string ID_record = "", string ID_patient = "", string symptoms = "", string diagnosis = "", string dateOfRecord = "", string advice = "");
        MedicalRecord(const MedicalRecord &record);
        ~MedicalRecord();

        bool setID_record();
        void setID_patient(const string &id);
        void setSymptoms(const string &sym);
        void setDiagnosis(const string &diag);
        void setDateOfRecord(const string &date);
        void setAdvice(const string &advice);

        string getID_record() const;
        string getID_patient() const;
        string getSymptoms() const;
        string getDiagnosis() const;
        Date getDateOfRecord() const;
        string getAdvice() const;

        // operator
        MedicalRecord& operator=(const MedicalRecord &record);

        bool writeMedicalRecordToFile(ofstream &f);
        void readMedicalRecordFromFile(const string &line);
};

#endif