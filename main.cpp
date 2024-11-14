// #include "./Management/Single/Account.h"
// #include "./Management/Single/Date.h"
// #include "./Management/Single/Patient.h"
// #include "./Management/listAccount.h"
#include <ftxui/component/component.hpp>        // for Button, Renderer, Input, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>
// #include <Management/Appoinment.hpp>
#include <Management/listPatient.hpp>
#include <Management/Patient.hpp>
#include <Management/Account.hpp>
#include <Management/listAccount.hpp>
// #include <Interface/Patient_interface.hpp>
// #include <fstream>
// #include <iostream>
// #include <windows.h>
// #include <filesystem>
using namespace std;
// using namespace filesystem;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    listPatient list;
    list.readListPatientFromFile();

    vector<Patient> result = list.setPatientByBirthRange("01/01/1999", "01/01/2007");
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i].getFullName() << endl;
    }

    system("pause");
    return 0;
}