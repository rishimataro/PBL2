#include "Interface/Admin_interface.hpp"
bool valid_password(const string &password)
{
    if (password.length() < 8)
    {
        return false;
    }
    if (!regex_search(password, regex("[a-zA-Z]")))
    {
        return false;
    }
    if (!regex_search(password, regex("[0-9]")))
    {
        return false;
    }
    if (!regex_search(password, regex("[!@#$%^&*()_+=-\\[\\]{};':\"\\\\|,.<>/?]")))
    {
        return false;
    }
    return true;
}
inline bool ValidateDate(const string &date)
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
string create_Patient_title(const Patient &patient)
{
    string id = patient.getID_patient();
    string dayOfBirth = patient.getDayOfBirth().getDate();
    string fullName = patient.getFullName();
    string gender = (patient.getGender()) ? "Nữ " : "Nam";
    // return (patient.getID_patient() + " " + " " + patient.getDayOfBirth().getDate() + " " + (patient.getGender() ? "Nữ" : "Nam") + patient.getFullName() + (string(' ', 30 - patient.getFullName().length())));
    return (id + string(7 - id.length(), ' ') + " " + dayOfBirth + "     " + gender + "     " + fullName);
}
string create_med_record_title(const MedicalRecord &record, listPatient &patients)
{
    vector<Patient *> filtered_patients = patients.searchPatient(SearchField::ID, record.getID_patient());
    if (filtered_patients.empty())
    {
        return "";
    }
    else
    {
        string rec_id = record.getID_record();
        string patient_id = record.getID_patient();
        string patient_name = filtered_patients[0]->getFullName();
        string date = record.getDateOfRecord().getDate();
        return (rec_id + string(7 - rec_id.length(), ' ') + " " + patient_id + string(7 - rec_id.length(), ' ') + date + "     " + patient_name);
        // return (record.getID_record() + "    " + record.getID_patient() + "    " + filtered_patients[0]->getFullName() + "      " + record.getDateOfRecord().getDate());
    }
}
void create_admin_account(listAccount &accounts)
{
    auto screen = ScreenInteractive::Fullscreen();
    string username, password, confirm_password;
    ftxui::InputOption input_pw_opt;
    input_pw_opt.password = true;
    string alert;
    Component create_admin_account_form =
        Container::Vertical({
            Renderer([&]()
                     { return vbox({
                           text("Tạo tài khoản quản trị") | bold | center,
                           separator(),
                       }); }),
            Container::Horizontal({
                Renderer([&]()
                         { return vbox({
                               text("Username:"),
                               text("Password:"),
                               text("Confirm Password:"),
                           }); }),
                Renderer([&]()
                         { return separator(); }),
                Container::Vertical({
                    Input(&username, "Username", input_pw_opt),
                    Input(&password, "Password", input_pw_opt),
                    Input(&confirm_password, "Confirm Password", input_pw_opt),
                }) | size(WIDTH, EQUAL, 63) |
                    hcenter,

            }),

        }) |
        border | size(HEIGHT, EQUAL, 7) | hcenter;
    Element alert_element = text(alert);
    Component main_layout = Container::Vertical({
                                create_admin_account_form,
                                Renderer([&]()
                                         { return vbox({
                                               alert_element,
                                           }); }) |
                                    hcenter,
                                Container::Horizontal({
                                    Button("    Quay lại   ", [&]()
                                           { screen.ExitLoopClosure()(); }),
                                    Renderer([&]()
                                             { return separatorEmpty() | size(WIDTH, EQUAL, 8); }),

                                    Button("Tạo tài khoản", [&]()
                                           {
                    if (password.empty() || confirm_password.empty())
                        {
                            alert_element = text("Mật khẩu không được để trống!") | color(Color::Red);
                        }
                        else if (password != confirm_password)
                        {
                            alert_element = text("Vui lòng nhập lại mật khẩu đúng.") | color(Color::Red);
                        }
                        else if (!valid_password(password))
                        {
                            alert_element = text("Mật khẩu phải có ít nhất 8 kí tự, bao gồm chữ cái, số và kí tự đặc biệt!") | color(Color::Red);
                        }
                        else{
                            Account *new_account = nullptr;
                            if(accounts.allocateAdminAccount(new_account, username, password) == 1)
                            {
                                alert = "Tạo tài khoản thành công!";
                                alert_element = text("Tạo tài khoản thành công!") | color(Color::Green);
                            }
                        } }),
                                }) | hcenter,
                            }) |
                            hcenter;
    screen.Loop(main_layout);
}
bool change_password_UI(Account *&account, listPatient &patients)
{
    auto screen = ScreenInteractive::Fullscreen();
    string old_password, new_password, confirm_password;
    Component account_info;
    if (account->getID().find("ADMIN") != string::npos)
    {
        account_info = Renderer([&]()
                                { return vbox({text("Tài khoản quản trị") | bold | center,
                                               separator(),
                                               hbox({text("Mã tài khoản:"),
                                                     // separator(),
                                                     text(account->getID())})}); });
    }
    else if (account->getID().find("USER") != string::npos)
    {
        AccountUser *user = dynamic_cast<AccountUser *>(account);
        vector<Patient *> filtered_patients = patients.searchPatient(SearchField::ID, user->getID_patient());
        Patient *selected_patient = filtered_patients[0];
        account_info = Renderer([&]()
                                { return vbox({
                                      text("Tài khoản bệnh nhân") | bold | center,
                                      separator(),
                                      hbox({vbox({
                                                text("Mã tài khoản:"),
                                                text("Mã bệnh nhân:"),
                                                text("Tên bệnh nhân:"),
                                                text("Số định danh:"),
                                            }),
                                            separator(),
                                            vbox({
                                                text(account->getID()),
                                                text(selected_patient->getID_patient()),
                                                text(selected_patient->getFullName()),
                                                text(selected_patient->getCCCD()),
                                            })}),
                                      separator(),
                                  }); });
    }
    ftxui::InputOption input_pw_opt;
    input_pw_opt.password = true;
    string change_password_msg = "";
    bool status = false;
    Component change_password_layout = Container::Vertical({
                                           account_info,
                                           Input(&old_password, "Mật khẩu cũ:", input_pw_opt),
                                           Input(&new_password, "Mật khẩu mới:", input_pw_opt),
                                           Input(&confirm_password, "Xác nhận mật khẩu:", input_pw_opt),

                                           Renderer([&]()
                                                    { return vbox({
                                                          text(change_password_msg) | color(Color::Red) | center,
                                                          separator(),
                                                      }); }),
                                           Container::Horizontal({
                                               Button("Trở về", [&]()
                                                      { screen.ExitLoopClosure()(); }),
                                               Button("Cập nhật", [&]()
                                                      { 
                                                         if (old_password.empty() || new_password.empty() || confirm_password.empty())
                                                         {
                                                            change_password_msg = "Mật khẩu không được để trống!";
                                                         }
                                                         else if (account->getPassword() != old_password)
                                                          {
                                                              change_password_msg = "Mật khẩu cũ không đúng!";
                                                          }
                                                          else if (new_password != confirm_password)
                                                          {
                                                              change_password_msg = "Vui lòng nhập lại mật khẩu đúng.";
                                                          }
                                                          else if (!valid_password(new_password))
                                                          {
                                                              change_password_msg = "Mật khẩu phải có ít nhất 8 ký tự,\nbao gồm chữ cái, số và ký tự đặc biệt!";
                                                          }
                                                          else
                                                          {
                                                              account->setPassword(new_password);
                                                              status = true;
                                                              change_password_msg = "Cập nhật mật khẩu thành công!";
                                                          } }),
                                           }) | hcenter,

                                       }) |
                                       border | size(WIDTH, EQUAL, 80) | size(HEIGHT, EQUAL, 20) | center;
    screen.Loop(change_password_layout);
    return status;
}
void QLTK(listPatient &listPatient)
{
    listAccount accounts;
    auto screen = ScreenInteractive::Fullscreen();
    int page_id = 0;
    auto create_admin_acc_btn = Button("Cấp tài khoản quản trị", [&]()
                                       { create_admin_account(accounts); });
    auto change_admin_pas_btm = Button("Cấp lại mật khẩu", [&]()
                                       { page_id = 1; });
    auto exit_btn = Button("Thoát", [&]()
                           { screen.Exit(); });
    Component Menu_layout = Container::Vertical({
                                Renderer([&]()
                                         { return vbox({
                                               text("Quản lý tài khoản") | bold | center,
                                               separator(),
                                           }); }),
                                create_admin_acc_btn,
                                change_admin_pas_btm,
                                Renderer([&]()
                                         { return vbox({
                                               separator(),
                                           }); }),
                                exit_btn,
                            }) |
                            border | size(WIDTH, EQUAL, 80);
    string username;
    string noti = "";
    vector<Account *> filtered_accounts;
    Component search_account_layout = Container::Vertical({
                                          Renderer([&]()
                                                   { return vbox({
                                                         text("Tìm kiếm tài khoản"),
                                                         separator(),
                                                     }); }),
                                          Input(&username, "Username") | border | size(WIDTH, EQUAL, 70) | hcenter,
                                          Renderer([&]()
                                                   { return vbox({
                                                         text(noti) | color(Color::Red),
                                                         separator(),
                                                     }); }),
                                          Container::Horizontal({
                                              Button("Trở về", [&]()
                                                     { page_id = 0; }),
                                              Renderer([&]
                                                       { return separatorEmpty() | size(WIDTH, EQUAL, 8); }),
                                              Button("Tìm kiếm", [&]()
                                                     {
                filtered_accounts = accounts.searchAccount(SearchField_acc::UserName, username);
                if (filtered_accounts.empty() || (filtered_accounts[0]->getUserName()!= username))
                {
                    noti = "Không tìm thấy tài khoản";
                }
                else
                {   

                    if(change_password_UI(filtered_accounts[0], listPatient))
                    {
                        accounts.updateAccountByID(filtered_accounts[0]->getID(), filtered_accounts[0]->getUserName(), filtered_accounts[0]->getPassword());
                    }
                } }),
                                          }) | hcenter,
                                      }) |
                                      border | size(WIDTH, EQUAL, 80) | hcenter;

    Component tab_layout = Container::Tab({
                                              Menu_layout,
                                              search_account_layout,
                                          },
                                          &page_id);
    screen.Loop(tab_layout);
}
void Analyse_UI()
{
    listMedicalRecord M_records;
    M_records.readListMedicalRecordFromFile();
    vector<pair<string, int>> diagnosisCount;
    diagnosisCount = M_records.setDiagnosisCount();
    int sum = 0;
    for (auto &pair : diagnosisCount)
    {
        sum += pair.second;
    }
    map<string, pair<int, double>> Diagnosis_percentage_count;
    for (auto &pair : diagnosisCount)
    {
        Diagnosis_percentage_count[pair.first] = make_pair(pair.second, (double)pair.second / sum * 100);
    }
    vector<vector<string>> table_data;
    table_data.push_back({"           Tên bệnh           ", "    Số lượt mắc    ", "(%)     "});
    for (auto &[key, value] : Diagnosis_percentage_count)
    {
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
    Component exit_btn = Button("Thoát", [&]()
                                { screen.ExitLoopClosure()(); });
    Component main_layout = Container::Vertical({
                                Renderer([&]
                                         { return document; }),
                                Renderer([&]
                                         { return separator(); }),
                                exit_btn,
                            }) |
                            size(WIDTH, EQUAL, 60) | border | hcenter;
    Component main_layout_renderer = Renderer(main_layout, [&]
                                              { return main_layout->Render(); });
    screen.Loop(main_layout_renderer);
}
void QLBA_UI(listPatient &patients)
{
    auto screen = ScreenInteractive::Fullscreen();
    int popup_level = 0;
    string MR_ID_query;
    string PT_ID_query;
    string loai_benh_query;
    listMedicalRecord M_records;
    // M_records.readListMedicalRecordFromFile();
    vector<MedicalRecord *> filtered_records;
    MedicalRecord *selected_record = nullptr;
    int search_mode = 0;

    Component mr_rec_btn = Container::Vertical({});

    Component MR_ID_input = Input(&MR_ID_query, "Mã bệnh án");
    Component PT_ID_input = Input(&PT_ID_query, "Mã bệnh nhân");
    Component loai_benh_input = Input(&loai_benh_query, "Loại bệnh");
    auto create_rec_btn = [&]()
    {
        for (auto &record : filtered_records)
        {
            mr_rec_btn->Add(Button(create_med_record_title(*record, patients), [&]()
                                   { selected_record = record; }, Btn_animated_opt1()));
        }
    };
    auto search_by_MR_ID = [&]()
    {
        filtered_records = M_records.searchMedicalRecord(SearchField_MR::RecordID, MR_ID_query);
        create_rec_btn();
        search_mode = 1;
        popup_level = 1;
    };
    auto search_by_PT_ID = [&]()
    {
        filtered_records = M_records.searchMedicalRecord(SearchField_MR::PatientID, PT_ID_query);
        create_rec_btn();
        search_mode = 2;
        popup_level = 1;
    };
    auto search_by_loai_benh = [&]()
    {
        filtered_records = M_records.searchMedicalRecord(SearchField_MR::Diagnosis, loai_benh_query);
        create_rec_btn();
        search_mode = 3;
        popup_level = 1;
    };
    Component MR_ID_search_btn = Button("Tìm theo bệnh án", search_by_MR_ID); // Btn_animated_opt1()
    Component PT_ID_search_btn = Button("Tìm theo bệnh nhân", search_by_PT_ID);
    Component loai_benh_search_btn = Button("Tìm theo loại bệnh", search_by_loai_benh);

    Component back_btn1 = Button("Quay lại", [&]()
                                 { screen.ExitLoopClosure()(); });

    Component search_layout = Container::Vertical({
                                  Renderer([&]()
                                           { return vbox({
                                                 text("Tìm kiếm bệnh án:") | color(Color::Green),
                                                 separator(),
                                             }); }),
                                  Container::Horizontal({MR_ID_input | size(WIDTH, EQUAL, 40),
                                                         MR_ID_search_btn | size(WIDTH, EQUAL, 25)}),
                                  Container::Horizontal({PT_ID_input | size(WIDTH, EQUAL, 40),
                                                         PT_ID_search_btn | size(WIDTH, EQUAL, 25)}),
                                  Container::Horizontal({loai_benh_input | size(WIDTH, EQUAL, 40),
                                                         loai_benh_search_btn | size(WIDTH, EQUAL, 25)}),
                                  Renderer([&]()
                                           { return separator(); }),
                                  back_btn1 | hcenter,
                              }) |
                              border | hcenter;
    Component back_btn2 = Button("Quay lại", [&]()
                                 {
        mr_rec_btn->DetachAllChildren();
        popup_level = 0; });
    Component search_result_layout = Container::Vertical({
        Renderer([&]()
                 { return text("Kết quả tìm kiếm:") | color(Color::Green); }),
        mr_rec_btn | vscroll_indicator | frame |
            size(HEIGHT, EQUAL, 20) | border,
        back_btn2 | hcenter,

    });

    Component search_scr_render = Renderer(search_layout, [&]()
                                           { return search_layout->Render(); });
    Component search_result_scr_render = Renderer(search_result_layout, [&]()
                                                  { return search_result_layout->Render(); });
    Component page_container = Container::Tab({
                                                  search_scr_render,
                                                  search_result_scr_render,
                                              },
                                              &popup_level);
    Component main_layout = Renderer(page_container, [&]
                                     { return vbox({
                                           page_container->Render(),
                                       }); });
    screen.Loop(main_layout);
}
void QLBN_searchBN(listPatient &patients)
{
    auto screen = ScreenInteractive::Fullscreen();
    int popup_level = 0;
    string Name_value;
    string ID_value;
    string start_Date_value;
    string end_Date_value;
    // listPatient patients;
    Patient *selected_patient = nullptr;
    // patients.readListPatientFromFile();
    vector<Patient *> filtered_patients;
    ofstream out("test_log.txt", ios::app);
    out << patients.size() << endl;
    Component QLBN_name_input = Input(&Name_value, "Tên bệnh nhân");
    Component QLBN_id_input = Input(&ID_value, "ID bệnh nhân");

    Component patient_btn = Container::Vertical({});

    Component QLBN_start_date_input = Input(&start_Date_value, "Ngày bắt đầu");
    auto start_date_msg = Renderer([&]
                                   { return text((ValidateDate(start_Date_value)) ? " " : "Ngày bắt đầu không hợp lệ") | color(Color::Red); });
    Component QLBN_end_date_input = Input(&end_Date_value, "Ngày kết thúc");
    auto end_date_msg = Renderer([&]
                                 { return text((ValidateDate(end_Date_value)) ? " " : "Ngày kết thúc không hợp lệ") | color(Color::Red); });
    // Tìm bệnh nhân theo tên, ID, và ngày sinh
    int search_mode = 0;
    auto search_by_name = [&]()
    {
        filtered_patients = patients.searchPatient(SearchField::FullName, Name_value);
        popup_level = 1;
        for (auto &patient : filtered_patients)
        {
            patient_btn->Add(Button(create_Patient_title(*patient), [&]()
                                    {
                                        selected_patient = patient;
                                        // popup_level = 2;
                                    },
                                    Btn_animated_opt1()));
        }
        search_mode = 1;
    };
    auto search_by_id = [&]()
    {
        filtered_patients = patients.searchPatient(SearchField::ID, ID_value);
        popup_level = 1;
        for (auto &patient : filtered_patients)
        {
            patient_btn->Add(Button(create_Patient_title(*patient), [&]()
                                    {
                                        selected_patient = patient;
                                        // popup_level = 2;
                                    },
                                    Btn_animated_opt1()));
        }
        search_mode = 2;
    };
    auto search_by_date = [&]()
    {
        filtered_patients = patients.setPatientByBirthRange(start_Date_value, end_Date_value);
        popup_level = 1;
        for (auto &patient : filtered_patients)
        {
            patient_btn->Add(Button(create_Patient_title(*patient), [&]()
                                    {
                                        selected_patient = patient;
                                        // popup_level = 2;
                                    },
                                    Btn_animated_opt1()));
        }
        search_mode = 3;
    };
    Component QLBN_name_search_btn = Button("Tìm theo tên", search_by_name);
    Component QLBN_id_search_btn = Button("Tìm theo ID", search_by_id);
    Component QLBN_date_search_btn = Button("Tìm theo ngày sinh", search_by_date);

    Component Exit_btn = Button("Thoát", [&]()
                                { screen.ExitLoopClosure()(); });
    Component Back_btn1 = Button("Quay lại", [&]()
                                 { 
        patient_btn->DetachAllChildren();
        popup_level = 0; });

    Component edit_ptn_info_btn =
        Button("Sửa thông tin", [&]()
               {
                   if (selected_patient != nullptr)
                   {
                       Patientdisplay(selected_patient);
                       patients.clear();
                       patients.readListPatientFromFile();
                       patient_btn->DetachAllChildren();
                       if (search_mode == 1)
                           search_by_name();
                       else if (search_mode == 2)
                           search_by_id();
                       else if (search_mode == 3)
                           search_by_date();
                   }

                   // popup_level = 0;
               });
    Component search_layout = Container::Vertical({
                                  Renderer([&]()
                                           { return vbox({
                                                 text("Tìm kiếm bệnh nhân:"),
                                                 separator(),
                                             }); }),
                                  Container::Horizontal({
                                      QLBN_name_input | size(WIDTH, EQUAL, 37) | center,
                                      Renderer([&]()
                                               { return separator(); }),
                                      QLBN_name_search_btn | size(WIDTH, EQUAL, 22) | center,
                                  }),
                                  Renderer([&]()
                                           { return separator(); }),
                                  Container::Horizontal({
                                      QLBN_id_input | size(WIDTH, EQUAL, 37),
                                      Renderer([&]()
                                               { return separator(); }),
                                      QLBN_id_search_btn | size(WIDTH, EQUAL, 22),
                                  }),
                                  Renderer([&]()
                                           { return separator(); }),
                                  Container::Horizontal({
                                      Container::Vertical({
                                          QLBN_start_date_input | size(WIDTH, EQUAL, 37) | size(HEIGHT, EQUAL, 3) | center,
                                          start_date_msg,
                                          Renderer([&]()
                                                   { return separator(); }),
                                          QLBN_end_date_input | size(WIDTH, EQUAL, 37) | size(HEIGHT, EQUAL, 3) | center,
                                          end_date_msg,
                                      }) | size(HEIGHT, EQUAL, 9),
                                      Renderer([&]()
                                               { return separator(); }),
                                      QLBN_date_search_btn | size(WIDTH, EQUAL, 22) | center,
                                  }),
                                  Renderer([&]()
                                           { return separator(); }),
                                  Exit_btn | hcenter,
                              }) |
                              border | hcenter;

    Component search_result_layout = Container::Vertical({
        patient_btn | vscroll_indicator | frame |
            size(HEIGHT, EQUAL, 15) | border,
        edit_ptn_info_btn | hcenter,
        Back_btn1 | hcenter,
    });

    Component search_layout_render = Renderer(search_layout, [&]
                                              { return search_layout->Render(); });
    Component search_result_renderer = Renderer(search_result_layout, [&]
                                                { return search_result_layout->Render(); });
    Component page_container = Container::Tab({
                                                  search_layout_render,
                                                  search_result_renderer,
                                              },
                                              &popup_level);

    Component main_layout = Renderer(page_container, [&]
                                     { return vbox({
                                           page_container->Render(),
                                       }); });
    screen.Loop(main_layout);
    // screen.Loop(search_layout_render);
}
void QLBN_UI(listPatient &patients)
{
    auto screen = ScreenInteractive::Fullscreen();

    Component QLBN_timBN_btn = Button("Tìm kiếm bệnh nhân", [&]()
                                      { QLBN_searchBN(patients); });
    Component QLBN_thongKe_btn = Button("Thống kê bệnh nhân", [&]() {});
    Component QLBN_thoat_btn = Button("Trở về", [&]()
                                      { screen.ExitLoopClosure()(); });

    Component layout = Container::Vertical({QLBN_timBN_btn,
                                            QLBN_thongKe_btn,
                                            QLBN_thoat_btn});

    Component render = Renderer(layout, [&]
                                { return vbox({
                                             text("Quản lý bệnh nhân"),
                                             separator(),
                                             QLBN_timBN_btn->Render(),
                                             QLBN_thongKe_btn->Render(),
                                             QLBN_thoat_btn->Render() | hcenter,
                                         }) |
                                         size(WIDTH, EQUAL, 80) | border | hcenter; });
    screen.Loop(render);
}
void Admin_UI()
{
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    listPatient admin_ListPatient;
    // admin_ListPatient.readListPatientFromFile();
    Component QL_benhNhan = Button("Quản lý bệnh nhân", [&]()
                                   { QLBN_UI(admin_ListPatient); });
    Component QL_taikhoan = Button("Quản lý tài khoản", [&]()
                                   { QLTK(admin_ListPatient); });
    Component QL_benhAn = Button("Quản lý bệnh án", [&]()
                                 { QLBA_UI(admin_ListPatient); });
    Component Kham_benh = Button("Khám bệnh", [&]() {});
    Component ThongKe = Button("Thống kê", [&]()
                               { Analyse_UI(); });
    Component Thoat = Button("Đăng xuất", [&]()
                             { screen.ExitLoopClosure()(); });

    Component layout = Container::Vertical({QL_benhNhan,
                                            QL_taikhoan,
                                            QL_benhAn,
                                            Kham_benh,
                                            ThongKe,
                                            Thoat});

    Component render = Renderer(layout, [&]
                                { return vbox({
                                             text("Hệ thống quản lý phòng khám"),
                                             separator(),
                                             QL_benhNhan->Render(),
                                             QL_taikhoan->Render(),
                                             QL_benhAn->Render(),
                                             Kham_benh->Render(),
                                             ThongKe->Render(),
                                             separator(),
                                             Thoat->Render() | hcenter,
                                         }) |
                                         size(WIDTH, EQUAL, 80) | border | hcenter; });
    screen.Loop(render);
    admin_ListPatient.writeListPatientToFile(1);
}