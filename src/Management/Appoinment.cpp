#include <Management/Appoinment.hpp>

Appoinment::Appoinment()
{
    this->ID = "T01";
    this->date.setDate("01/11/2024");
    this->time = 0;
    this->Patient_ID = "";
    this->description = "NULL";
}
void Appoinment::copy(const Appoinment &other)
{
    this->ID = other.ID;
    this->date = other.date;
    this->time = other.time;
    this->Patient_ID = other.Patient_ID;
    this->description = other.description;
    this->status = other.status;
    this->isProcessed = other.isProcessed;
}
Appoinment::Appoinment(Patient &patient, const Date &date, int time, const string &description)
{
    this->Patient_ID = patient.getID_patient();
    this->date = date;
    this->time = time;
    this->description = description;
}
bool Appoinment::UpdateStatus(const bool &Status, const bool &isProcessed)
{
    map<string, vector<string>> lichKham;
    DocFileLich(lichKham);
    this->status = Status;
    this->isProcessed = isProcessed;
    for (string &lk : lichKham[this->getDate().getDate()])
    {
        if (lk.find(this->ID) == 0)
        {
            int pos = lk.length() - 1;
            lk.replace(pos - 2, 1, (this->status ? "1" : "0"));
            lk.replace(pos, 1, (this->isProcessed ? "1" : "0"));
            GhiFileLich(lichKham);
            return true;
        }
    }
    return false;
}

void Appoinment::setDate(Date date)
{
    this->date = date;
}
void Appoinment::setTime(int time)
{
    this->time = time;
}
void Appoinment::setPatientID(const Patient &patient)
{
    this->Patient_ID = patient.getID_patient();
}
void Appoinment::setDescription(const string &description)
{
    this->description = description;
}
// Chưa sử dụng!!!!!!!

void Appoinment::setID(const string &ID)
{
    this->ID = ID;
}

Appoinment::~Appoinment() {}
void Appoinment::DocFileLich(map<string, vector<string>> &lichKham)
{
    path file_path = DATA_PATH "AppoinmentDB";
    file_path.append(to_string(this->date.getYear()) + "_" + to_string(this->date.getMonth()) + ".txt");
    file_path = absolute(file_path);
    ifstream file(file_path);
    string line;
    string currentDate;

    while (getline(file, line))
    {
        if (line.empty() || line == "---")
            continue;

        // Nếu là dòng ngày mới
        if (line.find("/") != string::npos)
        {
            currentDate = line;
            lichKham[currentDate]; // Tạo vector trống nếu chưa có
        }
        else
        {
            // Thêm lịch vào danh sách của ngày hiện tại
            lichKham[currentDate].push_back(line);
        }
    }
    file.close();
}
void Appoinment::GhiFileLich(const map<string, vector<string>> &lichKham)
{
    path file_path = DATA_PATH "AppoinmentDB";
    file_path.append(to_string(this->date.getYear()) + "_" + to_string(this->date.getMonth()) + ".txt");
    file_path = absolute(file_path);
    ofstream file(file_path);
    for (const auto &entry : lichKham)
    {
        file << entry.first << endl;
        // cout << entry.first <<endl;
        for (const auto &lich : entry.second)
        {
            file << lich << endl;
            // cout << lich << endl;
        }
        file << "---" << endl;
        // cout << "---" << endl;
    }
    file.close();
}
void Appoinment::ThemLichKham(const string &hieuLuc, const string &trangThai)
{
    map<string, vector<string>> lichKham;
    DocFileLich(lichKham);
    const string ngay = this->date.getDate();
    const string maBenhNhan = this->Patient_ID;
    const string maGio = to_string(this->time);
    const string trieuChung = this->description;
    // Tạo ID tự động
    int soThuTu = lichKham[ngay].size() + 1;
    ostringstream idStream;
    idStream << ngay.substr(8, 2) << ngay.substr(3, 2) << ngay.substr(0, 2) << setw(3) << setfill('0') << soThuTu;
    string idLichKham = idStream.str();

    // Thêm lịch mới vào ngày tương ứng
    ostringstream lichMoi;
    lichMoi << idLichKham << ";" << maBenhNhan << ";" << maGio << ";" << trieuChung << ";" << hieuLuc << ";" << trangThai;
    lichKham[ngay].emplace_back(lichMoi.str());

    // Ghi lại file
    GhiFileLich(lichKham);
    // cout << "Lich kham voi ID: " << idLichKham << " da duoc tao thanh cong!" << endl;
    // cout << "Thông tin ghi trong file: " << lichMoi.str() << endl;
}
Appoinment &Appoinment::operator=(const Appoinment &app)
{
    this->ID = app.getID();
    this->date = app.getDate();
    this->time = app.getTime();
    this->Patient_ID = app.getPatientID();
    this->description = app.getDescription();
    this->status = app.getStatus();
    this->isProcessed = app.getIsProcessed();
    return *this;
}
struct tm to_tmDate(const std::string &date)
{
    struct tm tm = {};
    int dd, mm, yyyy;
    char delim1, delim2;

    std::istringstream iss(date);
    iss >> dd >> delim1 >> mm >> delim2 >> yyyy;

    if (iss.fail() || delim1 != '/' || delim2 != '/')
    {
        std::cerr << "Định dạng ngày không hợp lệ." << std::endl;
        return tm;
    }

    tm.tm_mday = dd;
    tm.tm_mon = mm - 1;       // Tháng trong struct tm từ 0-11
    tm.tm_year = yyyy - 1900; // Năm tính từ 1900

    return tm;
}

bool NamTrongKhoangThoiGian(const std::string &ngay, const struct tm &ngayBatDau, const struct tm &ngayKetThuc)
{
    struct tm ngayKiemTra = to_tmDate(ngay);
    time_t tKiemTra = mktime(&ngayKiemTra);
    time_t tBatDau = mktime(const_cast<struct tm *>(&ngayBatDau));
    time_t tKetThuc = mktime(const_cast<struct tm *>(&ngayKetThuc));

    return tKiemTra >= tBatDau && tKiemTra <= tKetThuc;
}

string GioKham(int time_slot)
{
    std::vector<std::string> time_slots = {
        "07:30 - 08:30", "08:30 - 09:30", "09:30 - 10:30", "10:30 - 11:30",
        "13:30 - 14:30", "14:30 - 15:30", "15:30 - 16:30", "16:30 - 17:00"};
    return time_slots[time_slot];
}
