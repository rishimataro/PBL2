#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

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
    string diagnosis; // chuẩn đoán
    Date dateOfRecord;       

public:
    MedicalRecord(string ID_record = "", string ID_patient = "", string symptoms = "", string diagnosis = "", string dateOfRecord = "");
    MedicalRecord(const MedicalRecord &record);
    ~MedicalRecord();

    bool setID_record();
    void setID_patient(const string &id);
    void setSymptoms(const string &sym);
    void setDiagnosis(const string &diag);
    void setDateOfRecord(const string &date);

    string getID_record() const;
    string getID_patient() const;
    string getSymptoms() const;
    string getDiagnosis() const;
    Date getDateOfRecord() const;

    // operator
    MedicalRecord& operator=(const MedicalRecord &record);

    bool writeMedicalRecordToFile(fstream &f);
    bool writeMedicalRecordToFile_all(ofstream &fout);
    void readMedicalRecordFromFile(fstream &f);
};

#endif