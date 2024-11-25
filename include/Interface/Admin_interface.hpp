#pragma once
#include <ftxui/component/component.hpp>        // for Button, Renderer, Input, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>      
#include <string>
#include <regex>
#include "Interface/Patient_interface.hpp"
#include "Management/Patient.hpp"
#include "Management/listPatient.hpp"
using namespace std;
using namespace ftxui;

// bool validateDate(const std::string& date_);
void Analyse_UI();
void QLBA_UI();
void QLBN_UI();
void Admin_UI();