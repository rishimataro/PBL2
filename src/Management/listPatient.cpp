#include <Management/listPatient.hpp>

//* Constructor & Destructor
listPatient::listPatient()
{
    this->head = NULL;
}

listPatient::~listPatient()
{
    if (this->head == NULL)
        return;

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

//* Read & Write
bool listPatient::readListPatientFromFile()
{
    string file_path = "../Database/PatientDB/patient.txt";
    fstream fin, patientFile;
    Patient patient;

    fin.open(file_path, ios::in);
    if (!fin.is_open())
        return false;

    string id;
    while (getline(fin, id))
    {
        if (id.empty())
            continue;

        file_path = "../Database/PatientDB/" + id + ".txt";
        patientFile.open(file_path, ios::in);

        if (!patientFile.is_open())
            continue;

        patient.readPatientFromFile(patientFile);
        this->append(patient);

        patientFile.close();
    }
    fin.close();
    return true;
}

bool listPatient::writeListPatientToFile(bool check)
{
    string file_path = "../Database/PatientDB/patient.txt";
    char ch;

<<<<<<< HEAD
    ofstream fo;
    if (check)
    {
        fo.open(file_path, ios::trunc); 
    }
    else
    {
        fo.open(file_path, ios::app);  
    }

=======
    ifstream fi(file_path);
    if (fi.is_open())
    {
        fi.seekg(-1, ios::end);
        fi.get(ch);
        if (ch != '\n' && ch != '\0')
        {
            ofstream temp(file_path, ios::app);
            temp << "\n";
            temp.close();
        }
        fi.close();
    }

    ofstream fo(file_path, ios::app);
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
    if (!fo.is_open())
        return false;

    Patient patient;
    if (check)
    {
        for (int i = 0; i < this->size(); i++)
        {
            patient = this->get(i);
            patient.writePatientToFile_all(fo);
        }
    }
    else
    {
        patient = this->get(this->size() - 1);
        patient.writePatientToFile_all(fo);
    }

    fo.close();

    return true;
}

bool listPatient::writePatientToFile(int index)
{
    string path = "../Database/PatientDB/";
    string fileName = path + this->get(index).getID_patient() + ".txt";

    fstream fout;
    fout.open(fileName, ios::out);

    if (!fout.is_open())
    {
        return false;
    }

    this->get(index).writePatientToFile(fout);
    fout.close();
    return true;
}

//* Setter & Getter
vector<Patient> listPatient::setPatientByGender(bool gender)
{
    vector<Patient> result;
    if (this->size() == 0)
        return result;

    for (int i = 0; i < this->size(); i++)
    {
        Patient patient = this->get(i);
        if (patient.getGender() == gender)
        {
            result.push_back(patient);
        }
    }
    return result;
}

vector<Patient> listPatient::setPatientByBirthRange(const string &startDate, const string &endDate)
{
    vector<Patient> result;
    if (this->size() == 0)
        return result;

    Date startDateObj, endDateObj;
    startDateObj.setDate(startDate);
    endDateObj.setDate(endDate);

    int left = 0, right = this->size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        Date birthDate = this->get(mid).getDayOfBirth();

        if (birthDate >= startDateObj && birthDate <= endDateObj)
        {
            result.push_back(this->get(mid));

            int temp = mid - 1;
            while (temp >= left && this->get(temp).getDayOfBirth() >= startDateObj && this->get(temp).getDayOfBirth() <= endDateObj)
            {
                result.push_back(this->get(temp));
                temp--;
            }
            temp = mid + 1;
            while (temp <= right && this->get(temp).getDayOfBirth() >= startDateObj && this->get(temp).getDayOfBirth() <= endDateObj)
            {
                result.push_back(this->get(temp));
                temp++;
            }
            break;
        }
<<<<<<< HEAD

        if (birthDate < startDateObj)
            left = mid + 1;
        else
            right = mid - 1;
    }
=======

        if (birthDate < startDateObj)
            left = mid + 1;
        else
            right = mid - 1;
    }

>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
    return result;
}

vector<Patient> listPatient::setAllPatient()
{
    vector<Patient> result;
    if (this->size() == 0)
        return result;

    result.reserve(this->size());
    for (int i = 0; i < this->size(); i++)
    {
        result.push_back(this->get(i));
    }
    return result;
}

