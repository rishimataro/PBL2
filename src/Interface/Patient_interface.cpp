#include <Interface/Patient_interface.hpp>

int safe_stoi(const string &str) {
    try {
        return stoi(str);
    } catch (const invalid_argument& e) {
        cerr << "Lỗi: Chuỗi không hợp lệ để chuyển đổi thành số nguyên: " << e.what() << endl;
        return 0;
    }
}

wstring FormatDate(const tm& date) {
    wstringstream ss;
    ss << put_time(&date, L"%d/%m");
    return ss.str();
}
Component Wrap(string name, Component component) {
  return Renderer(component, [name, component] {
    return hbox({
               text(name) | size(WIDTH, EQUAL, 20),
               separator(),
               component->Render() | xflex,
           }) |
           xflex;
  });
}
bool ValidateDate(const string& date) {
    regex date_pattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4}$)");
    if (!regex_match(date, date_pattern)) {
        return false;
    }

    int day = safe_stoi(date.substr(0, 2));
    int month = safe_stoi(date.substr(3, 2));
    int year = safe_stoi(date.substr(6, 4));

    if (month == 2) {
        bool is_leap_year = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > 29 || (day == 29 && !is_leap_year)) {
            return false;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return false;
        }
    }
    return true;
}
ButtonOption btn_style1()
{
  auto option = ButtonOption::Border();
  option.transform = [](const EntryState& s) {
    auto element = text(s.label);
    if (s.focused) {
      element |= bold;
    }
    return element | center | border;
  };
  return option;
}
Component Patientdisplay(Patient& patient)
{   
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    Patient_State current_patient_state = Patient_State::MainScreen;
    bool is_female = patient.getGender();
    string Gender = (patient.getGender())? "Nữ" : "Nam";
    string DOB = patient.getDayOfBirth().getDate();
    string full_name = patient.getFullName();
    string phoneNumber = patient.getPhone();
    string address = patient.getAddress();
    string ID = patient.getID_patient();

    //-----radiobox-----------
    int gender_index = (is_female)? 1 : 0;
    vector<string> gender_labels = {"Nam", "Nữ"};
    Component gender_radiobox = Radiobox(&gender_labels, &gender_index);
    gender_radiobox = Wrap("Giới tính", gender_radiobox);
    //-----input-----------
    Component input_full_name = Input(&full_name, "Nhập họ và tên");
    input_full_name = Wrap("Họ và tên", input_full_name);

    Component input_phone_number = Input(&phoneNumber, "Nhập số điện thoại");
    input_phone_number = Wrap("Số điện thoại", input_phone_number);
    input_phone_number |= CatchEvent([&](Event event) {
    return event.is_character() && !isdigit(event.character()[0]);
    });
    input_phone_number |= CatchEvent([&](Event event) {
    return event.is_character() && phoneNumber.size() > 10;
    });

    Component input_dob = Input(&DOB, "DD/MM/YYYY");
    auto validity_message = Renderer([&] {
        return text((ValidateDate(DOB)) ? " " : "Ngày không hợp lệ") | color(Color::Red);
    });
    Component input_dateofbirth = Wrap("Ngày sinh", 
        Container::Vertical({
            input_dob,         // Gọi Render() để chuyển đổi thành Element
            validity_message
        })
    );

    // input_dob = Wrap("Ngày sinh", input_dob);
    // Component input_dateofbirth = Renderer([&] {
    //     return vbox({
    //         input_dob->Render(),
    //         text((ValidateDate(DOB))? " " : "Ngày không sinh hợp lệ")
    //     });
    // });
    // input_dateofbirth = Wrap("Ngày sinh", input_dateofbirth);
    
    Component input_address = Input(&address, "Nhập địa chỉ");
    input_address = Wrap("Địa chỉ", input_address);
    //-------Text-----------
    Component ID_text = Renderer([&] {
        return text(ID);
    });
    ID_text = Wrap("Mã bệnh nhân", ID_text);
    //-------Button-----------
    Component save_button = Button("Lưu & quay lại", [&]() {current_patient_state = Patient_State::MainScreen;}, btn_style1());
    //--------Layout-----------
    Component Patient_display_container = Container::Vertical({
        ID_text,
        input_full_name,
        input_dateofbirth,
        gender_radiobox,
        input_phone_number,
        input_address,
        save_button
    });
    Component Patient_display_interface = Renderer(Patient_display_container, [&]{
        return vbox({
            text("Thông tin bệnh nhân") | bold | center,
            separator(),
            ID_text->Render(),
            separator(),
            input_full_name->Render(),
            separator(),
            input_dateofbirth->Render(),
            separator(),
            gender_radiobox->Render(),
            separator(),
            input_phone_number->Render(),
            separator(),
            input_address->Render(),
            separator(),
            save_button->Render()
        })|
           xflex | size(WIDTH, EQUAL, 100) | border | hcenter;
    });
    screen.Loop(Patient_display_interface);
    return Patient_display_interface;
}
void Patient_UI(Patient& patient)
{
    
    int current_page = 0;
    
}