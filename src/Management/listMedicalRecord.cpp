#include "./listMedicalRecord.h"

//* Constructor & Destructor  
listMedicalRecord::listMedicalRecord() {
    this->head = NULL;  // Khởi tạo danh sách rỗng
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

//* Setter & Getter
void listMedicalRecord::setListMedicalRecordByFile() {
    fstream fin;
    fin.open("./Database/MedicalRecordDB/medicalRecords.txt", ios::in);

    if (!fin.is_open())
        return;

    string line;
    while (getline(fin, line)) {
        if (line.empty())
            continue;

        MedicalRecord record;
        record.setMedicalRecord(line); // Cần định nghĩa hàm setMedicalRecord trong lớp MedicalRecord
        this->addMedicalRecord(record);
    }
    fin.close();
}

void listMedicalRecord::saveListMedicalRecordToFile() {
    fstream fout;
    fout.open("./Database/MedicalRecordDB/medicalRecords.txt", ios::out);

    if (!fout.is_open())
        return;

    for (int i = 0; i < this->size(); i++) {
        this->get(i).saveAllMedicalRecord(fout); // Cần định nghĩa hàm saveAllMedicalRecord trong lớp MedicalRecord
    }

    fout.close();
    cout << "Lưu thành công!" << endl;
}

void listMedicalRecord::saveMedicalRecordToFile(int index) {
    string path = "./Database/MedicalRecordDB/";
    string fileName = path + this->get(index).getRecordID() + ".txt"; // Cần định nghĩa hàm getRecordID trong lớp MedicalRecord
    fstream fout;
    fout.open(fileName, ios::out);

    if (!fout.is_open()) {
        return;
    }

    this->get(index).saveMedicalRecord(fout); // Cần định nghĩa hàm saveMedicalRecord trong lớp MedicalRecord
    fout.close();
}

//* Display
void listMedicalRecord::printAllMedicalRecords() const {
    if (this->size() == 0) return;

    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        record.printMedicalRecordHorizontal(); // Cần định nghĩa hàm printMedicalRecordHorizontal trong lớp MedicalRecord
        cout << "------------------------" << endl;
    }
}

void listMedicalRecord::printMedicalRecordsByPatientID(const string& patientID) const {
    if (this->size() == 0) return;

    bool found = false;
    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        if (record.getPatientID() == patientID) { // Cần định nghĩa hàm getPatientID trong lớp MedicalRecord
            record.printMedicalRecordHorizontal();
            found = true;
        }
    }

    if (!found) {
        cout << "Không tìm thấy bệnh án cho bệnh nhân ID: " << patientID << endl;
    }
}

void listMedicalRecord::printMedicalRecordsByDiagnosis(const string& diagnosis) const {
    if (this->size() == 0) return;

    bool found = false;
    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        if (record.getDiagnosis() == diagnosis) { // Cần định nghĩa hàm getDiagnosis trong lớp MedicalRecord
            record.printMedicalRecordHorizontal();
            found = true;
        }
    }

    if (!found) {
        cout << "Không tìm thấy bệnh án với chẩn đoán: " << diagnosis << endl;
    }
}

void listMedicalRecord::printMedicalRecordsByRecordRange(const Date &startDate, const Date &endDate) const {
    if (this->size() == 0) return;

    bool found = false;
    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        Date recordDate = record.getDate(); // Cần định nghĩa hàm getDate trong lớp MedicalRecord

        if (recordDate >= startDate && recordDate <= endDate) {
            record.printMedicalRecordHorizontal();
            found = true;
        }
    }

    if (!found) {
        cout << "Không tìm thấy bệnh án trong khoảng thời gian này." << endl;
    }
}

//* Add
void listMedicalRecord::addMedicalRecord(const MedicalRecord &record) {
    this->append(record); // Cần đảm bảo hàm append đã được định nghĩa trong lớp LinkedList
    cout << "Thêm bệnh án thành công!" << endl;
}

//* Check
int listMedicalRecord::checkRecordID(const string& recordID) {
    for (int i = 0; i < this->size(); i++) {
        if (this->get(i).getRecordID() == recordID) { // Cần định nghĩa hàm getRecordID trong lớp MedicalRecord
            return i;
        }
    }
    return -1; // Trả về -1 nếu không tìm thấy
}

//* Delete
void listMedicalRecord::removeMedicalRecordByID(const string& recordID) {
    int index = this->checkRecordID(recordID);
    if (index == -1) {
        cout << "Không tìm thấy bệnh án với ID: " << recordID << endl;
        return;
    }

    this->remove(index); // Cần đảm bảo hàm remove đã được định nghĩa trong lớp LinkedList
    cout << "Xóa bệnh án thành công!" << endl;
}

//* Update
void listMedicalRecord::updateMedicalRecordByID(const string& recordID) {
    int index = this->checkRecordID(recordID);
    if (index == -1) {
        cout << "Không tìm thấy bệnh án với ID: " << recordID << endl;
        return;
    }

    MedicalRecord currentRecord = this->get(index);
    // Thực hiện cập nhật thông tin cho currentRecord...
    // Ví dụ:
    string newDiagnosis;
    cout << "Nhập chẩn đoán mới: ";
    cin >> newDiagnosis;
    currentRecord.setDiagnosis(newDiagnosis); // Cần định nghĩa hàm setDiagnosis trong lớp MedicalRecord

    this->saveMedicalRecordToFile(index); // Lưu lại thông tin bệnh án đã cập nhật
}

//* Search
void listMedicalRecord::searchMedicalRecord(SearchField field, const string& value) {
    if (this->size() == 0) return;

    bool found = false;
    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        string fieldValue;

        switch (field) {
            case SearchField::RecordID:
                fieldValue = record.getRecordID(); // Cần định nghĩa hàm getRecordID trong lớp MedicalRecord
                break;
            case SearchField::PatientID:
                fieldValue = record.getPatientID(); // Cần định nghĩa hàm getPatientID trong lớp MedicalRecord
                break;
            case SearchField::Symptoms:
                fieldValue = record.getSymptoms(); // Cần định nghĩa hàm getSymptoms trong lớp MedicalRecord
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

//* Statistics
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
        string diagnosis = record.getDiagnosis(); // Cần định nghĩa hàm getDiagnosis trong lớp MedicalRecord
        string symptoms = record.getSymptoms(); // Cần định nghĩa hàm getSymptoms trong lớp MedicalRecord

        diagnosisCount[diagnosis]++;
        // Tách triệu chứng thành từng phần và đếm
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
        string symptoms = record.getSymptoms(); // Cần định nghĩa hàm getSymptoms trong lớp MedicalRecord

        istringstream iss(symptoms);
        string symptom;
        while (iss >> symptom) {
            symptomsCount[symptom]++;
        }
    }

    // Tìm triệu chứng phổ biến nhất
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
        string diagnosis = record.getDiagnosis(); // Cần định nghĩa hàm getDiagnosis trong lớp MedicalRecord
        diagnosisCount[diagnosis]++;
    }

    cout << "Số lượng chẩn đoán theo bệnh:" << endl;
    for (const auto& pair : diagnosisCount) {
        cout << "Chẩn đoán: " << pair.first << ", Số lượng: " << pair.second << endl;
    }
}

