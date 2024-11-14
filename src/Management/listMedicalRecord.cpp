#include <Management/listMedicalRecord.hpp>

listMedicalRecord::listMedicalRecord() {
    this->head = NULL;
}

listMedicalRecord::~listMedicalRecord() {
    if (this->head == NULL) return;
    
    Node<MedicalRecord>* current = this->head;
    Node<MedicalRecord>* tail = this->head->prev;

    do {
        Node<MedicalRecord>* temp = current;
        current = current->next;
        delete temp;
    } while (current != head);

    this->head = NULL;
}

bool listMedicalRecord::readListMedicalRecordFromFile() {
    string file_path = "../Database/MedicalRecordDB/medicalRecords.txt";
    fstream fin, recordFile;
    MedicalRecord record;

    fin.open(file_path, ios::in);
    if (!fin.is_open())
        return false;

    string id;
    while (getline(fin, id)) {
        if (id.empty())
            continue;

        file_path = "../Database/MedicalRecordDB/" + id + ".txt";
        recordFile.open(file_path, ios::in);

        if (!recordFile.is_open())
            continue;

        record.readMedicalRecordFromFile(recordFile);
        this->append(record);

        recordFile.close();
    }
    fin.close();
    return true;
}

bool listMedicalRecord::writeListMedicalRecordToFile(bool check) {
    string file_path = "../Database/MedicalRecordDB/medicalRecords.txt";
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
    if (check) {
        fo.open(file_path, ios::trunc); 
    } else {
        fo.open(file_path, ios::app);  
    }

    if (!fo.is_open())
        return false;

    MedicalRecord record;
    if (check) {
        for (int i = 0; i < this->size(); i++) {
            record = this->get(i);
            record.writeMedicalRecordToFile_all(fo);
        }
    } else {
        record = this->get(this->size() - 1);
        record.writeMedicalRecordToFile_all(fo);
    }

    fo.close();
    return true;
}

bool listMedicalRecord::writeMedicalRecordToFile(int index) {
    string path = "../Database/MedicalRecordDB/";
    string fileName = path + this->get(index).getID_record() + ".txt";

    fstream fout;
    fout.open(fileName, ios::out);

    if (!fout.is_open()) {
        return false;
    }

    this->get(index).writeMedicalRecordToFile(fout);
    fout.close();
    return true;
}

void listMedicalRecord::setListMedicalRecordByFile() {
    fstream fin;
    fin.open("../Database/MedicalRecordDB/medicalRecords.txt", ios::in);

    if (!fin.is_open())
        return;

    string line;
    while (getline(fin, line)) {
        if (line.empty())
            continue;

        MedicalRecord record;
        record.setMedicalRecord(line);
        this->addMedicalRecord(record);
    }
    fin.close();
}

void listMedicalRecord::saveListMedicalRecordToFile() {
    fstream fout;
    fout.open("../Database/MedicalRecordDB/medicalRecords.txt", ios::out);

    if (!fout.is_open())
        return;

    for (int i = 0; i < this->size(); i++) {
        this->get(i).saveAllMedicalRecord(fout);
    }

    fout.close();
    cout << "Lưu thành công!" << endl;
}

void listMedicalRecord::saveMedicalRecordToFile(int index) {
    string path = "../Database/MedicalRecordDB/";
    string fileName = path + this->get(index).getID_record() + ".txt";
    fstream fout;
    fout.open(fileName, ios::out);

    if (!fout.is_open()) {
        return;
    }

    this->get(index).saveMedicalRecord(fout);
    fout.close();
}

vector<MedicalRecord> listMedicalRecord::setAllMedicalRecords() const {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    for (int i = 0; i < this->size(); i++) {
        records.push_back(this->get(i));
    }
    return records;
}

vector<MedicalRecord> listMedicalRecord::setMedicalRecordsByPatientID(const string& patientID) const {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        if (record.getPatientID() == patientID) {
            records.push_back(record);
        }
    }
    return records;
}

vector<MedicalRecord> listMedicalRecord::setMedicalRecordsByDiagnosis(const string& diagnosis) const {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        if (record.getDiagnosis() == diagnosis) {
            records.push_back(record);
        }
    }
    return records;
}

vector<MedicalRecord> listMedicalRecord::setMedicalRecordsByRecordRange(const Date &startDate, const Date &endDate) const {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        Date recordDate = record.getDate();

        if (recordDate >= startDate && recordDate <= endDate) {
            records.push_back(record);
        }
    }
    return records;
}

