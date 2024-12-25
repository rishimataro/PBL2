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
void test()
{
    listMedicalRecord listMR;
    cout << "1" << endl;
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // loginUI();
    Admin_UI();

    // listMedicalRecord listMR;
    // listAccount lspt;
    // listPatient listpatient;

    // // Kiểm tra nếu danh sách ban đầu rỗng
    // if (listMR.size() == 0)
    //     std::cout << "Test 1: Danh sách rỗng.\n";
    // else
    //     std::cout << "Test 1: Danh sách không rỗng.\n";

    // // Kiểm tra đọc bản ghi y tế từ file
    // bool readSuccess = listMR.readListMedicalRecordFromFile();
    // if (readSuccess)
    //     std::cout << "Test 2: Đọc bản ghi y tế từ file thành công.\n";
    // else
    //     std::cout << "Test 2: Đọc bản ghi y tế từ file thất bại.\n";

    // if (listMR.size() == 0)
    //     std::cout << "Test 3: Danh sách rỗng.\n";
    // else
    //     std::cout << "Test 3: Danh sách không rỗng.\n";
    // vector<MedicalRecord> mrList = listMR.searchMedicalRecord(SearchField_MR::PatientID, "P3");
    // if (mrList.size() == 0)
    //     std::cout << "Test 4: Danh sách tìm kiếm rỗng.\n";
    // else
    //     std::cout << "Test 4: Danh sách tìm kiếm không rỗng.\n";
    // cout << mrList[0].getID_patient() << endl;
    // system("pause");
    return 0;
}
// // Copyright 2023 Arthur Sonzogni. All rights reserved.
// // Use of this source code is governed by the MIT license that can be found in
// // the LICENSE file.
// #include <ftxui/component/component.hpp>
// #include <ftxui/component/screen_interactive.hpp>

// using namespace ftxui;

// Component DummyWindowContent() {
//   class Impl : public ComponentBase {
//    private:
//     bool checked[3] = {false, false, false};
//     float slider = 50;

//    public:
//     Impl() {
//       Add(Container::Vertical({
//           Checkbox("Check me", &checked[0]),
//           Checkbox("Check me", &checked[1]),
//           Checkbox("Check me", &checked[2]),
//           Slider("Slider", &slider, 0.f, 100.f),
//       }));
//     }
//   };
//   return Make<Impl>();
// }

// int main() {
//   int window_1_left = 20;
//   int window_1_top = 10;
//   int window_1_width = 40;
//   int window_1_height = 20;
//     bool checked[3] = {false, false, false};
//     float slider = 50;
//     Component xx = Container::Vertical({
//           Checkbox("Check me", &checked[0]),
//           Checkbox("Check me", &checked[1]),
//           Checkbox("Check me", &checked[2]),
//           Slider("Slider", &slider, 0.f, 100.f),
//           Renderer([&]{
//             return text("Hello, world!");
//           }),
//           Button("Dummy button", [&]{}, ButtonOption::Animated()),
//       });
//   auto window_1 = Window({
//       .inner = xx,
//       .title = "First window",
//       .left = &window_1_left,
//       .top = &window_1_top,
//       .width = &window_1_width,
//       .height = &window_1_height,
//   });

//   auto window_2 = Window({
//       .inner = DummyWindowContent(),
//       .title = "My window",
//       .left = 40,
//       .top = 20,
//   });

//   auto window_3 = Window({
//       .inner = DummyWindowContent(),
//       .title = "My window",
//       .left = 60,
//       .top = 30,
//   });

//   auto window_4 = Window({
//       .inner = DummyWindowContent(),
//   });

//   auto window_5 = Window({});

//   auto window_container = Container::Stacked({
//       window_1,
//       window_2,
//       window_3,
//       window_4,
//       window_5,
//   });

//   auto display_win_1 = Renderer([&] {
//     return text("window_1: " +  //
//                 std::to_string(window_1_width) + "x" +
//                 std::to_string(window_1_height) + " + " +
//                 std::to_string(window_1_left) + "," +
//                 std::to_string(window_1_top));
//   });

//   auto layout = Container::Vertical({
//       display_win_1,
//       window_container,
//   });

//   auto screen = ScreenInteractive::Fullscreen();
//   screen.Loop(layout);

//   return EXIT_SUCCESS;
// }
