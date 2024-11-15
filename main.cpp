// #include "./Management/Single/Account.h"
// #include "./Management/Single/Date.h"
// #include "./Management/Single/Patient.h"
// #include "./Management/listAccount.h"
#include <ftxui/component/component.hpp>          // for Button, Renderer, Input, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>
// #include <Management/Appoinment.hpp>
#include <Management/listPatient.hpp>
#include <Management/Patient.hpp>
#include <Management/listMedicalRecord.hpp>
#include <Management/MedicalRecord.hpp>
// #include "Interface/Patient_interface.hpp"
#include "Management/Date.hpp"
#include "Interface/Login.hpp"
// #include <fstream>
// #include <iostream>
// #include <windows.h>
#include <filesystem>
#include <string>
using namespace std;
// using namespace filesystem;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    listMedicalRecord listMR;
    listMR.loadSymptomSolutionsFromFile();

    cout << "Danh sách triệu chứng và giải pháp sau khi tải từ file:\n";
    for (const auto& entry : listMR.getSymptomSolutions()) {
        cout << "Triệu chứng: " << entry.first << ", Giải pháp: " << entry.second << "\n";
    }
    cout << "------------------------------------------------------------\n";

    cout << "Diagnosis: Sốt => " << listMR.analyzeDiagnosisAndProvideSolutions("Sốt") << endl;
    cout << "Diagnosis: Ho khan => " << listMR.analyzeDiagnosisAndProvideSolutions("Ho khan") << endl;
    system("pause");
    return 0;
}
