#ifndef LISTMEDICALRECORD_H
#define LISTMEDICALRECORD_H
#include <Management/MedicalRecord.hpp>
#include <Template/LinkedList.hpp>
#include <Header/Header.hpp>

enum class SearchField { RecordID, PatientID, Symptoms };

class listMedicalRecord : public LinkedList<MedicalRecord>
{
public:
    listMedicalRecord();
    ~listMedicalRecord();

    bool readListMedicalRecordFromFile();
    bool writeListMedicalRecordToFile(bool check);
    bool writeMedicalRecordToFile(int index);

    void setListMedicalRecordByFile();
    void saveListMedicalRecordToFile();
    void saveMedicalRecordToFile(int index);

    vector<MedicalRecord> setAllMedicalRecords() const;
    vector<MedicalRecord> setMedicalRecordsByPatientID(const string& patientID) const;
    vector<MedicalRecord> setMedicalRecordsByDiagnosis(const string& diagnosis) const;
    vector<MedicalRecord> setMedicalRecordsByRecordRange(const Date &startDate, const Date &endDate) const;

    void addMedicalRecord(const MedicalRecord &record);

    int checkRecordID(const string& recordID);

    bool removeMedicalRecordByID(const string& recordID);

    void updateMedicalRecordByID(const string& recordID);

    void searchMedicalRecord(SearchField field, const string& value);

    void generateStatistics();
    void displayMostCommonSymptoms() const;
    void displayDiagnosisCount() const;
};

#endif
