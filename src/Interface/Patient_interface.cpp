#include <Interface/Patient_interface.hpp>

string splitText(string text, int boxWidth)
{
    vector<string> lines;
    int startIndex = 0;
    int textLength = text.length();

    while (startIndex < textLength)
    {
        // Xác định chiều dài dòng hiện tại
        int endIndex = startIndex + boxWidth;

        // Kiểm tra nếu endIndex vượt quá chiều dài của chuỗi
        if (endIndex >= textLength)
        {
            endIndex = textLength;
        }
        else
        {
            // Lùi lại để tìm khoảng trắng gần nhất nếu có
            while (endIndex > startIndex && text[endIndex] != ' ')
            {
                endIndex--;
            }

            // Nếu không tìm thấy khoảng trắng, giữ nguyên chiều dài mặc định
            if (endIndex == startIndex)
            {
                endIndex = startIndex + boxWidth;
            }
        }

        // Lấy đoạn văn bản từ startIndex đến endIndex
        string line = text.substr(startIndex, endIndex - startIndex);
        lines.push_back(line);

        // Bỏ qua dấu cách ở đầu dòng tiếp theo (nếu có)
        startIndex = endIndex;
        while (startIndex < textLength && text[startIndex] == ' ')
        {
            startIndex++;
        }
    }
    string result = "";
    for (auto &line : lines)
    {
        result += line + "\n";
    }
    return result;
}
void unSplitText(string &text)
{
    for (int i = 0; i < text.length() - 1; i++)
    {
        if (text[i] == '\n' && text[i + 1] != '\n')
        {
            text.erase(i, 1);
            i--;
        }
    }
}
std::string FormatDate(const std::tm &date)
{
    std::stringstream ss;
    ss << std::put_time(&date, "%d/%m");
    return ss.str();
}
std::string Date_to_string(const tm &timeStruct)
{
    char buffer[11]; // Đủ để chứa chuỗi định dạng "dd/mm/yyyy" + ký tự null
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &timeStruct);
    return std::string(buffer);
}
Component Wrap(string name, Component component)
{
    return Renderer(component, [name, component]
                    { return hbox({
                                 text(name) | size(WIDTH, EQUAL, 20),
                                 separator(),
                                 component->Render() | xflex,
                             }) |
                             xflex; });
}
bool validateDate(const string &date)
{
    regex date_pattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4}$)");
    if (!regex_match(date, date_pattern))
    {
        return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (month == 2)
    {
        bool is_leap_year = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > 29 || (day == 29 && !is_leap_year))
        {
            return false;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
        {
            return false;
        }
    }
    return true;
}
ButtonOption btn_style1()
{
    auto option = ButtonOption::Border();
    option.transform = [](const EntryState &s)
    {
        auto element = text(s.label) | border;
        if (s.focused)
        {
            element |= inverted;
        }
        return element | center;
    };
    return option;
}
ButtonOption btn_style2()
{
    auto option = ButtonOption::Border();
    option.transform = [](const EntryState &s)
    {
        auto element = text(s.label) | border;
        if (s.focused)
        {
            element |= inverted;
        }
        return element;
    };
    return option;
}
ButtonOption Btn_animated_opt1()
{
    auto option = ButtonOption::Animated();
    option.transform = [](const EntryState &s)
    {
        auto element = text(s.label);
        if (s.focused)
        {
            element |= bold;
        }
        return element;
    };
    return option;
}
void Patientdisplay(Patient *&patient)
{
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    bool is_female = patient->getGender();
    string Gender = (patient->getGender()) ? "Nữ" : "Nam";
    string DOB = patient->getDayOfBirth().getDate();
    string full_name = patient->getFullName();
    string phoneNumber = patient->getPhone();
    string address = patient->getAddress();
    string ID = patient->getID_patient();
    string CCCD = patient->getCCCD();

    //-----radiobox-----------
    int gender_index = (is_female) ? 1 : 0;
    vector<string> gender_labels = {"Nam", "Nữ"};
    Component gender_radiobox = Radiobox(&gender_labels, &gender_index);
    gender_radiobox = Wrap("Giới tính", gender_radiobox);
    //-----input-----------
    Component input_full_name = Input(&full_name, "Nhập họ và tên");
    input_full_name = Wrap("Họ và tên", input_full_name);

    Component input_phone_number = Input(&phoneNumber, "Nhập số điện thoại");
    input_phone_number = Wrap("Số điện thoại", input_phone_number);
    input_phone_number |= CatchEvent([&](Event event)
                                     { return event.is_character() && !isdigit(event.character()[0]); });
    input_phone_number |= CatchEvent([&](Event event)
                                     { return event.is_character() && phoneNumber.size() > 10; });

    Component input_dob = Input(&DOB, "DD/MM/YYYY");
    auto validity_message = Renderer([&]
                                     { return text((validateDate(DOB)) ? " " : "Ngày không hợp lệ") | color(Color::Red); });
    Component input_dateofbirth = Wrap("Ngày sinh",
                                       Container::Vertical({input_dob, // Gọi Render() để chuyển đổi thành Element
                                                            validity_message}));
    Component input_CCCD = Input(&CCCD, "Số định danh:");
    input_CCCD = Wrap("Mã định danh", input_CCCD);
    input_CCCD |= CatchEvent([&](Event event)
                             { return event.is_character() && !isdigit(event.character()[0]); });
    input_CCCD |= CatchEvent([&](Event event)
                             { return event.is_character() && CCCD.size() > 12; });
    Component input_address = Input(&address, "Nhập địa chỉ");
    input_address = Wrap("Địa chỉ", input_address);
    //-------Text-----------
    Component ID_text = Renderer([&]
                                 { return text(ID); });
    ID_text = Wrap("Mã bệnh nhân", ID_text);
    //-------Button-----------

    Component back_button = Button("Quay lại", screen.ExitLoopClosure(), btn_style1());
    Component submit_button = Button("Lưu thông tin", [&]()
                                     {
        patient->setFullName(full_name);
        patient->setPhone(phoneNumber);
        patient->setDayOfBirth(DOB);
        patient->setAddress(address);
        patient->setGender(gender_index);
        patient->setCCCD(CCCD);
        // path file_path = "../Database/PatientDB/";
        // file_path.append(patient.getID_patient() + ".txt");
        // fstream fi(file_path, ios::out);
        // patient.writePatientToFile(fi);
        // fi.close();
        screen.ExitLoopClosure()(); }, btn_style1());
    //--------Layout-----------
    Component Patient_display_container = Container::Vertical({ID_text,
                                                               input_full_name,
                                                               input_dateofbirth,
                                                               gender_radiobox,
                                                               input_CCCD,
                                                               input_phone_number,
                                                               input_address,
                                                               Container::Horizontal({
                                                                   back_button,
                                                                   submit_button,
                                                               })});
    Component Patient_display_interface = Renderer(Patient_display_container, [&]
                                                   { return vbox({
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
                                                                input_CCCD->Render(),
                                                                separator(),
                                                                input_phone_number->Render(),
                                                                separator(),
                                                                input_address->Render(),
                                                                separator(),
                                                                hbox({
                                                                    back_button->Render(),
                                                                    submit_button->Render(),
                                                                }) | xflex |
                                                                    center,

                                                            }) |
                                                            xflex | size(WIDTH, EQUAL, 100) | border | hcenter; });
    screen.Loop(Patient_display_interface);
}
string Greeting(const std::string &name)
{
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);
    int hour = localTime->tm_hour;
    if (hour < 12)
        return "Chào buổi sáng, " + name + ".";
    if (hour < 18)
        return "Chào buổi chiều, " + name + ".";
    return "Chào buổi tối, " + name + ".";
}
void P_Appoinment_info_UI(Patient &patient)
{
    auto screen = ScreenInteractive::TerminalOutput();
    // std::vector<Appoinment> danhSachLich = searchAppoinments(patient);
    listAppoinment listApp;
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);
    string start_date = Date_to_string(*localTime);
    localTime->tm_mday += 30;
    mktime(localTime);
    string end_date = Date_to_string(*localTime);
    vector<Appoinment *> danhSachLich = listApp.getAppointmentsByPatientIDIRange(patient.getID_patient(), start_date, end_date);
    // Component Appoinment_cancel_renderer;
    // ID  Ngày  Thời gian
    // vector<string> App_list;
    // Element header_text = text(patient.getID_patient()) | bold | center;
    Element header_text = text("Danh sách lịch khám") | bold | center;
    Element tb_text = text("   Mã lịch khám   Ngày   Thời gian") | bold;
    // for(auto& app : danhSachLich)
    // {
    //     App_list.push_back("  " + app.getID() + "        " + (app.getDate().getDate()) + "       " + GioKham(app.getTime()) + (app.getStatus()? "Còn hiệu lực" : "Đã hủy"));
    // }
    int selected = 1;
    int popup_level = 0;
    Appoinment *selected_app;
    // auto Create_App_cancel = [&screen, &patient](Appoinment &app) {

    // };
    Component Menu_app_list = Container::Vertical({});

    for (auto &app : danhSachLich)
    {
        auto tmp_btn = Button(("  " + app->getID() + "        " + (app->getDate().getDate()) + "       " + GioKham(app->getTime()) + "            " + (app->getStatus() ? "Hiệu lực" : " Đã hủy")), [&]()
                              {
            selected_app = app; // gán lịch khám đã chọn
            popup_level = 1; }, Btn_animated_opt1());
        Menu_app_list->Add(tmp_btn);
    }
    // Menu_app_list->;
    Component exit_btn = Button("Quay lại", [&]
                                { screen.ExitLoopClosure()(); }, btn_style1());
    Component Menu_app = Container::Vertical({
        Menu_app_list,
        exit_btn,
    });
    auto menu_app_list_renderer = Renderer(Menu_app, [&]
                                           {
        // return window(
            // text("Danh sách lịch khám") | bold | center,
        return vbox({
            // separator(),
            hbox({
                text("Mã lịch khám"), 
                separatorEmpty() | size(WIDTH, EQUAL, 10), 
                text("Ngày"), 
                separatorEmpty() | size(WIDTH, EQUAL, 13), 
                text("Giờ khám"),
                separatorEmpty() | size(WIDTH, EQUAL, 13),
                text("Trạng thái"),
                // separatorEmpty() | size(WIDTH, EQUAL, 10),
            }),
            separator(),
            Menu_app_list->Render(),
            separator(),
            exit_btn->Render() | hcenter,
            }//)
        ); });

    Component Patient_id = Wrap("Mã bệnh nhân:", Renderer([&]
                                                          { return text(patient.getID_patient()); }));
    Component Full_name = Wrap("Họ và tên:", Renderer([&]()
                                                      { return text(patient.getFullName()); }));
    Component Phone_number = Wrap("Số điện thoại:", Renderer([&]
                                                             { return text(patient.getPhone()); }));
    Component DOB = Wrap("Ngày sinh:", Renderer([&]()
                                                { return text(patient.getDayOfBirth().getDate()); }));
    Component CCCD = Wrap("CCCD:", Renderer([&]()
                                            { return text(patient.getCCCD()); }));
    string Gender = (patient.getGender() ? "Nữ" : "Nam");
    Component Patient_gender = Wrap("Giới tính:", Renderer([&]()
                                                           { return text(Gender); }));
    Component Address = Wrap("Địa chỉ:", Renderer([&]()
                                                  { return text(patient.getAddress()); }));
    Component a_ID = Wrap("Mã lịch khám:", Renderer([&]()
                                                    { return text((*selected_app).getID()); }));
    Component a_Date = Wrap("Ngày khám:", Renderer([&]()
                                                   { return text((*selected_app).getDate().getDate()); }));
    Component a_Time = Wrap("Giờ khám:", Renderer([&]()
                                                  { return text(GioKham((*selected_app).getTime())); }));
    Component Symptom_text = Wrap("Triệu chứng:", Renderer([&]()
                                                           { return paragraph((*selected_app).getDescription()); }));
    Component status_text = Wrap("Hiệu lực:", Renderer([&]()
                                                       { return text((*selected_app).getStatus() ? "Hiệu lực" : "Đã hủy"); }));
    Component is_Processed = Wrap("Trạng thái khám: ", Renderer([&]()
                                                                { return text((*selected_app).getIsProcessed() ? "Đã khám" : "Chưa khám"); }));
    auto app_cancel_btn = Button("Hủy lịch khám", [&]()
                                 {
            // selected_app.setStatus(false);
            popup_level = 2; });
    auto app_exit_btn = Button("Quay lại", [&]()
                               { popup_level = 0; }, btn_style1());
    // Xem và hủy lịch khám
    auto cancel_app = Container::Horizontal({app_cancel_btn,
                                             app_exit_btn}) |
                      size(HEIGHT, EQUAL, 3);
    Component Appoinment_info = Container::Vertical({
        Patient_id,
        Full_name,
        Phone_number,
        DOB,
        CCCD,
        Patient_gender,
        Address,
        a_ID,
        a_Date,
        a_Time,
        Symptom_text,
        status_text,
        is_Processed,
        // cancel_app,
        // app_exit_btn,
    });
    auto popup_container = Container::Vertical({
        Appoinment_info,
        cancel_app,
    });
    auto Appoinment_cancel_renderer = Renderer(popup_container, [&]
                                               {
        // return window(
            // text("Thông tin lịch khám") | bold | center,
        return    vbox({
                separator(),
                Patient_id->Render(),
                Full_name->Render(),
                DOB->Render(),
                CCCD->Render(),
                Patient_gender->Render(),
                Address->Render(),
                separator(),
                a_ID->Render(),
                a_Date->Render(),
                a_Time->Render(),
                Symptom_text->Render(),
                separator(),
                status_text->Render(),
                is_Processed->Render(),
                separator(),
                // cancel_app->Render() | hcenter,
                hbox({
                    app_cancel_btn->Render(),
                    separatorEmpty() | size(WIDTH, EQUAL, 6),  // Add empty space for separator
                    app_exit_btn->Render(),
                })| size(HEIGHT, EQUAL, 3) | hcenter,
                // app_exit_btn->Render() | hcenter,
            }//)
        ); });
    // screen.Loop(Appoinment_cancel_renderer);
    string Confirm_msg;
    Component confirm_btn = Button("Xác nhận", [&]()
                                   {
                                       (*selected_app).UpdateStatus(0, 0);
                                       Confirm_msg = "Hủy lịch khám thành công!";
                                       listApp.writeAppointmentsToFile();
                                       // popup_level = 1;
                                   },
                                   btn_style1());
    Component cancel_btn = Button("Quay lại", [&]()
                                  { 
        popup_level = 1;
        Confirm_msg = ""; }, btn_style1());
    Component exit_btn1_ = Button("Thoát", [&]()
    {
        screen.ExitLoopClosure()();
    }, btn_style1());
    Component cancel_confirm_container = Container::Horizontal({
        cancel_btn,
        confirm_btn,
        exit_btn1_,

    });
    Component cancel_confirm_renderer = Renderer(cancel_confirm_container, [&]
                                                 {
        // return window(
        //     text("Xác nhận hủy lịch khám") | bold | center,
        return vbox({
                separator(),
                text("Thao tác hủy sẽ không thể hoàn tác, vui lòng xác nhận trước khi hủy.") | color(Color::Red) | hcenter,
                hbox({
                    cancel_btn->Render(),
                    separatorEmpty() | size(WIDTH, EQUAL, 5),  // Add empty space for separator,
                    confirm_btn->Render(),
                    separatorEmpty() | size(WIDTH, EQUAL, 5),  // Add empty space for separator,
                    exit_btn1_->Render(),
                }) | hcenter,
                separator(),
                text(Confirm_msg)| color(Color::Green) | hcenter,
            }); });
    // string temp = to_string(danhSachLich.size());
    auto window_1 = Window({
        .inner = menu_app_list_renderer,
        .title = "Danh sách lịch khám",
        // .title = temp,
        .width = 100,
        .height = 23,
    });
    auto window_2 = Window({
        .inner = Appoinment_cancel_renderer,
        .title = "Thông tin lịch khám",
        .width = 70,
        .height = 22,
    });
    auto window_3 = Window({
        .inner = cancel_confirm_renderer,
        .title = "Xác nhận hủy lịch khám",
        .width = 70,
        .height = 9,
    });
    auto main_container = Container::Tab(
        {
            window_1,
            window_2,
            window_3,
        },
        &popup_level);
    // Component window_container;
    // screen.Loop(window_container);
    // auto main_container = Container::Tab(
    //     {
    //         menu_app_list_renderer,
    //         Appoinment_cancel_renderer,
    //         cancel_confirm_renderer,
    //     },
    //     &popup_level
    // );
    Component main_renderer = Renderer(main_container, [&]
                                       {
        Element showing = window_1->Render() | bgcolor(Color::Black);
        if (popup_level == 1) {
            showing = dbox({
                // showing = window_1->Render(),
                // showing,
                window_1->Render() | bgcolor(Color::Black),
                window_2->Render() | bgcolor(Color::Black),
        });
        }
        if (popup_level == 2) {
            showing = dbox({
                // showing = window_1->Render(),
                // window_2->Render(),
                window_1->Render() | bgcolor(Color::Black),
                window_2->Render() | bgcolor(Color::Black),
                window_3->Render() | bgcolor(Color::Black),
            });
        }
        // Element showing = Appoinment_cancel_renderer->Render() | size(WIDTH, LESS_THAN, 80) | size(WIDTH, GREATER_THAN, 60);
        return showing; });
    screen.Loop(main_renderer);
}

