#include <Interface/Patient_interface.hpp>

std::string FormatDate(const std::tm& date) {
    std::stringstream ss;
    ss << std::put_time(&date, "%d/%m");
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

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

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
    auto element = text(s.label) | border;
    if (s.focused) {
      element |= inverted;
    }
    return element | center;
  };
  return option;
}
ButtonOption btn_style2()
{
  auto option = ButtonOption::Border();
  option.transform = [](const EntryState& s) {
    auto element = text(s.label)| border;
    if (s.focused) {
      element |= inverted;
    }
    return element;
  };
  return option;
}

void Patientdisplay(Patient& patient)
{   
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
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
    Component input_address = Input(&address, "Nhập địa chỉ");
    input_address = Wrap("Địa chỉ", input_address);
    //-------Text-----------
    Component ID_text = Renderer([&] {
        return text(ID);
    });
    ID_text = Wrap("Mã bệnh nhân", ID_text);
    //-------Button-----------
    
    Component back_button = Button("Quay lại", screen.ExitLoopClosure(), btn_style1());
    Component submit_button = Button("Lưu thông tin", [&]() {
        patient.setFullName(full_name);
        patient.setPhone(phoneNumber);
        patient.setDayOfBirth(DOB);
        patient.setAddress(address);
        screen.ExitLoopClosure()();
    }, btn_style1());
    //--------Layout-----------
    Component Patient_display_container = Container::Vertical({
        ID_text,
        input_full_name,
        input_dateofbirth,
        gender_radiobox,
        input_phone_number,
        input_address,
        Container::Horizontal({
        back_button,
        submit_button,
        })
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
            hbox({
                back_button->Render(),
                submit_button->Render(),
            })|xflex | center,

        })|
           xflex | size(WIDTH, EQUAL, 100) | border | hcenter;
    });
    screen.Loop(Patient_display_interface);
}
string Greeting(const std::string& name)
{
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    int hour = localTime->tm_hour;
    if(hour < 12) return "Chào buổi sáng, " + name + ".";
    if(hour < 18) return "Chào buổi chiều, " + name + ".";
    return "Chào buổi tối, " + name + ".";
}

