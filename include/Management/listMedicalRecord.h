#ifndef LISTMEDICALRECORD_H
#define LISTMEDICALRECORD_H

#include "./Single/MedicalRecord.h"
#include "../Template/LinkedList.cpp"
#include "../Library/Header.h"

enum class SearchField { RecordID, PatientID, Symptoms };

class listMedicalRecord : public LinkedList<MedicalRecord>
{
public:
    //* Constructor & Destructor  
    listMedicalRecord();
    ~listMedicalRecord();

    //* Setter & Getter
    void setListMedicalRecordByFile(); 
    void saveListMedicalRecordToFile();
    void saveMedicalRecordToFile(int index);

    //* Display
    void printAllMedicalRecords() const;
    void printMedicalRecordsByPatientID(const string& patientID) const;
    void printMedicalRecordsByDiagnosis(const string& diagnosis) const;
    void printMedicalRecordsByRecordRange(const Date &startDate, const Date &endDate) const;

    //* Add
    void addMedicalRecord(const MedicalRecord &record);

    //* Check
    int checkRecordID(const string& recordID);

    //* Delete
    void removeMedicalRecordByID(const string& recordID);

    //* Update
    void updateMedicalRecordByID(const string& recordID);

    //* Search
    void searchMedicalRecord(SearchField field, const string& value);

    //* Statistics
    void generateStatistics();  // Tạo thống kê về bệnh án
    void displayMostCommonSymptoms() const;  // Hiển thị triệu chứng phổ biến nhất
    void displayDiagnosisCount() const;  // Hiển thị số lượng chẩn đoán theo bệnh
};

#endif
