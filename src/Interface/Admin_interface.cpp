#include "Interface/Admin_interface.hpp"

inline bool ValidateDate(const string& date) {
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
string create_Patient_title(const Patient& patient) {
    return (patient.getID_patient() + " " + patient.getFullName() + (string(' ' ,30 - patient.getFullName().length())) + " " + patient.getDayOfBirth().getDate() + " " + (patient.getGender()? "Nữ" : "Nam"));

}
string create_med_record_title(const MedicalRecord& record) {
    fstream fi;
    path file_path = "../Database/PatientDB/";
    file_path.append(record.getID_patient() + ".txt");
    fi.open(file_path);
    Patient pt;
    pt.readPatientFromFile(fi);
    fi.close();
    return (record.getID_record() + "    " + record.getID_patient() + "    " + pt.getFullName() + "      " + record.getDateOfRecord().getDate());
    // return "test";
}
// void Kham_benh()
// {
//     auto screen = ScreenInteractive::TerminalOutput();
//     map<string, vector<string>> lichKham;
//     Date today;
//     today.setCurrentDate();
//     Appoinment app_s;
//     app_s.setDate(today);
//     app_s.DocFileLich(lichKham);
//     vector<Appoinment> danhSachLich;
//     // if(lichKham.find(today.getDate())!= lichKham.end())
//     // {
//     //     danhSachLich = lichKham[today.getDate()];
//     // }
//     // Component Appoinment_cancel_renderer;
//     //ID  Ngày  Thời gian
//     // vector<string> App_list;
//     Element header_text = text("Danh sách lịch khám") | bold | center;
//     Element tb_text = text("   Mã lịch khám   Ngày   Thời gian") | bold;
//     // for(auto& app : danhSachLich)
//     // {
//     //     App_list.push_back("  " + app.getID() + "        " + (app.getDate().getDate()) + "       " + GioKham(app.getTime()) + (app.getStatus()? "Còn hiệu lực" : "Đã hủy"));
//     // }
//     int selected = 1;
//     int popup_level = 0;
//     Appoinment *selected_app;
//     // auto Create_App_cancel = [&screen, &patient](Appoinment& app) {
    
//     // };
//     Component Menu_app_list = Container::Vertical({});
    
//     for(auto& app : danhSachLich)
//     {   
//         auto tmp_btn = Button(("  " + app.getID() + "        " + (app.getDate().getDate()) + "       " + GioKham(app.getTime()) + "            " + (app.getStatus()? "Hiệu lực" : " Đã hủy")), [&]() {
//             selected_app = &app; // gán lịch khám đã chọn
//             popup_level = 1;
//         }, Btn_animated_opt1());
//         Menu_app_list->Add(tmp_btn);
    
//     }
//     // Menu_app_list->;
//     Component exit_btn = Button("Quay lại", [&]{
//         screen.ExitLoopClosure()();
//     }, btn_style1());
//     Component Menu_app = Container::Vertical({
//         Menu_app_list,
//         exit_btn,
//     });
//     auto menu_app_list_renderer = Renderer(Menu_app, [&] {
//         // return window(
//             // text("Danh sách lịch khám") | bold | center,
//         return vbox({
//             // separator(),
//             hbox({
//                 text("Mã lịch khám"), 
//                 separatorEmpty() | size(WIDTH, EQUAL, 10), 
//                 text("Ngày"), 
//                 separatorEmpty() | size(WIDTH, EQUAL, 13), 
//                 text("Giờ khám"),
//                 separatorEmpty() | size(WIDTH, EQUAL, 13),
//                 text("Trạng thái"),
//                 // separatorEmpty() | size(WIDTH, EQUAL, 10),
//             }),
//             separator(),
//             Menu_app_list->Render(),
//             separator(),
//             exit_btn->Render() | hcenter,
//             }//)
//         );
//     });
// }
void Statistics()
{
    listMedicalRecord M_records;
    M_records.readListMedicalRecordFromFile();
    vector<pair<string, int>> diagnosisCount;
    diagnosisCount = M_records.setDiagnosisCount();
    int sum = 0;
    for (auto& pair : diagnosisCount) {
        sum += pair.second;
    }
    map<string, pair<int, double>> Diagnosis_percentage_count;
    for (auto& pair : diagnosisCount) {
        Diagnosis_percentage_count[pair.first] = make_pair(pair.second, (double)pair.second / sum * 100);
    }
    vector<vector<string>> table_data;
    table_data.push_back({"           Tên bệnh           ", "    Số lượt mắc    ", "(%)     "});
    for (auto& [key, value] : Diagnosis_percentage_count) {
        vector<string> row = {key, to_string(value.first), format("{:.2f}", value.second) + "%"};
        table_data.push_back(row);
    }
    auto table = Table(table_data);
    table.SelectAll().Border(LIGHT);
    table.SelectRow(0).BorderBottom(LIGHT);
    table.SelectColumns(0, 2).SeparatorVertical(LIGHT);
    auto document = table.Render();
    // auto screen = Screen::Create(Dimension::Fit(document));
    // Render(screen, document);
    // screen.Print();
    // cout << endl;
    auto screen = ScreenInteractive::Fullscreen();
    Component exit_btn = Button("Thoát", [&]() {screen.ExitLoopClosure()(); });
    Component main_layout = Container::Vertical({
        Renderer([&]{ return document;}),
        Renderer([&]{ return separator(); }),
        exit_btn,
    }) | size(WIDTH, EQUAL, 60) | border | hcenter;
    Component main_layout_renderer = Renderer(main_layout, [&]{
        return main_layout->Render();
    });
    screen.Loop(main_layout_renderer);

}
void QLBA_UI()
{   
    auto screen = ScreenInteractive::Fullscreen();
    int popup_level = 0;
    string MR_ID_query;
    string PT_ID_query;
    string loai_benh_query;
    listMedicalRecord M_records;
    M_records.readListMedicalRecordFromFile();
    vector<MedicalRecord> filtered_records;
    MedicalRecord *selected_record = nullptr;
    int search_mode = 0;

    Component mr_rec_btn = Container::Vertical({});

    Component MR_ID_input = Input(&MR_ID_query, "Mã bệnh án");
    Component PT_ID_input = Input(&PT_ID_query, "Mã bệnh nhân");
    Component loai_benh_input = Input(&loai_benh_query, "Loại bệnh");
    auto search_by_MR_ID =  [&]() {
        filtered_records = M_records.searchMedicalRecord(SearchField_MR::RecordID, MR_ID_query);
        for(auto& record : filtered_records) {
            mr_rec_btn->Add(Button(create_med_record_title(record), [&]() {
                selected_record = &record;
        },Btn_animated_opt1()));
        }
        search_mode = 1;
        popup_level = 1;
    };
    auto search_by_PT_ID =  [&]() {
        filtered_records = M_records.searchMedicalRecord(SearchField_MR::PatientID, PT_ID_query);
        for(auto& record : filtered_records) {
            mr_rec_btn->Add(Button(create_med_record_title(record), [&]() {
                selected_record = &record;
                // popup_level = 2;
            }, Btn_animated_opt1()));
        }
        search_mode = 2;
        popup_level = 1;
    };
    auto search_by_loai_benh =  [&]() {
        filtered_records = M_records.searchMedicalRecord(SearchField_MR::Diagnosis, loai_benh_query);
        for(auto& record : filtered_records) {
            mr_rec_btn->Add(Button(create_med_record_title(record), [&]() {
                selected_record = &record;
        },Btn_animated_opt1()));
        }
        search_mode = 3;
        popup_level = 1;
    };
    Component MR_ID_search_btn = Button("Tìm theo bệnh án", search_by_MR_ID, Btn_animated_opt1());
    Component PT_ID_search_btn = Button("Tìm theo bệnh nhân", search_by_PT_ID, Btn_animated_opt1());
    Component loai_benh_search_btn = Button("Tìm theo loại bệnh", search_by_loai_benh, Btn_animated_opt1());

    Component back_btn1 = Button("Quay lại", [&]() {screen.ExitLoopClosure()(); });
    
    Component search_layout = Container::Vertical({
        Container::Horizontal({
            MR_ID_input | size(WIDTH, EQUAL, 40),
            MR_ID_search_btn | size(WIDTH, EQUAL, 25)
        }),
        Container::Horizontal({
            PT_ID_input | size(WIDTH, EQUAL, 40),
            PT_ID_search_btn | size(WIDTH, EQUAL, 25)
        }),
        Container::Horizontal({
            loai_benh_input | size(WIDTH, EQUAL, 40),
            loai_benh_search_btn | size(WIDTH, EQUAL, 25)
        }),
        Renderer([&]() {return separator();}),
        back_btn1 | hcenter,
    }) | border | hcenter;
    Component back_btn2 = Button("Quay lại", [&]() {
        mr_rec_btn->DetachAllChildren();
        popup_level = 0; });
    Component search_result_layout = Container::Vertical({
        Renderer([&]() {return text("Kết quả tìm kiếm:") | color(Color::Green);}),
        mr_rec_btn | vscroll_indicator | frame |
           size(HEIGHT, EQUAL, 20) | border,
        back_btn2 | hcenter,

    });

    Component search_scr_render = Renderer(search_layout, [&]() {
        return search_layout->Render();
    });
    Component search_result_scr_render = Renderer(search_result_layout, [&]() {
        return search_result_layout->Render();
    });
    Component page_container = Container::Tab({
        search_scr_render,
        search_result_scr_render,
    }, &popup_level);
    Component main_layout = Renderer(page_container, [&]{
        return vbox({
            page_container->Render(),
        });
    });
    screen.Loop(main_layout);
}
void QLBN_searchBN()
{
    auto screen = ScreenInteractive::Fullscreen();
    int popup_level = 0;
    string Name_value;
    string ID_value;
    string start_Date_value;
    string end_Date_value;
    listPatient patients;
    Patient *selected_patient = nullptr;
    patients.readListPatientFromFile();
    vector<Patient> filtered_patients;

    Component QLBN_name_input = Input(&Name_value, "Tên bệnh nhân");
    Component QLBN_id_input = Input(&ID_value, "ID bệnh nhân");

    Component patient_btn = Container::Vertical({});

    Component QLBN_start_date_input = Input(&start_Date_value, "Ngày bắt đầu");
    auto start_date_msg = Renderer([&] {
        return text((ValidateDate(start_Date_value)) ? " " : "Ngày bắt đầu không hợp lệ") | color(Color::Red);
    });
    Component QLBN_end_date_input = Input(&end_Date_value, "Ngày kết thúc");
    auto end_date_msg = Renderer([&] {
        return text((ValidateDate(end_Date_value)) ? " " : "Ngày kết thúc không hợp lệ") | color(Color::Red);
    });
    //Tìm bệnh nhân theo tên, ID, và ngày sinh
    int search_mode = 0;
    auto search_by_name =  [&]() {
        filtered_patients = patients.searchPatient(SearchField::FullName, Name_value);
        popup_level = 1;
        for (auto& patient : filtered_patients) {
            patient_btn->Add(Button(create_Patient_title(patient), [&]() {
                selected_patient = &patient;
                // popup_level = 2;
            }, Btn_animated_opt1()));
        }
        search_mode = 1;
    };
    auto search_by_id = [&]() {
        filtered_patients = patients.searchPatient(SearchField::ID, ID_value);
        popup_level = 1;
        for (auto& patient : filtered_patients) {
            patient_btn->Add(Button(create_Patient_title(patient), [&]() {
                selected_patient = &patient;
                // popup_level = 2;
            }, Btn_animated_opt1()));
        }
        search_mode = 2;
    };
    auto search_by_date = [&]() {
        filtered_patients = patients.setPatientByBirthRange(start_Date_value, end_Date_value);
        popup_level = 1;
        for (auto& patient : filtered_patients) {
            patient_btn->Add(Button(create_Patient_title(patient), [&]() {
                selected_patient = &patient;
                // popup_level = 2;
            }, Btn_animated_opt1()));
        }
        search_mode = 3;
    };
    Component QLBN_name_search_btn = Button("Tìm theo tên", search_by_name);
    Component QLBN_id_search_btn = Button("Tìm theo ID", search_by_id);
    Component QLBN_date_search_btn = Button("Tìm theo ngày sinh", search_by_date);

    Component Exit_btn = Button("Thoát", [&]() { screen.ExitLoopClosure()(); });
    Component Back_btn1 = Button("Quay lại", [&]() { 
        patient_btn->DetachAllChildren();
        popup_level = 0; });

    Component edit_ptn_info_btn = Button("Sửa thông tin", [&]() {
        if(selected_patient!= nullptr)
        {
            Patientdisplay(*selected_patient);
            patients.clear();
            patients.readListPatientFromFile();
            patient_btn->DetachAllChildren();
            if(search_mode == 1) search_by_name();
            else if (search_mode == 2) search_by_id();
            else if (search_mode == 3) search_by_date();
        }

        // popup_level = 0;
    });
    Component search_layout = Container::Vertical({
        Container::Horizontal({
            QLBN_name_input | size(WIDTH, EQUAL, 37) | center,
            Renderer([&]() {return separator();}),
            QLBN_name_search_btn | size(WIDTH, EQUAL, 22) | center,
        }),
        Renderer([&]() {return separator();}),
        Container::Horizontal({
            QLBN_id_input | size(WIDTH, EQUAL, 37),
            Renderer([&]() {return separator();}),
            QLBN_id_search_btn | size(WIDTH, EQUAL, 22),
        }),
        Renderer([&]() {return separator();}),
        Container::Horizontal({
            Container::Vertical({
                QLBN_start_date_input | size(WIDTH, EQUAL, 37) | size(HEIGHT, EQUAL, 3) | center,
                start_date_msg,
                Renderer([&]() {return separator();}),
                QLBN_end_date_input | size(WIDTH, EQUAL, 37) | size(HEIGHT, EQUAL, 3) | center,
                end_date_msg,
            }) | size(HEIGHT, EQUAL, 9),
            Renderer([&]() {return separator();}),
            QLBN_date_search_btn | size(WIDTH, EQUAL, 22) | center,
        }),
        Renderer([&]() {return separator();}),
        Exit_btn | hcenter,
    }) | border | hcenter;

    Component search_result_layout = Container::Vertical({
        patient_btn | vscroll_indicator | frame |
           size(HEIGHT, EQUAL, 15) | border,
        edit_ptn_info_btn | hcenter,    
        Back_btn1 | hcenter,
    });



    Component search_layout_render = Renderer(search_layout, [&]{
        return search_layout->Render();
    });
    Component search_result_renderer = Renderer(search_result_layout, [&]{
        return search_result_layout->Render();
    });
    Component page_container = Container::Tab({
        search_layout_render,
        search_result_renderer,
    }, &popup_level);

    Component main_layout = Renderer(page_container, [&]{
        return vbox({
            page_container->Render(),
        });
    });
    screen.Loop(main_layout);
    // screen.Loop(search_layout_render);
}
void QLBN_UI()
{
    auto screen = ScreenInteractive::Fullscreen();

    Component QLBN_timBN_btn = Button("Tìm kiếm bệnh nhân", [&]() {QLBN_searchBN(); });
    Component QLBN_thongKe_btn = Button("Thống kê bệnh nhân", [&]() { });
    Component QLBN_thoat_btn = Button("Trở về", [&]() { screen.ExitLoopClosure()(); });
    
    Component layout = Container::Vertical({
        QLBN_timBN_btn,
        QLBN_thongKe_btn,
        QLBN_thoat_btn
    });
    
    Component render = Renderer(layout,[&]{
        return vbox({
            text("Quản lý bệnh nhân"),
            separator(),
            QLBN_timBN_btn->Render(),
            QLBN_thongKe_btn->Render(),
            QLBN_thoat_btn->Render() | hcenter,
        }) | size(WIDTH, EQUAL, 80) | border | hcenter;
    });
    screen.Loop(render);
}
void Admin_UI()
{
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    
    Component QL_benhNhan = Button("Quản lý bệnh nhân", [&]() {QLBN_UI(); });
    Component QL_taikhoan = Button("Quản lý tài khoản", [&]() { });
    Component QL_benhAn = Button("Quản lý bệnh án", [&]() { QLBA_UI(); });
    Component Kham_benh = Button("Khám bệnh", [&]() { });
    Component ThongKe = Button("Thống kê", [&]() { Statistics();});
    Component Thoat = Button("Đăng xuất", [&]() { screen.ExitLoopClosure()(); });
    
    Component layout = Container::Vertical({
        QL_benhNhan,
        QL_taikhoan,
        QL_benhAn,
        Kham_benh,
        ThongKe,
        Thoat
    });

    Component render = Renderer(layout,[&]{
        return vbox({
            text("Hệ thống quản lý phòng khám"),
            separator(),
            QL_benhNhan->Render(),
            QL_taikhoan->Render(),
            QL_benhAn->Render(),
            Kham_benh->Render(),
            ThongKe->Render(),
            separator(),
            Thoat->Render() | hcenter,
        }) | size(WIDTH, EQUAL, 80) | border | hcenter;
    });
    screen.Loop(render);
}