void Appoinment_UI(Patient& patient)
{
    std::vector<std::string> days_of_week = {"CN", "Hai", "Ba", "Tư", "Năm", "Sáu", "Bảy"};
    // Tạo các nút giờ
    std::vector<std::string> time_slots = {
    "07:30 - 08:30", "08:30 - 09:30", "09:30 - 10:30", "10:30 - 11:30",
    "13:30 - 14:30", "14:30 - 15:30", "15:30 - 16:30", "16:30 - 17:00"
    };
    auto screen = ScreenInteractive::FullscreenAlternateScreen();
    int current_page = 0;
    int total_pages = 3;
    // Ngày hiện tại
    auto now = system_clock::now();
    auto current_time = system_clock::to_time_t(now);
    std::tm current_date = *std::localtime(&current_time);

    // Chuyển sang đầu tháng hiện tại
    // current_date.tm_mday = 1;
    mktime(&current_date);

    int selected_day = -1;
    int selected_time = -1;
    std::vector<std::vector<Component>> day_buttons;
    tm next_month = current_date;
    // next_month.tm_mon++;
    next_month.tm_mday+=30;
    mktime(&next_month);
    // Tạo các nút cho lịch ngày
    for (int i = 0; i < 6; ++i) {  // 6 hàng cho các tuần trong tháng
        std::vector<Component> week;
        for (int j = 0; j < 7; ++j) {  // 7 cột cho các ngày trong tuần
            auto date = current_date;
            int day_offset = i * 7 + j - current_date.tm_wday;
            date.tm_mday += day_offset;
            mktime(&date);

            auto day_button = Button(
                FormatDate(date),
                [&, day_offset]() { selected_day = day_offset; }
            );

            if(date.tm_yday == current_date.tm_yday) {
                week.push_back(day_button | bgcolor(Color::CyanLight) | color(Color::White));
            }

            else if (!(date.tm_yday >= current_date.tm_yday && date.tm_yday < next_month.tm_yday)) {
                week.push_back(day_button | color(Color::GrayDark));
            } 
            else {
                week.push_back(day_button | color(Color::GrayLight));
            }
        }
        day_buttons.push_back(week);
    }
    //Layout chọn ngày
    Component day_container = Container::Vertical({});
    for (const auto& week : day_buttons) {
        day_container->Add(Container::Horizontal(week));
    }

    Component next_page_btn = Button("Tiếp theo",  [&]{
        if (current_page < total_pages - 1) current_page++;
    });
    next_page_btn = Container::Horizontal({next_page_btn});
    Component prev_page_btn = Button("Quay lại", [&]{
        if (current_page == 0) screen.ExitLoopClosure()();
        if (current_page > 0) current_page--;
    });
    prev_page_btn = Container::Horizontal({prev_page_btn});
    Component end_button = Button("Kết thúc", 
        screen.ExitLoopClosure() // Thoát khỏi vòng lặp giao diện
    );
    end_button = Container::Horizontal({end_button});
    //Các nút
    Component page_btn = Container::Horizontal({
        next_page_btn,
        prev_page_btn,
        end_button
    });
    Component select_date_container = Container::Vertical({
        day_container
        // page_btn
    });

    Component select_date_layout = Renderer(select_date_container, [&]{
        Elements day_of_week_headers;
        for (const auto& day : days_of_week) {
            day_of_week_headers.push_back(text(day) | center | bold | size(WIDTH, EQUAL, 10));
        }

        Elements week_elements;
        for (const auto& week : day_buttons) {
            Elements day_elements;
            for (const auto& day_button : week) {
                day_elements.push_back(day_button->Render() | center | size(WIDTH, EQUAL, 10));
            }
            week_elements.push_back(hbox(day_elements) | center);
        }
        return vbox({
            text("Vui lòng chọn ngày khám") | center | bold,
            separator(),
            hbox(day_of_week_headers) | center,
            vbox(week_elements),
        });
    });


    std::vector<Component> time_buttons;

    for (int i = 0; i < time_slots.size(); ++i) {
        auto time_button = Button(
            time_slots[i],
            [&, i]() { selected_time = i; }
        );

        // Nổi bật nút thời gian được chọn
        if (selected_time == i) {
            time_buttons.push_back(time_button | bgcolor(Color::Blue) | color(Color::White));
        } else {
            time_buttons.push_back(time_button );
        }
    }

    Component time_container = Container::Horizontal(time_buttons);
    Component select_time_container = Container::Vertical({
        time_container
        // back_button
    });

    Component select_time_layout = Renderer(select_time_container, [&] {
        return vbox({
            text("Vui lòng chọn giờ khám") | center | bold,
            separator(),
            text("Buổi sáng") | bold | center | color(Color::Green),
            hbox({
                time_buttons[0]->Render(),
                time_buttons[1]->Render(),
                time_buttons[2]->Render(),
                time_buttons[3]->Render(),
            }) | center,
            separator(),
            text("Buổi chiều") | bold | center | color(Color::Green),
            hbox({
                time_buttons[4]->Render(),
                time_buttons[5]->Render(),
                time_buttons[6]->Render(),
                time_buttons[7]->Render(),
            }) | center,
        });
    });
    string symptom;
    InputOption symptom_input_options = InputOption::Spacious();
    symptom_input_options.multiline = true;
    Component InputSymptom = Input(symptom, "Nhập triệu chứng:", symptom_input_options) | xflex | size(HEIGHT, GREATER_THAN, 15);
    // InputSymptom = Container::Horizontal({InputSymptom})|size(HEIGHT, GREATER_THAN, 15) | size(WIDTH, EQUAL, 98);
    Component symptom_Layout = Renderer(InputSymptom, [&] {
        return vbox({
            text("Hãy cho chúng tôi biết tình vấn đề của bạn!") | center | bold,
            separator(),
            InputSymptom->Render()
        }) | size(WIDTH, EQUAL, 100) | size(HEIGHT, GREATER_THAN, 15) | border | hcenter;
    });

    // screen.Loop(time_select_layout);
    Component pages_container = Container::Tab(
        {
            select_date_layout, 
            select_time_layout,
            symptom_Layout,
            // back_button
        },
        &current_page
    );
    Component main_container = Container::Vertical({
        pages_container,
        page_btn
    });
    Component main_layout = Renderer(main_container, [&] {
        return vbox({
            pages_container->Render(),
            separator(),
            hbox({
                prev_page_btn->Render(),
                separatorEmpty()|size(WIDTH, EQUAL, 10),
                (current_page == total_pages - 1 ? end_button->Render() : next_page_btn->Render()) // Hiển thị nút kết thúc ở trang cuối
            }) | center
        });
    });
    screen.Loop(main_layout);

}
void Patient_UI(Patient& patient)
{   
    Patient_State state = Patient_State::MainScreen;
    // Tạo màn hình giao diện
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    std::string patient_name = patient.getFullName(); // Tên bệnh nhân

    // Các mục lựa chọn
    auto greeting = ftxui::Renderer([&] { return ftxui::text(Greeting(patient_name)); });
    auto xem_sua_thong_tin = ftxui::Button("Xem/Sửa Thông Tin", [&] {Patientdisplay(patient); }, btn_style2()) ;
    auto dat_lich = ftxui::Button("Đặt Lịch Khám", [&] {Appoinment_UI(patient); }, btn_style2());
    auto xem_sua_xoa_lich = ftxui::Button("Lịch khám Bệnh", [&] { }, btn_style2());
    auto lich_su_kham = ftxui::Button("Lịch Sử Khám Bệnh", [&] { }, btn_style2());
    auto thoat = ftxui::Button("  Thoát  ", [&] { screen.ExitLoopClosure()(); }, btn_style1());
    auto main_page_layout = ftxui::Container::Vertical({
        greeting,
        xem_sua_thong_tin,
        dat_lich,
        xem_sua_xoa_lich,
        lich_su_kham,
        thoat,
    });
    auto main_page = ftxui::Renderer(main_page_layout, [&] {
        return vbox({
            greeting->Render(),
            separator(),
            xem_sua_thong_tin->Render(),
            dat_lich->Render(),
            xem_sua_xoa_lich->Render(),
            lich_su_kham->Render(),
            separator(),
            thoat->Render(),
        }) |
            xflex | size(WIDTH, EQUAL, 100) | size(HEIGHT, EQUAL, 50) | border | hcenter;
    });

    screen.Loop(main_page);
    // while(true)
    // {
    //     switch(state)
    //     {
    //         case Patient_State::Info:
    //             Patientdisplay(patient);
    //             state = Patient_State::MainScreen;
    //             break;
    //         case Patient_State::Appoinment:
    //             Appoinment_UI(patient);
    //             state = Patient_State::MainScreen;
    //             break;
    //         case Patient_State::MainScreen:
    //             screen.Loop(main_page);
    //             break;
    //     }
    // }
    
}