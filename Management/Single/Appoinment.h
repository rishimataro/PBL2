#include "./Date.h"
#include "./Patient.h"
#include "../../Library/Filelib.h"
#include "../../Library/Graphics.h"
#include <filesystem>
using namespace filesystem;

class Appoinment
{
private:
    string ID;
    Date date;
    int time;//second
    string Patient_ID;
    string description;
public:
    Appoinment(/* args */);
    void setDate(Date date);
    void setTime(int time);
    void setPatientID(const Patient& patient);
    void setDescription(const string& description);
    //Chưa sử dụng!!!!!!!
    void readFromFile();
    bool setID();
    bool writeToFile();
    // void readFromFile(ifstream& file);

    ~Appoinment();
};

void printCalendar(int month, int year);
void AppoinmentUI();
