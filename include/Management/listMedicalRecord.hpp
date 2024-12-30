#ifndef LISTMEDICALRECORD_HPP
#define LISTMEDICALRECORD_HPP
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

        vector<MedicalRecord*> setAllMedicalRecords();
        vector<MedicalRecord*> setMedicalRecordsByPatientID(const string& patientID);
        vector<MedicalRecord*> setMedicalRecordsByDiagnosis(const string& diagnosis);
        vector<MedicalRecord*> setMedicalRecordsByRecordRange(const string &startDate, const string &endDate);
        vector<pair<string, int>> setDiagnosisCount();

        void addMedicalRecord(const string& patientID, const string& symptoms, const string& diagnosis, const string& dateOfRecord);

        int checkRecordID(const string& recordID);

        bool removeMedicalRecordByID(const string& recordID);

        bool updateMedicalRecordByID(const string& recordID, const string& newDiagnosis, const string& newSymptoms);

        vector<MedicalRecord*> searchMedicalRecord(SearchField_MR field, const string& value);

        // Phân tích các bệnh phổ biến và đưa ra giải pháp
        string analyzeDiagnosisAndProvideSolutions(MedicalRecord* record, const string& diagnosis);
        bool appendDiagnosisSolutionToFile(const string& diagnosis, const string& solution);
        void loadSymptomSolutionsFromFile();
        map<string, string> getSymptomSolutions();

    private:
        map<string, string> symptomSolutions;
};

#endif