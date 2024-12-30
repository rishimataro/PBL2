#include <Management/listMedicalRecord.hpp>

listMedicalRecord::listMedicalRecord() : LinkedList<MedicalRecord>() {
    this->readListMedicalRecordFromFile();
    this->loadSymptomSolutionsFromFile();
}

listMedicalRecord::~listMedicalRecord() { 
    // for (int i = 0; i < this->size(); i++) {
    //     delete this->get(i); // Giải phóng bộ nhớ cho từng bệnh án
    // }
    // this->clear(); // Xóa toàn bộ danh sách bệnh án
}

bool listMedicalRecord::readListMedicalRecordFromFile() {
    string file_path = "../Database/Medical_recordDB/medical_record.txt";
    fstream fin;

    fin.open(file_path, ios::in);
    if (!fin.is_open())
        return false;

    string line;
    while (getline(fin, line)) {
        if (!line.empty()) {
            MedicalRecord* record = new MedicalRecord();
            record->readMedicalRecordFromFile(line);
            this->append(record);
        }
    }
    fin.close();
    return true;
}

bool listMedicalRecord::writeListMedicalRecordToFile(bool check) {
    string file_path = "../Database/Medical_recordDB/medical_record.txt";
    char ch;

    ifstream fi(file_path);
    if (fi.is_open()) {
        fi.seekg(-1, ios::end);
        fi.get(ch);
        if (ch != '\n' && ch != '\0') {
            ofstream temp(file_path, ios::app);
            temp << "\n";
            temp.close();
        }
        fi.close();
    }

    ofstream fo;
    check ? fo.open(file_path, ios::trunc) : fo.open(file_path, ios::app);

    if (!fo.is_open()) 
        return false;

    MedicalRecord* record;
    if (check) {
        for (int i = 0; i < this->size(); i++) {
            record = this->get(i);
            record->writeMedicalRecordToFile(fo);
        }
    } else {
        record = this->get(this->size() - 1);
        record->writeMedicalRecordToFile(fo);
    }

    fo.close();
    return true;
}


vector<MedicalRecord*> listMedicalRecord::setAllMedicalRecords() {
    vector<MedicalRecord*> records;
    if (this->size() == 0) return records;

    for(int i = 0; i < this->size(); i++) {
        records.push_back(this->get(i)); 
    }

    return records;
}

vector<MedicalRecord*> listMedicalRecord::setMedicalRecordsByPatientID(const string& patientID) {
    vector<MedicalRecord*> records;
    if (this->size() == 0) return records;

    for(int i = 0; i < this->size(); i++) {
        if (this->get(i)->getID_patient() == patientID) {
            records.push_back(this->get(i));
        }
    }

    return records;
}

vector<MedicalRecord*> listMedicalRecord::setMedicalRecordsByDiagnosis(const string& diagnosis) {
    vector<MedicalRecord*> records;
    if (this->size() == 0) return records;

    for(int i = 0; i < this->size(); i++) {
        if (this->get(i)->getDiagnosis() == diagnosis) {
            records.push_back(this->get(i));
        }
    }

    return records;
}

vector<MedicalRecord*> listMedicalRecord::setMedicalRecordsByRecordRange(const string &startDate, const string &endDate) {
    vector<MedicalRecord*> records;
    if (this->size() == 0) return records;

    Date start, end;
    start.setDate(startDate);
    end.setDate(endDate);

    for(int i = 0; i < this->size(); i++) {
        if (this->get(i)->getDateOfRecord() >= start && this->get(i)->getDateOfRecord() <= end) {
            records.push_back(this->get(i));
        }
    }

    return records;
}

vector<pair<string, int>> listMedicalRecord::setDiagnosisCount() {
    vector<pair<string, int>> diagnosisCount;
    if (this->size() == 0) return diagnosisCount;

    map<string, int> count;
    for (int i = 0; i < this->size(); i++) {
        count[this->get(i)->getDiagnosis()]++;
    }

    for (auto it = count.begin(); it != count.end(); it++) {
        diagnosisCount.push_back(make_pair(it->first, it->second));
    }

    return diagnosisCount;
}

