#include <Management/listPatient.hpp>

//* Constructor & Destructor  
listPatient::listPatient() {
    this->head = NULL;
}

listPatient::~listPatient() {
    if(this->head == NULL) return;
    
    Node<Patient> *current = this->head;
    Node<Patient> *tail = this->head->prev;

    do
    {
        Node<Patient> *temp = current;
        current = current->next;
        delete temp;
    } while (current != head);

    this->head = NULL;
}

//* Setter & Getter
void listPatient::setListPatientByFile() {
    fstream fin;
    fin.open("./Database/PatientDB/patient.txt", ios::in);

    if (!fin.is_open())
        return;

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        Patient patient;
        cout << 1 << endl;
        patient.setPatient(line);
        this->append(patient);
    }
    fin.close();
}

void listPatient::saveListPatientToFile() {
    fstream fout;
    fout.open("./Database/PatientDB/patient.txt", ios::out);

    if (!fout.is_open())
        return;

    for (int i = 0; i < this->size(); i++)
    {
        this->get(i).saveAllPatient(fout);
    }

    fout.close();
    cout << "Lưu thành công!" << endl;
}

void listPatient::savePatientToFile(int index) {
    string path = "./Database/PatientDB/";
    string fileName = path + this->get(index).getID_patient() + ".txt";
    fstream fout;
    fout.open(fileName, ios::out);

    if (!fout.is_open()) {
        return;
    }

    this->get(index).savePatient(fout);
    fout.close();
}

//* Display
void listPatient::printPatientByGender(bool gender) const {
    if(this->size == 0) return;
    string gender_str = gender ? "Nữ" : "Nam";

    for(int i = 0; i < this->size; i++) {
        Patient patient = this->get(i); 
        if(patient.getGenderToString() == gender_str) {
            cout << "ID: " << patient.getID_patient() << endl;
            cout << "Họ tên: " << patient.getFullName() << endl;
            cout << "SĐT: " << patient.getPhone() << endl;
            cout << "Ngày sinh: " << patient.getDayOfBirth().getDate() << endl;
            cout << "CCCD: " << patient.getCCCD() << endl;
            cout << "Giới tính: " << gender_str << endl;
            cout << "Địa chỉ: " << patient.getAddress() << endl;
            cout << "------------------------" << endl;
        }
    }   
}


void listPatient::printPatientByBirthRange(const string &startDate, const string &endDate) {
    if (this->size() == 0) return;

    Patient patient;
    Date birthDate;

    Date startDateObj, endDateObj;
    startDateObj.setDate(startDate);
    endDateObj.setDate(endDate);

    cout << "Danh sách bệnh nhân có ngày sinh từ " << startDate << " đến " << endDate << endl;

    bool found = false;
    for (int i = 0; i < this->size(); i++) {
        patient = this->get(i);
        birthDate = patient.getDayOfBirth();

        if (birthDate >= startDateObj && birthDate <= endDateObj) {
            patient.printPatientHorizontal();
            found = true;
        }
    }

    if (!found) {
        cout << "Không tìm thấy bệnh nhân nào trong khoảng ngày sinh này." << endl;
    }
}

void listPatient::printAllPatient() const {
    if (this->size() == 0) return;

    for(int i = 0; i < this->size; i++) {
        Patient patient = this->get(i);
        patient.printPatientHorizontal();
        cout << "------------------------" << endl;
    }   
}

//* Add
void listPatient::addPatient(const Patient &patient) {
    this->append(patient);
    cout << "Thêm thành công!" << endl;
}

//* Check
int listPatient::checkID(const string& ID) {
    for (int i = 0; i < this->size(); i++)
    {
        if (this->get(i).getID_patient() == ID)
            return i;
    }
    return 0;
}


//* Delete
void listPatient::removePatientByID(const string& ID) {
    Node<Account> *current = this->head;
    if (current == NULL)
        return;
    
    int index = this->checkID(ID);
    if (index == 0)
        return;
    
    this->remove(index);
    cout << "Xóa thành công!" << endl;
    return;
}

//* Update
void listPatient::updatePatientByID(const string& ID) {
    Node<Account> *current = this->head;
    if (current == NULL)
        return;
    
    int index = this->checkID(ID);
    if (index == 0)
        return;
    
    Patient currentPatient = this->get(index);
    string newFullName, newPhone, newDayOfBirth, newCCCD, newgender, newAddress;

    cout << "Họ tên: "; cin >> newFullName;
    cout << "SĐT: "; cin >> newPhone;
    cout << "Ngày sinh: "; cin >> newDayOfBirth;    
    cout << "CCCD: "; cin >> newCCCD;    
    cout << "Giới tính: "; cin >> newgender;    
    cout << "Địa chỉ: "; cin.ignore(); getline(cin, newAddress);

    currentPatient.setFullName(newFullName);
    currentPatient.setPhone(newPhone);
    currentPatient.setDayOfBirth(newDayOfBirth);
    currentPatient.setCCCD(newCCCD);
    currentPatient.setGender(newGender);
    currentPatient.setAddress(newAddress);

    this->savePatientToFile(index);
    return;
}

//* Search
string toLowerCase(const string &str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
void listPatient::searchPatient(SearchField field, const string &value)
{
    if (this->size() == 0) return;

    bool found = false;
    string lowerValue = toLowerCase(value);
    string fieldValue;

    for (int i = 0; i < this->size(); i++)
    {
        switch (field)
        {
            case SearchField::ID:
                fieldValue = toLowerCase(this->get(i).getID_patient());
                break;
            case SearchField::FullName:
                fieldValue = toLowerCase(this->get(i).getFullName());
                break;
            case SearchField::CCCD:
                fieldValue = toLowerCase(this->get(i).getCCCD());
                break;
        }

        if (fieldValue.find(lowerValue) == 0)
        {
            this->get(i).printPatientHorizontal();
            found = true;
        }
    }

    if (!found)
    {
        cout << "Không tìm thấy bệnh nhân phù hợp!" << endl;
    }
}