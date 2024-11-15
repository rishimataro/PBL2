#ifndef LISTMEDICALRECORD_H
#define LISTMEDICALRECORD_H
#include <Management/MedicalRecord.hpp>
#include <Template/LinkedList.hpp>
#include <Header/Header.hpp>

enum class SearchField_MR { RecordID, PatientID, Diagnosis};

class listMedicalRecord : public LinkedList<MedicalRecord>
{
public:
    listMedicalRecord();
    ~listMedicalRecord();

    bool readListMedicalRecordFromFile();
    bool writeListMedicalRecordToFile(bool check);
    bool writeMedicalRecordToFile(int index);

    vector<MedicalRecord> setAllMedicalRecords();
    vector<MedicalRecord> setMedicalRecordsByPatientID(const string& patientID);
    vector<MedicalRecord> setMedicalRecordsByDiagnosis(const string& diagnosis);
    vector<MedicalRecord> setMedicalRecordsByRecordRange(const string &startDate, const string &endDate);
    vector<pair<string, int>> setDiagnosisCount(); // Thống kê số lượng chẩn đoán theo bệnh phổ biến

    void addMedicalRecord(const string& patientID, Patient* patient, const string& symptoms, const string& diagnosis, const string& dateOfRecord);

    int checkRecordID(const string& recordID);

    bool removeMedicalRecordByID(const string& recordID);

    void updateMedicalRecordByID(const string& recordID, const string& newDiagnosis, const string& newSymptoms);

    vector<MedicalRecord> searchMedicalRecord(SearchField_MR field, const string& value);

    // ! Chưa test
    // Phân tích các bệnh phổ biến và đưa ra giải pháp
    string analyzeDiagnosisAndProvideSolutions(const string& diagnosis);
    bool appendDiagnosisSolutionToFile(const string& diagnosis, const string& solution);
    void loadSymptomSolutionsFromFile();
    map<string, string> getSymptomSolutions();

private:
    map<string, string> symptomSolutions;
};

#endif
