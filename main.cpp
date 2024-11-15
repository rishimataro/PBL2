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

    // Kiểm tra nếu danh sách ban đầu rỗng
    if (listMR.size() == 0)
        std::cout << "Test 1: Danh sách rỗng.\n";
    else
        std::cout << "Test 1: Danh sách không rỗng.\n";

    // Kiểm tra đọc bản ghi y tế từ file
    bool readSuccess = listMR.readListMedicalRecordFromFile();
    if (readSuccess)
        std::cout << "Test 2: Đọc bản ghi y tế từ file thành công.\n";
    else
        std::cout << "Test 2: Đọc bản ghi y tế từ file thất bại.\n";

    

    system("pause");
    return 0;
}