//* Add
void listPatient::addPatient(const string &newFullName, const string &newPhone, const string &newDayOfBirth, const string &newCCCD, const string &newGender, const string &newAddress)
{
    Patient newPatient;

    newPatient.setID_patient();
    newPatient.setFullName(newFullName);
    newPatient.setPhone(newPhone);
    newPatient.setDayOfBirth(newDayOfBirth);
    newPatient.setCCCD(newCCCD);

    newPatient.setGender(newGender == "Nữ");
    newPatient.setAddress(newAddress);

    this->append(newPatient);
    this->writePatientToFile(this->size() - 1);
    this->writeListPatientToFile(false);

    return;
}

//* Check
int listPatient::checkID(const string &ID)
{
    int left = 0, right = this->size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        string midID = this->get(mid).getID_patient();
        if (midID == ID)
            return mid;
        if (midID < ID)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

//* Delete
void listPatient::removePatientByID(const string &ID)
{
    Node<Patient> *current = this->head;
    if (current == NULL)
        return;

    int index = this->checkID(ID);
    if (index == 0)
        return;

    this->remove(index);

    return;
}

//* Update
void listPatient::updatePatientByID(const string &ID, const string &newFullName, const string &newPhone, const string &newDayOfBirth, const string &newCCCD, const string &newGender, const string &newAddress)
{
    Node<Patient> *current = this->head;
    if (current == NULL)
        return;

    int index = this->checkID(ID);
    if (index == 0)
        return;

    Patient currentPatient = this->get(index);
    string file_path = "../Database/PatientDB/" + currentPatient.getID_patient() + ".txt";
    if (std::remove(file_path.c_str()) != 0)
        return;

    currentPatient.setFullName(newFullName);
    currentPatient.setPhone(newPhone);
    currentPatient.setDayOfBirth(newDayOfBirth);
    currentPatient.setCCCD(newCCCD);
    currentPatient.setGender(newGender == "Nữ");
    currentPatient.setAddress(newAddress);

    this->set(index, currentPatient);
    this->writePatientToFile(index);
    return;
}

//* Search
vector<Patient> listPatient::searchPatient(SearchField field, const string &value)
{
<<<<<<< HEAD
    vector<Patient> result;
    if (this->size() == 0)
        return result;

    string lowerValue = toLowerCase(value);
    int left = 0, right = this->size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        string fieldValue;
        switch (field)
        {
        case SearchField::ID:
            fieldValue = toLowerCase(this->get(mid).getID_patient());
            break;
        case SearchField::FullName:
            fieldValue = toLowerCase(this->get(mid).getFullName());
            break;
        case SearchField::CCCD:
            fieldValue = toLowerCase(this->get(mid).getCCCD());
            break;
        }

        if (fieldValue.find(lowerValue) == 0)
        {
            result.push_back(this->get(mid));
            int temp = mid - 1;
            while (temp >= left && toLowerCase(this->get(temp).getID_patient()).find(lowerValue) == 0)
            {
                result.push_back(this->get(temp));
                temp--;
            }
            temp = mid + 1;
            while (temp <= right && toLowerCase(this->get(temp).getID_patient()).find(lowerValue) == 0)
            {
                result.push_back(this->get(temp));
                temp++;
            }
            break;
        }

        if (fieldValue < lowerValue)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return result;
}
=======
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
// vector<Patient> listPatient::searchPatient(SearchField field, const string &value)
// {
//     vector<Account> result;
//     if(this->size() == 0) return result;
//     string lowerValue = toLowerCase(value);

//     if (field == SearchField::ID)
//     {
//         for (const auto &entry : idMap)
//         {
//             string fieldValue = toLowerCase(entry.first);
//             if (fieldValue.find(lowerValue) == 0)  
//             {
//                 result.push_back(entry.second);
//             }
//         }
//     }
//     else if (field == SearchField::UserName)
//     {
//         for (const auto &entry : userNameMap)
//         {
//             string fieldValue = toLowerCase(entry.first); 
//             if (fieldValue.find(lowerValue) == 0)     
//             {
//                 result.push_back(entry.second);
//             }
//         }
//     }

//     return result;
// }
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