void listMedicalRecord::addMedicalRecord(const string& patientID, const string& symptoms, const string& diagnosis, const string& dateOfRecord) {
    MedicalRecord* newRecord = new MedicalRecord();

    newRecord->setID_record();
    newRecord->setID_patient(patientID);
    newRecord->setSymptoms(symptoms);
    newRecord->setDiagnosis(diagnosis);
    newRecord->setDateOfRecord(dateOfRecord);

    this->append(newRecord);
    this->writeListMedicalRecordToFile(false);
}

int listMedicalRecord::checkRecordID(const string& recordID) {
    for (int i = 0; i < this->size(); i++) {
        if (this->get(i)->getID_record() == recordID) {
            return i;
        }
    }
    return -1;
}

bool listMedicalRecord::removeMedicalRecordByID(const string& recordID) {
    int index = this->checkRecordID(recordID);
    if (index == -1)
        return false;
    this->remove(index);
    this->writeListMedicalRecordToFile(true);
    return true;
}

bool listMedicalRecord::updateMedicalRecordByID(const string& recordID, const string& newDiagnosis, const string& newSymptoms) {
    int index = this->checkRecordID(recordID);
    if (index == -1)
        return false;

    auto curMR = this->get(index);
    if (!curMR)
        return false;

    curMR->setDiagnosis(newDiagnosis);
    curMR->setSymptoms(newSymptoms);
    this->set(index, curMR);

    return this->writeListMedicalRecordToFile(true);
}


vector<MedicalRecord*> listMedicalRecord::searchMedicalRecord(SearchField_MR field, const string& value) {
    vector<MedicalRecord*> result;
    if (this->size() == 0)
        return result;

    string lowerValue = toLowerCase(value);

    for (int i = 0; i < this->size(); i++) {
        string fieldValue;
        switch (field) {
        case SearchField_MR::RecordID:
            fieldValue = toLowerCase(this->get(i)->getID_record());
            break;
        case SearchField_MR::PatientID:
            fieldValue = toLowerCase(this->get(i)->getID_patient());
            break;
        case SearchField_MR::Diagnosis:
            fieldValue = toLowerCase(this->get(i)->getDiagnosis());
            break;
        }

        if (fieldValue.find(lowerValue) == 0) {
            result.push_back(this->get(i));
        }
    }

    return result;
}

void listMedicalRecord::loadSymptomSolutionsFromFile() {
    path file_path = "../Database/Medical_recordDB/symptom_solutions.txt";
    file_path = absolute(file_path);

    ifstream file;
    file.open(file_path);

    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        string diagnosis, solution;
        getline(stream, diagnosis, ';');
        getline(stream, solution);
        symptomSolutions[diagnosis] = solution;
    }

    file.close();
}

map<string, string> listMedicalRecord::getSymptomSolutions() {
    return symptomSolutions;
}

bool listMedicalRecord::appendDiagnosisSolutionToFile(const string& diagnosis, const string& solution) {
    this->symptomSolutions[diagnosis] = solution;

    path file_path = "../Database/Medical_recordDB/symptom_solutions.txt";
    file_path = absolute(file_path);

    ofstream file;
    file.open(file_path, ios::app);

    if (!file.is_open()) return false;

    file << diagnosis << ";" << solution << "\n";

    file.close();
    return true;
}

string listMedicalRecord::analyzeDiagnosisAndProvideSolutions(MedicalRecord* record, const string& diagnosis) {
    if (this->symptomSolutions.find(diagnosis) != this->symptomSolutions.end()) {
        record->setAdvice(this->symptomSolutions[diagnosis]);
        return this->symptomSolutions[diagnosis];
    }

    return "Không có lời khuyên cho bệnh này!";
}