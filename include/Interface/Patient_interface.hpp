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
using namespace std::chrono;
// auto screen = ScreenInteractive::Fullscreen();
std::string FormatDate(const std::tm& date);
enum class Patient_State {
  MainScreen,
  Info,
  Appoinment,
  View_appoinments,
  Prescription,
};

// extern Patient_State current_patient_state = Patient_State::MainScreen;
ButtonOption btn_style1();
ButtonOption btn_style2();
Component Wrap(std::string name, Component component);
bool ValidateDate(const std::string& date);
void Patientdisplay(Patient& patient);
void Appoinment_UI(Patient& patient);
string Greeting(const std::string& name);
void Patient_UI(Patient& patient);
