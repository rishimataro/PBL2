#include "Management/listAppoinment.hpp"
// struct tm _to_tmDate(const std::string &date)
// {
//     struct tm tm = {};
//     int dd, mm, yyyy;
//     char delim1, delim2;

//     std::istringstream iss(date);
//     iss >> dd >> delim1 >> mm >> delim2 >> yyyy;

//     if (iss.fail() || delim1 != '/' || delim2 != '/')
//     {
//         std::cerr << "Định dạng ngày không hợp lệ." << std::endl;
//         return tm;
//     }

//     tm.tm_mday = dd;
//     tm.tm_mon = mm - 1;       // Tháng trong struct tm từ 0-11
//     tm.tm_year = yyyy - 1900; // Năm tính từ 1900

//     return tm;
// }
// bool inDateRange(const std::string &ngay, const struct tm &ngayBatDau, const struct tm &ngayKetThuc)
// {
//     struct tm ngayKiemTra = to_tmDate(ngay);
//     time_t tKiemTra = mktime(&ngayKiemTra);
//     time_t tBatDau = mktime(const_cast<struct tm *>(&ngayBatDau));
//     time_t tKetThuc = mktime(const_cast<struct tm *>(&ngayKetThuc));

//     return tKiemTra >= tBatDau && tKiemTra <= tKetThuc;
// }
listAppoinment::listAppoinment()
{
    readAppointmentsFromFile();
}

bool listAppoinment::readAppointmentsFromFile()
{
    string file_path = "../Database/AppoinmentDB/Appoinment.txt";
    fstream file;
    file.open(file_path, ios::in);
    if (!file.is_open())
        return false;
    string line;
    string curDate;
    LinkedList<Appoinment> curListApp;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (line.empty())
                continue;
            line.push_back(';');
            stringstream ss(line);
            string tmp;
            getline(ss, tmp, ';');
            string date_str = tmp.substr(6, 2) + "/" + tmp.substr(4, 2) + "/" + tmp.substr(0, 4);
            Date dd;
            dd.setDate(date_str);
            Appoinment *app = new Appoinment();
            app->setDate(dd);
            app->setID(tmp);
            getline(ss, tmp, ';');
            app->setPatientID(tmp);
            getline(ss, tmp, ';');
            app->setTime(stoi(tmp));
            getline(ss, tmp, ';');
            app->setStatus(stoi(tmp));
            getline(ss, tmp, ';');
            app->setIsProcessed(stoi(tmp));
            getline(ss, tmp, ';');
            app->setDescription(tmp);

            this->operator[](dd).append(app);
            
        }
    }
            file.close();
            return true;
}

bool listAppoinment::writeAppointmentsToFile()
{
    string file_path = "../Database/AppoinmentDB/Appoinment.txt";
    fstream file;
    file.open(file_path, ios::out);
    if (!file.is_open())
    {
        return false;
    }
    
    for(auto it = this->begin(); it!= this->end(); ++it)
    {
        
        for(int i = 0; i < it->second.size(); i++)
        {
            file << it->second.get(i)->getID() << ";";
            file << it->second.get(i)->getPatientID() << ";";
            file << it->second.get(i)->getTime() << ";";
            file << it->second.get(i)->getStatus() << ";";
            file << it->second.get(i)->getIsProcessed() << ";";
            file << it->second.get(i)->getDescription();
            file << "\n";
        }
    }
    file.close();
    return true;
}

void listAppoinment::addAppointment(Appoinment* &app)
{
    if(!count(app->getDate()))
    {
        LinkedList<Appoinment> temp_list;
        Date date = app->getDate();
        string month =((date.getMonth() < 10) ? "0" : "") + to_string(date.getMonth());
        // string month = to_string(date.getMonth());
        string day =((date.getDay() < 10) ? "0" : "") + to_string(date.getDay());
        // string day = to_string(date.getDay());
        string ID  = to_string(date.getYear()) + month + day + "001";
        app->setID(ID);
        // temp_list.append(app);
        this->operator[](date).append(app);
    }else
    {
        Date date = app->getDate();
        string month =(date.getMonth() < 10 ? "0" : "") + to_string(date.getMonth());
        string day =(date.getDay() < 10 ? "0" : "") + to_string(date.getDay());
        string ID  = to_string(date.getYear()) + month + day;
        string number = to_string(this->operator[](date).size() + 1);
        number = string(3 - number.length(), '0') + number;
        ID += number;
        app->setID(ID);
        this->operator[](date).append(app);
        // ofstream out("D:\\Test_Code\\PBL\\PBL2\\build\\test_log1.txt", ios::out);

        // out << count(app->getDate()) << endl;
        // out.close();

    }
    this->writeAppointmentsToFile();
}
vector<Appoinment*> listAppoinment::getAppointmentsByDateRange(const string &startDate, const string &endDate)
{
    Date start_date, end_date;
    vector<Appoinment*> result;
    start_date.setDate(startDate);
    end_date.setDate(endDate);
    auto start = this->lower_bound(start_date);
    auto end = this->upper_bound(end_date);
    for (auto it = start; it!= end; ++it)
    {
        for (int i = 0; i < it->second.size(); i++)
        {   
            auto x = it->second.get(i);
            result.push_back(x);
        }
    }
    return result;
}

vector<Appoinment*> listAppoinment::getAppointmentsByPatientIDIRange(const string &patientID, const string &startDate, const string &endDate)
{
    vector<Appoinment*> range = getAppointmentsByDateRange(startDate, endDate);
    vector<Appoinment*> result;
    for (int i = 0; i < range.size(); i++)
    {
        auto x = range[i];
        if (x->getPatientID() == patientID)
        {
            result.push_back(x);
        }
    }
    return result;
}
bool listAppoinment::updateAppoinmentStatus(const string &ID, const bool &status, const bool &isProcessed)
{
    Date date;
    date.setYear(stoi(ID.substr(0, 4)));
    date.setMonth(stoi(ID.substr(4, 2)));
    date.setDay(stoi(ID.substr(6, 2)));
    auto it = this->find(date);
    if (it!= this->end())
    {
        for (int i = 0; i < it->second.size(); i++)
        {
            auto x = it->second.get(i);
            if ((x)->getID() == ID)
            {
                (x)->setStatus(status);
                (x)->setIsProcessed(isProcessed);
                this->writeAppointmentsToFile();
                return true;
            }
        }
    }
    return false;
}