void Appoinment_UI(Patient &patient)
{
    std::vector<std::string> days_of_week = {"CN", "Hai", "Ba", "Tư", "Năm", "Sáu", "Bảy"};
    // Tạo các nút giờ
    std::vector<std::string> time_slots = {
        "07:30 - 08:30", "08:30 - 09:30", "09:30 - 10:30", "10:30 - 11:30",
        "13:30 - 14:30", "14:30 - 15:30", "15:30 - 16:30", "16:30 - 17:00"};
    string scr_date;
    string scr_time;
    string symptom = "";
    listAppoinment danhSachLich;
    auto screen = ScreenInteractive::FullscreenAlternateScreen();
    int current_page = 0;
    int total_pages = 4;
    // Ngày hiện tại
    auto now = system_clock::now();
    auto current_time = system_clock::to_time_t(now);
    std::tm current_date = *std::localtime(&current_time);

    // Chuyển sang đầu tháng hiện tại
    // current_date.tm_mday = 1;
    mktime(&current_date);
    const int secondsPerDay = 86400;
    int current_epoch_date = mktime(&current_date) / secondsPerDay;
    int selected_day = -1;
    int selected_time = -1;
    std::vector<std::vector<Component>> day_buttons;
    tm next_month = current_date;
    // next_month.tm_mon++;
    next_month.tm_mday += 30;
    // mktime(&next_month);
    int next_month_epoch_date = mktime(&next_month) / secondsPerDay;
    // Tạo các nút cho lịch ngày
    for (int i = 0; i < 6; ++i)
    { // 6 hàng cho các tuần trong tháng
        std::vector<Component> week;
        for (int j = 0; j < 7; ++j)
        { // 7 cột cho các ngày trong tuần
            auto date = current_date;

            int day_offset = i * 7 + j - current_date.tm_wday;
            date.tm_mday += day_offset;
            int epoch_date = mktime(&date) / secondsPerDay;

            auto day_button = Button(
                FormatDate(date),
                [&, day_offset]()
                { selected_day = day_offset; });

            if (date.tm_yday == current_date.tm_yday)
            {
                week.push_back(day_button | bgcolor(Color::CyanLight) | color(Color::White));
            }

            // else if (!(date.tm_yday >= current_date.tm_yday && date.tm_yday < next_month.tm_yday)) {
            //     week.push_back(day_button | color(Color::GrayDark));
            // }
            else if (!(epoch_date >= current_epoch_date && epoch_date < next_month_epoch_date))
            {
                week.push_back(day_button | color(Color::GrayDark));
            }
            else
            {
                week.push_back(day_button | color(Color::GrayLight));
            }
        }
        day_buttons.push_back(week);
    }
    // Layout chọn ngày
    Component day_container = Container::Vertical({});
    for (const auto &week : day_buttons)
    {
        day_container->Add(Container::Horizontal(week));
    }

    Component next_page_btn = Button("Tiếp theo", [&]
                                     {
        if (current_page < total_pages - 1) current_page++; });
    next_page_btn = Container::Horizontal({next_page_btn});
    Component prev_page_btn = Button("Quay lại", [&]
                                     {
        if (current_page == 0) screen.ExitLoopClosure()();
        if (current_page > 0) current_page--; });
    prev_page_btn = Container::Horizontal({prev_page_btn});
    Component end_button = Button("Kết thúc", [&]
                                  {
        Date dd;
        dd.setDate(scr_date);
        // Thêm code xử lý đặt lịch khám và thông báo đã đặt lịch thành công
        Appoinment *app = new Appoinment(patient, dd, selected_time, symptom);
        danhSachLich.addAppointment(app);
        screen.ExitLoopClosure()(); });
    end_button = Container::Horizontal({end_button});
    // Các nút
    Component page_btn = Container::Horizontal({next_page_btn,
                                                prev_page_btn,
                                                end_button});
    Component select_date_container = Container::Vertical({
        day_container
        // page_btn
    });

    Component select_date_layout = Renderer(select_date_container, [&]
                                            {
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
        }); });
    std::vector<Component> time_buttons;
    for (int i = 0; i < time_slots.size(); ++i)
    {
        auto time_button = Button(
            time_slots[i],
            [&, i]()
            { selected_time = i; });

        // Nổi bật nút thời gian được chọn
        if (selected_time == i)
        {
            time_buttons.push_back(time_button | bgcolor(Color::Blue) | color(Color::White));
        }
        else
        {
            time_buttons.push_back(time_button);
        }
    }

    Component time_container = Container::Horizontal(time_buttons);
    Component select_time_container = Container::Vertical({
        time_container
        // back_button
    });

    Component select_time_layout = Renderer(select_time_container, [&]
                                            { return vbox({
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
                                              }); });
    InputOption symptom_input_options = InputOption::Default();
    symptom_input_options.multiline = true;
    Component InputSymptom = Input(&symptom, "Nhập triệu chứng:", symptom_input_options) | size(HEIGHT, GREATER_THAN, 15);
    Component symptom_Layout = Renderer(InputSymptom, [&]
                                        { return vbox({
                                                     text("Hãy cho chúng tôi biết tình tình trạng của bạn!") | center | bold,
                                                     separator(),
                                                     InputSymptom->Render() | border,
                                                 }) |
                                                 size(WIDTH, EQUAL, 100) | size(HEIGHT, GREATER_THAN, 15) | border | hcenter; });

    // Xác nhận thông tin

    Component Patient_id = Wrap("Mã bệnh nhân:", Renderer([&]
                                                          { return text(patient.getID_patient()); }));
    Component Full_name = Wrap("Họ và tên:", Renderer([&]()
                                                      { return text(patient.getFullName()); }));
    Component Phone_number = Wrap("Số điện thoại:", Renderer([&]
                                                             { return text(patient.getPhone()); }));
    Component DOB = Wrap("Ngày sinh:", Renderer([&]()
                                                { return text(patient.getDayOfBirth().getDate()); }));
    Component CCCD = Wrap("CCCD:", Renderer([&]()
                                            { return text(patient.getCCCD()); }));
    string Gender = (patient.getGender() ? "Nữ" : "Nam");
    Component Patient_gender = Wrap("Giới tính:", Renderer([&]()
                                                           { return text(Gender); }));
    Component Address = Wrap("Địa chỉ:", Renderer([&]()
                                                  { return text(patient.getAddress()); }));

    Component a_Date = Wrap("Ngày khám:", Renderer([&]()
                                                   { return text(scr_date); }));
    Component a_Time = Wrap("Giờ khám:", Renderer([&]()
                                                  { return text(scr_time); }));
    Component Symptom_text = Wrap("Triệu chứng:", Renderer([&]()
                                                           { return paragraph(symptom); }));
    Component Appoinment_info = Container::Vertical({
        Patient_id,
        Full_name,
        Phone_number,
        DOB,
        CCCD,
        Patient_gender,
        Address,
        a_Date,
        a_Time,
        Symptom_text,
    });
    Component Appoinment_info_layout = Renderer(Appoinment_info, [&]
                                                { return vbox({
                                                             text("Xác nhận thông tin lịch khám") | center | bold,
                                                             separator(),
                                                             Patient_id->Render(),
                                                             Full_name->Render(),
                                                             Phone_number->Render(),
                                                             DOB->Render(),
                                                             CCCD->Render(),
                                                             Patient_gender->Render(),
                                                             Address->Render(),
                                                             separator(),
                                                             a_Date->Render(),
                                                             a_Time->Render(),
                                                             Symptom_text->Render(),
                                                             separator(),
                                                         }) |
                                                         size(WIDTH, EQUAL, 100) | size(HEIGHT, GREATER_THAN, 15) | border | hcenter; });

    // screen.Loop(time_select_layout);
    Component pages_container = Container::Tab(
        {
            select_date_layout,
            select_time_layout,
            symptom_Layout,
            Appoinment_info_layout,
            // back_button
        },
        &current_page);
    Component main_container = Container::Vertical({pages_container,
                                                    page_btn});
    Component main_layout = Renderer(main_container, [&]
                                     {
        screen.Post([&](){
            if (selected_day >= 0 && selected_time >= 0) {
                //Chuyển thành ngày chính xác
            auto selected_date = current_date;
            selected_date.tm_mday += selected_day;
            mktime(&selected_date);
            scr_date = Date_to_string(selected_date);
            scr_time = time_slots[selected_time];
        }
        });
        return vbox({
            pages_container->Render(),
            separator(),
            hbox({
                prev_page_btn->Render(),
                separatorEmpty()|size(WIDTH, EQUAL, 10),
                (current_page == total_pages - 1 ? end_button->Render() : next_page_btn->Render()) // Hiển thị nút kết thúc ở trang cuối
            }) | center
        }); });

    screen.Loop(main_layout);
    // system("pause");
}
void Med_record_UI(Patient &patient)
{
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    listMedicalRecord lsMR;
    // lsMR.readListMedicalRecordFromFile();
    vector<MedicalRecord *> medRecords = lsMR.searchMedicalRecord(SearchField_MR::PatientID, patient.getID_patient());
    int popup_level = 0;
    MedicalRecord *selected_medRecord = nullptr;
    bool show_window2 = false;
    Component medical_records_container = Container::Vertical({});
    for (auto &medRecord : medRecords | std::views::reverse)
    {   
        string ID_record = medRecord->getID_record();
        Component btn = Button(" " + ID_record+ string(23 - ID_record.size(), ' ') + medRecord->getDateOfRecord().getDate(), [&]
                               {
            selected_medRecord = medRecord;
            popup_level = 1;
            show_window2= true; }, Btn_animated_opt1());
        medical_records_container->Add(btn);
    }
    // Menu_app_list->;
    Component exit_btn = Button("Quay lại", [&]
                                {
        screen.Exit();
        }, btn_style1());
    Component Menu_MR_list = Container::Vertical({
        medical_records_container,
        exit_btn,
    });
    auto Menu_MR_renderer = Renderer(Menu_MR_list, [&]
                                     { return vbox({
                                           hbox({
                                               text("Mã lịch sử khám"),
                                               separatorEmpty() | size(WIDTH, EQUAL, 10),
                                               text("Ngày cấp"),
                                           }),
                                           separator(),
                                           medical_records_container->Render(),
                                           separator(),
                                           exit_btn->Render() | hcenter,
                                       }); });
    Component Patient_id = Wrap("Mã bệnh nhân:", Renderer([&]
                                                          { return text(patient.getID_patient()); }));
    Component Full_name = Wrap("Họ và tên:", Renderer([&]()
                                                      { return text(patient.getFullName()); }));
    Component Phone_number = Wrap("Số điện thoại:", Renderer([&]
                                                             { return text(patient.getPhone()); }));
    Component DOB = Wrap("Ngày sinh:", Renderer([&]()
                                                { return text(patient.getDayOfBirth().getDate()); }));
    Component CCCD = Wrap("CCCD:", Renderer([&]()
                                            { return text(patient.getCCCD()); }));
    string Gender = (patient.getGender() ? "Nữ" : "Nam");
    Component Patient_gender = Wrap("Giới tính:", Renderer([&]()
                                                           { return text(Gender); }));
    Component Address = Wrap("Địa chỉ:", Renderer([&]()
                                                  { return text(patient.getAddress()); }));
    Component MR_ID = Wrap("Mã đơn thuốc:", Renderer([&]
                                                     { return text(selected_medRecord->getID_record()); }));
    Component MR_date = Wrap("Ngày cấp:", Renderer([&]
                                                   { return text(selected_medRecord->getDateOfRecord().getDate()); }));
    Component MR_symptom = Wrap("Triệu chứng:", Renderer([&]
                                                         { return paragraph(selected_medRecord->getSymptoms()); }));
    Component MR_diagnosis = Wrap("Chẩn đoán:", Renderer([&]
                                                         { return text(selected_medRecord->getDiagnosis()); }));
    Component back_btn = Button("Quay lại", [&]
                                { popup_level = 0;
                                show_window2 = false; }, btn_style1());
    Component MR_info = Container::Vertical({
        Patient_id,
        Full_name,
        Phone_number,
        DOB,
        CCCD,
        Patient_gender,
        Address,
        MR_ID,
        MR_date,
        MR_symptom,
        MR_diagnosis,
    });
    Component MR_popup = Container::Vertical({
        MR_info,
        back_btn,
    });
    auto popup_renderer = Renderer(MR_popup, [&]
                                   { return vbox({
                                         Patient_id->Render(),
                                         Full_name->Render(),
                                         Phone_number->Render(),
                                         DOB->Render(),
                                         CCCD->Render(),
                                         Patient_gender->Render(),
                                         Address->Render(),
                                         separator(),
                                         MR_ID->Render(),
                                         MR_date->Render(),
                                         separator(),
                                         MR_symptom->Render(),
                                         separator(),
                                         MR_diagnosis->Render(),
                                         separator(),
                                         back_btn->Render(),
                                     }); });

    Component window_1 = Window({
        .inner = Menu_MR_renderer,
        .title = "Danh sách đơn thuốc",
        .left = 20,
        .width = 80,
        .height = 30,
    });
    Component window_2 = Window({
        .inner = popup_renderer,
        .title = "Chi tiết đơn thuốc",
        .left = 20,
        .width = 80,
        .height = 30,
    });

    // Component main_layout = Container::Tab({
    //     window_1,
    //     window_2,
    // }, &popup_level);
    // Component main_screen = Renderer(main_layout, [&] {
    //     Element showing = window_1->Render() | bgcolor(Color::Black);
    //     if (popup_level == 1)
    //     {
    //         showing = dbox({
    //             showing,
    //             window_2->Render() | clear_under,
    //         });
    //     }
    //     return showing;
    // });
    // screen.Loop(main_screen);
    // Component w12 = Container::Stacked({
    //     window_1,
    //     window_2,
    // });
    Component main_w_layout = Container::Tab({
                                                 window_1,
                                                 window_2,
                                             },
                                             &popup_level);
    screen.Loop(main_w_layout);

    // auto window12 = Container::Stacked({
    //     window_1,
    //     window_2,
    // });
    // auto main_layout = Container::Tab({
    //                                       window_1,
    //                                       window12,
    //                                   },
    //                                   &popup_level);
    // screen.Loop(main_layout);
    // Component layout = Container::Tab({
    //     Menu_MR_list,
    //     MR_popup,
    // }, &popup_level);
    // screen.Loop(Menu_MR_renderer);
    // out << "2.5" << endl;
    //     Component temp_win1 = Container::Vertical({
    //         window_1
    //     });
    //     Component temp_layout = Renderer(temp_win1, [&]
    //     {
    //         return dbox({
    //             window_1->Render(),
    //         });
    //     });
    // screen.Loop(temp_layout);
}
void change_password_UI(Patient *patient, listAccount &accounts, AccountUser *&current_account)
{
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    string old_password, new_password, confirm_password;
    ftxui::InputOption input_pw_opt;
    input_pw_opt.password = true;
    Component account_info = Renderer([&]()
                                      { return vbox({
                                            text("Tài khoản bệnh nhân") | bold | center,
                                            separator(),
                                            hbox({vbox({
                                                      text("Mã tài khoản:"),
                                                      text("Tên đăng nhập:"),
                                                      text("Mã bệnh nhân:"),
                                                      text("Tên bệnh nhân:"),
                                                      text("Số định danh:"),
                                                  }) |size(WIDTH, EQUAL, 18),
                                                  separator(),
                                                  vbox({
                                                      text(current_account->getID()),
                                                      text(current_account->getUserName()),
                                                      text(patient->getID_patient()),
                                                      text(patient->getFullName()),
                                                      text(patient->getCCCD()),
                                                  })}),
                                            separator(),
                                        }); });
    Element change_password_msg = text("");
    Component change_password_form = Container::Vertical(
        {
            Container::Vertical({
                account_info,
                Container::Horizontal({Renderer([&]
                                                { return vbox({
                                                    text("Mật khẩu cũ:"),
                                                    text("Mật khẩu mới:"),
                                                    text("Xác nhận mật khẩu:"),
                                                }); }),
                                    Renderer([&]
                                                { return separator(); }),
                                    Container::Vertical({
                                        Input(&old_password, "Mật khẩu cũ:", input_pw_opt),
                                        Input(&new_password, "Mật khẩu mới:", input_pw_opt),
                                        Input(&confirm_password, "Xác nhận mật khẩu:", input_pw_opt),
                                    }) | size(WIDTH, EQUAL, 50),

                }),
            }) | border,
                Renderer([&]
                            { return change_password_msg; }) | hcenter,
                Container::Horizontal({
                    Button("Trở về", [&]()
                        { screen.ExitLoopClosure()(); }),
                        Renderer([&]{return separatorEmpty() | size(WIDTH, EQUAL, 8);}),
                    Button("Cập nhật", [&](){ 
                        if (old_password.empty() || new_password.empty() || confirm_password.empty())
                        {
                            change_password_msg = text("Mật khẩu không được để trống!") | color(Color::Red);
                        }
                        else if (current_account->getPassword() != old_password)
                        {
                            change_password_msg = text("Mật khẩu cũ không đúng!") | color(Color::Red);
                        }
                        else if (new_password != confirm_password)
                        {
                            change_password_msg = text("Vui lòng nhập lại mật khẩu đúng.") | color(Color::Red);
                        }
                        else if (!valid_password(new_password))
                        {
                            change_password_msg = hflow(paragraph("Mật khẩu phải có ít nhất 8 ký tự, bao gồm chữ cái, số và ký tự đặc biệt!")) | color(Color::Red);
                        }
                        else
                        {
                            current_account->setPassword(new_password);
                            accounts.writeListAccountToFile(1, 1);
                            change_password_msg = text("Cập nhật mật khẩu thành công!") | color(Color::Green);
                        } }),
            }) | hcenter,
        }) | hcenter;
    screen.Loop(change_password_form);
}
void Patient_UI(Patient *&patient, listPatient &patients, listAccount &accounts, AccountUser *&current_account)
{
    // Tạo màn hình giao diện
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    std::string patient_name = patient->getFullName(); // Tên bệnh nhân
    ofstream out("test_log.txt", ios::app);
    // Các mục lựa chọn
    auto greeting = ftxui::Renderer([&]
                                    { return ftxui::text(Greeting(patient_name)); });
    auto xem_sua_thong_tin = ftxui::Button("Xem/Sửa Thông Tin", [&]
                                           { Patientdisplay(patient); }, btn_style2());
    auto dat_lich = ftxui::Button("Đặt Lịch Khám", [&]
                                  { Appoinment_UI(*patient); }, btn_style2());
    auto xem_sua_xoa_lich = ftxui::Button("Lịch khám Bệnh", [&]
                                          { P_Appoinment_info_UI(*patient); }, btn_style2());
    auto lich_su_kham = ftxui::Button("Lịch Sử Khám Bệnh", [&]
                                      { Med_record_UI(*patient); }, btn_style2());
    auto doi_mk = Button("Đổi mật khẩu", [&]
                         { change_password_UI(patient, accounts, current_account); }, btn_style2());
    auto thoat = ftxui::Button("  Đăng xuất  ", [&]
                               { screen.ExitLoopClosure()(); }, btn_style1());
    auto main_page_layout = ftxui::Container::Vertical({
                                greeting,
                                Renderer([&]
                                         { return separator(); }),
                                xem_sua_thong_tin,
                                dat_lich,
                                xem_sua_xoa_lich,
                                lich_su_kham,
                                doi_mk,
                                Renderer([&]
                                         { return separator(); }),
                                thoat,
                            }) |
                            xflex | size(WIDTH, EQUAL, 100) | size(HEIGHT, EQUAL, 50) | border | hcenter;
    // auto main_page = ftxui::Renderer(main_page_layout, [&]
    //                                  { return vbox({
    //                                               greeting->Render(),
    //                                               separator(),
    //                                               xem_sua_thong_tin->Render(),
    //                                               dat_lich->Render(),
    //                                               xem_sua_xoa_lich->Render(),
    //                                               lich_su_kham->Render(),
    //                                               separator(),
    //                                               thoat->Render(),
    //                                           }) |
    //                                           xflex | size(WIDTH, EQUAL, 100) | size(HEIGHT, EQUAL, 50) | border | hcenter; });

    screen.Loop(main_page_layout);
    // Med_record_UI(*patient);
}