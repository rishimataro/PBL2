#include <ftxui/component/component.hpp>        // for Button, Renderer, Input, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>
#include <Management/Appoinment.hpp>
#include <Management/Patient.hpp>
#include <chrono>                               // for system_clock
#include <iomanip>                              // for put_time
#include <ctime>                                // for time_t
#include <io.h>
#include <fcntl.h>
#include <regex>
using namespace ftxui;
using namespace std;

// vector<wstring> days_of_week = {L"CN", L"Hai", L"Ba", L"Tư", L"Năm", L"Sáu", L"Bảy"};
// // Tạo các nút giờ
// vector<wstring> time_slots = {
//     L"07:30 - 08:30", L"08:30 - 09:30", L"09:30 - 10:30", L"10:30 - 11:30",
//     L"13:30 - 14:30", L"14:30 - 15:30", L"15:30 - 16:30", L"16:30 - 17:00"
// };
// auto screen = ScreenInteractive::Fullscreen();

wstring FormatDate(const tm& date);
enum class Patient_State {
  MainScreen,
  Info,
  Appoinment,
  View_appoinments,
  Prescription,
  Logout,
};

// extern Patient_State current_patient_state = Patient_State::MainScreen;
ButtonOption btn_style1();
Component Wrap(string name, Component component);
bool ValidateDate(const string& date);
Component Patientdisplay(Patient& patient);
void Patient_UI(Patient& patient);