void listMedicalRecord::addMedicalRecord(const MedicalRecord &record) {
    this->append(record);
    cout << "Thêm bệnh án thành công!" << endl;
}

int listMedicalRecord::checkRecordID(const string& recordID) {
    for (int i = 0; i < this->size(); i++) {
        if (this->get(i).getRecordID() == recordID) {
            return i;
        }
    }
    return -1;
}

bool listMedicalRecord::removeMedicalRecordByID(const string& recordID) {
    int index = this->checkRecordID(recordID);
    if (index == -1) {
        cout << "Không tìm thấy bệnh án với ID: " << recordID << endl;
        return false;
    }

    this->remove(index);
    cout << "Xóa bệnh án thành công!" << endl;
    return true;
}

void listMedicalRecord::updateMedicalRecordByID(const string& recordID) {
    int index = this->checkRecordID(recordID);
    if (index == -1) {
        cout << "Không tìm thấy bệnh án với ID: " << recordID << endl;
        return;
    }

    MedicalRecord currentRecord = this->get(index);
    string newDiagnosis;
    cout << "Nhập chẩn đoán mới: ";
    cin >> newDiagnosis;
    currentRecord.setDiagnosis(newDiagnosis);

    this->saveMedicalRecordToFile(index);
}

void listMedicalRecord::searchMedicalRecord(SearchField field, const string& value) {
    if (this->size() == 0) return;

    bool found = false;
    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        string fieldValue;

        switch (field) {
            case SearchField::RecordID:
                fieldValue = record.getRecordID();
                break;
            case SearchField::PatientID:
                fieldValue = record.getPatientID();
                break;
            case SearchField::Symptoms:
                fieldValue = record.getSymptoms();
                break;
        }

        if (fieldValue.find(value) != string::npos) {
            record.printMedicalRecordHorizontal();
            found = true;
        }
    }

    if (!found) {
        cout << "Không tìm thấy bệnh án phù hợp!" << endl;
    }
}

void listMedicalRecord::generateStatistics() {
    if (this->size() == 0) {
        cout << "Không có dữ liệu để thống kê!" << endl;
        return;
    }

    int totalRecords = this->size();
    map<string, int> diagnosisCount;
    map<string, int> symptomsCount;

    for (int i = 0; i < totalRecords; i++) {
        MedicalRecord record = this->get(i);
        string diagnosis = record.getDiagnosis();
        string symptoms = record.getSymptoms();

        diagnosisCount[diagnosis]++;
        istringstream iss(symptoms);
        string symptom;
        while (iss >> symptom) {
            symptomsCount[symptom]++;
        }
    }

    cout << "Tổng số bệnh án: " << totalRecords << endl;
    cout << "Số lượng chẩn đoán theo bệnh:" << endl;
    for (const auto& pair : diagnosisCount) {
        cout << "Chẩn đoán: " << pair.first << ", Số lượng: " << pair.second << endl;
    }

    cout << "Số triệu chứng phổ biến:" << endl;
    for (const auto& pair : symptomsCount) {
        cout << "Triệu chứng: " << pair.first << ", Số lượng: " << pair.second << endl;
    }
}

void listMedicalRecord::displayMostCommonSymptoms() const {
    if (this->size() == 0) {
        cout << "Không có dữ liệu để hiển thị!" << endl;
        return;
    }

    map<string, int> symptomsCount;

    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        string symptoms = record.getSymptoms();

        istringstream iss(symptoms);
        string symptom;
        while (iss >> symptom) {
            symptomsCount[symptom]++;
        }
    }

    string mostCommonSymptom;
    int maxCount = 0;

    for (const auto& pair : symptomsCount) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostCommonSymptom = pair.first;
        }
    }

    cout << "Triệu chứng phổ biến nhất: " << mostCommonSymptom << " (Số lượng: " << maxCount << ")" << endl;
}

void listMedicalRecord::displayDiagnosisCount() const {
    if (this->size() == 0) {
        cout << "Không có dữ liệu để hiển thị!" << endl;
        return;
    }

    map<string, int> diagnosisCount;

    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        string diagnosis = record.getDiagnosis();
        diagnosisCount[diagnosis]++;
    }

    cout << "Số lượng chẩn đoán theo bệnh:" << endl;
    for (const auto& pair : diagnosisCount) {
        cout << "Chẩn đoán: " << pair.first << ", Số lượng: " << pair.second << endl;
    }
}

