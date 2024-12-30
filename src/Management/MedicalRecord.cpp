#include <Management/MedicalRecord.hpp>

MedicalRecord::MedicalRecord(string ID_record, string ID_patient, string symptoms, string diagnosis, string dateOfRecord, string advice) {
    this->ID_record = ID_record;
    this->ID_patient = ID_patient;
    this->symptoms = symptoms;
    this->diagnosis = diagnosis;
    this->dateOfRecord.setDate(dateOfRecord);
    this->advice = advice;
}

MedicalRecord::MedicalRecord(const MedicalRecord &record) {
    this->ID_record = record.ID_record;
    this->ID_patient = record.ID_patient;
    this->symptoms = record.symptoms;
    this->diagnosis = record.diagnosis;
    this->dateOfRecord = record.dateOfRecord;
    this->advice = record.advice;
}

MedicalRecord::~MedicalRecord() {}

bool MedicalRecord::setID_record() {
    path file_path = "../Database/Medical_recordDB/medical_record.txt";
    file_path = absolute(file_path);
    
    fstream fi;
    fi.open(file_path, ios::in);

    if (!fi.is_open()) {
        return false;
    }

    int maxID = 1;
    
    if (isFileEmpty(fi)) {
        maxID = 0;
    } else {
        string temp;
        moveToEndOfLastLine(fi);
        getline(fi, temp);

        if (!temp.empty() && temp.substr(0, 2) == "MR") {
            maxID = stoi(temp.substr(2));
        }
    }

    maxID++;
    string id = "MR" + to_string(maxID);

    this->ID_record = id;

    fi.close();
    return true;
}


void MedicalRecord::setID_patient(const string &id) { this->ID_patient = id; }
void MedicalRecord::setSymptoms(const string &sym) { this->symptoms = sym; }
void MedicalRecord::setDiagnosis(const string &diag) { this->diagnosis = diag; }
void MedicalRecord::setDateOfRecord(const string &date) { this->dateOfRecord.setDate(date); }
void MedicalRecord::setAdvice(const string &advice) { this->advice = advice; }

string MedicalRecord::getID_record() const { return this->ID_record; }
string MedicalRecord::getID_patient() const { return this->ID_patient; }
string MedicalRecord::getSymptoms() const { return this->symptoms; }
string MedicalRecord::getDiagnosis() const { return this->diagnosis; }
Date MedicalRecord::getDateOfRecord() const { return this->dateOfRecord; }
string MedicalRecord::getAdvice() const { return this->advice; }

MedicalRecord& MedicalRecord::operator=(const MedicalRecord &record) {
    if (this == &record) return *this;
    this->ID_record = record.ID_record;
    this->ID_patient = record.ID_patient;
    this->symptoms = record.symptoms;
    this->diagnosis = record.diagnosis;
    this->dateOfRecord = record.dateOfRecord;
    this->advice = record.advice;

    return *this;
}

bool MedicalRecord::writeMedicalRecordToFile(ofstream &f) {
    string data;

    data.append(this->ID_record + ";");
    data.append(this->ID_patient + ";");
    data.append(this->symptoms + ";");
    data.append(this->diagnosis + ";");
    // data.append(this->advice + ";");
    data.append(this->dateOfRecord.getDate() + "\n");

    f << data;

    return true;
}

void MedicalRecord::readMedicalRecordFromFile(const string &line) {
    stringstream ss(line);
    string temp;

    getline(ss, temp, ';');
    this->ID_record = temp;

    getline(ss, temp, ';');
    this->ID_patient = temp;

    getline(ss, temp, ';');
    this->symptoms = temp;

    getline(ss, temp, ';');
    this->diagnosis = temp;

    getline(ss, temp, ';');
    this->dateOfRecord.setDate(temp);
}