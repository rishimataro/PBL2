#include "./MedicalRecord.h"

// Constructor & Destructor
MedicalRecord::MedicalRecord(string ID_record, string ID_patient, Patient* patient, string symptoms, string diagnosis, string dateOfRecord) {
    this->ID_record = ID_record;
    this->ID_patient = ID_patient;
    this->symptoms = symptoms;
    this->diagnosis = diagnosis;
    this->dateOfRecord.setDate(dateOfRecord);
    this->patient = patient;
}

MedicalRecord::MedicalRecord(const MedicalRecord &record) {
    this->ID_record = record.ID_record;
    this->ID_patient = record.ID_patient;
    this->symptoms = record.symptoms;
    this->diagnosis = record.diagnosis;
    this->dateOfRecord = record.dateOfRecord;
    this->patient = record.patient;
}

MedicalRecord::~MedicalRecord() {}

// Setters
void MedicalRecord::setID_record(const string &id) { this->ID_record = id; }
void MedicalRecord::setID_patient(const string &id) { this->ID_patient = id; }
void MedicalRecord::setSymptoms(const string &sym) { this->symptoms = sym; }
void MedicalRecord::setDiagnosis(const string &diag) { this->diagnosis = diag; }
void MedicalRecord::setDateOfRecord(const Date &date) { this->dateOfRecord = date; }
void MedicalRecord::setPatient(Patient* patient) { this->patient = patient; }

// Getters
string MedicalRecord::getID_record() const { return this->ID_record; }
string MedicalRecord::getID_patient() const { return this->ID_patient; }
string MedicalRecord::getSymptoms() const { return this->symptoms; }
string MedicalRecord::getDiagnosis() const { return this->diagnosis; }
Date MedicalRecord::getDateOfRecord() const { return this->dateOfRecord; }
Patient* MedicalRecord::getPatient() const { return this->patient; }

// Nhập thông tin bệnh án
void MedicalRecord::inputMedicalRecord() {
    int x = whereX(), y = whereY();

    gotoXY(x + 12, y + 1); cout << this->ID_record;
    gotoXY(x + 12, y + 4); cout << this->ID_patient;
    gotoXY(x + 12, y + 7); cin.ignore(); getline(cin, this->symptoms);
    gotoXY(x + 12, y + 10); cin.ignore(); getline(cin, this->diagnosis);
    gotoXY(x + 12, y + 13); this->dateOfRecord.inputDate();

}

// In thông tin bệnh án
void MedicalRecord::printMedicalRecord() {
    int x = whereX(), y = whereY();

    gotoXY(x + 4, y);
    cout << this->ID_record;
    gotoXY(x + 16, y);
    cout << this->ID_patient;

    if(this->patient != NULL) {
        gotoXY(x + 41, y);
        cout << patient->getFullName();
        gotoXY(x + 61, y);
        cout << patient->getSexToString();
    }

    gotoXY(x + 81, y);
    cout << this->symptoms;
    gotoXY(x + 101, y);
    cout << this->diagnosis;
    gotoXY(x + 121, y);
    cout << this->dateOfRecord.getDate() << endl;
}

// Thiết lập thông tin bệnh án từ một dòng văn bản
void MedicalRecord::setMedicalRecord(const string &line) {
    stringstream ss(line);
    string token;

    getline(ss, token, ';'); this->ID_record = token;
    getline(ss, token, ';'); this->ID_patient = token;
    getline(ss, token, ';'); this->symptoms = token;
    getline(ss, token, ';'); this->diagnosis = token;
    getline(ss, token, ';'); this->dateOfRecord.setDate(token);
}

// Lưu thông tin bệnh án vào file
void MedicalRecord::saveMedicalRecord(fstream &f) {
    f << this->ID_record << endl;
    f << this->ID_patient << endl;
    f << this->symptoms << endl;
    f << this->diagnosis << endl;
    f << this->dateOfRecord.getDate() << endl;
}

// Lưu tất cả bệnh án vào file
void MedicalRecord::saveAllMedicalRecord(fstream &f) {
    f << this->ID_record << ";" << this->ID_patient << ";" << this->symptoms << ";" 
      << this->diagnosis << ";" << this->dateOfRecord.getDate() << endl;
}
