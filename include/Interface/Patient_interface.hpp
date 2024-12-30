#pragma once
#include <ftxui/component/component.hpp>          // for Button, Renderer, Input, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>
#include <Management/Appoinment.hpp>
#include <Management/Patient.hpp>
#include "Management/date.hpp"
#include "Management/listMedicalRecord.hpp"
#include "Management/listPatient.hpp"
#include "Management/listAppoinment.hpp"
#include "Management/listAccount.hpp"
#include "Header/Header.hpp"
#include <chrono>  // for system_clock
#include <iomanip> // for put_time
#include <ctime>   // for time_t
#include <io.h>
#include <fcntl.h>
#include <regex>
#include <ranges>
using namespace ftxui;
using namespace std::chrono;
// auto screen = ScreenInteractive::Fullscreen();

std::string FormatDate(const std::tm &date);
enum class Patient_State
{
  MainScreen,
  Info,
  Appoinment,
  View_appoinments,
  Prescription,
};

// extern Patient_State current_patient_state = Patient_State::MainScreen;
ButtonOption btn_style1();
ButtonOption btn_style2();
ButtonOption Btn_animated_opt1();
Component Wrap(std::string name, Component component);
bool validateDate(const std::string &date);
void Patientdisplay(Patient* &patient);
void P_Appoinment_info_UI(Patient &patient);
void Appoinment_UI(Patient &patient);
string Greeting(const std::string &name);
void Med_record_UI(Patient &patient);
void Patient_UI(Patient* &patient, listPatient &patients, listAccount &accounts, AccountUser* &current_account);
