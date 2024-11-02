#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include <Header/Header.hpp>
#include <Management/Date.hpp>
#include <Management/Patient.hpp> // Thêm để sử dụng lớp Patient
#include <Library/Graphics.hpp>
class MedicalRecord {
private:
    string ID_record;         // ID bệnh án (MR02)
    string ID_patient;        // ID bệnh nhân (P2)
    Patient* patient;        // Con trỏ tới đối tượng Patient
    string symptoms;         // Triệu chứng
    string diagnosis;        // Chẩn đoán bệnh
    Date dateOfRecord;       // Ngày ghi nhận bệnh án

public:
    // Constructor & Destructor
    MedicalRecord(string ID_record = "", string ID_patient = "", Patient* patient = nullptr, string symptoms = "", string diagnosis = "", string dateOfRecord = "");
    MedicalRecord(const MedicalRecord &record);
    ~MedicalRecord();

    // Setters
    void setID_record(const string &id);
    void setID_patient(const string &id);
    void setSymptoms(const string &sym);
    void setDiagnosis(const string &diag);
    void setDateOfRecord(const Date &date);
    void setPatient(Patient* patient);

    // Getters
    string getID_record() const;
    string getID_patient() const;
    string getSymptoms() const;
    string getDiagnosis() const;
    Date getDateOfRecord() const;
    Patient* getPatient() const;

    // Methods to input and display the medical record
    void inputMedicalRecord();
    void printMedicalRecord();

    // Method to set data from a line of text (for loading from file)
    void setMedicalRecord(const string &line);

    // Method to save the medical record to a file
    void saveAllMedicalRecord(fstream &f);
    void saveMedicalRecord(fstream &f);
};

#endif
