#include "Interface/Admin_interface.hpp"
bool _valid_password(const string &password)
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
                        else if (!_valid_password(password))
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
                                        //    Input(&old_password, "Mật khẩu cũ:", input_pw_opt),
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
                                                        //  else if (account->getPassword() != old_password)
                                                        //   {
                                                        //       change_password_msg = "Mật khẩu cũ không đúng!";
                                                        //   }
                                                          else if (new_password != confirm_password)
                                                          {
                                                              change_password_msg = "Vui lòng nhập lại mật khẩu đúng.";
                                                          }
                                                          else if (!_valid_password(new_password))
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
void TK_ten_benh()
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
    // ofstream out("test_log.txt", ios::app);
    // out << patients.size() << endl;
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
vector<string> splitTextIntoLines(const string& text, int boxWidth) {
    vector<string> lines;
    int startIndex = 0;
    int textLength = text.length();

    while (startIndex < textLength) 
    {
        // Xác định chiều dài dòng hiện tại
        int endIndex = startIndex + boxWidth;

        // Kiểm tra nếu endIndex vượt quá chiều dài của chuỗi
        if (endIndex >= textLength) {
            endIndex = textLength;
        } else {
            // Lùi lại để tìm khoảng trắng gần nhất nếu có
            while (endIndex > startIndex && text[endIndex] != ' ') {
                endIndex--;
            }

            // Nếu không tìm thấy khoảng trắng, giữ nguyên chiều dài mặc định
            if (endIndex == startIndex) {
                endIndex = startIndex + boxWidth;
            }
        }

        // Lấy đoạn văn bản từ startIndex đến endIndex
        string line = text.substr(startIndex, endIndex - startIndex);
        lines.push_back(line);

        // Bỏ qua dấu cách ở đầu dòng tiếp theo (nếu có)
        startIndex = endIndex;
        while (startIndex < textLength && text[startIndex] == ' ') {
            startIndex++;
        }
    }
    return lines;
}
string split_text(string text, int width)
{
    vector<string> lines = splitTextIntoLines(text, width);
    string result = "";
    for (const auto& line : lines) {
        result += line + "\n";
    }
    return result;
}
string delete_break_line(string text)
{
    size_t pos = 0;
    while (((pos = text.find('\n', pos))!= std::string::npos) || ((pos = text.find('\r', pos))!= std::string::npos)) {
        text.erase(pos, 1);
    }
    return text;
}
void Kham_benh_UI(Patient* &patient, Appoinment* &selected_app, listAppoinment &Appoinments)
{   
    listMedicalRecord medicalRecords;
    map<string, string> solution_hint = medicalRecords.getSymptomSolutions();
    auto screen = ScreenInteractive::Fullscreen();
    Component Patient_id = Wrap("Mã bệnh nhân:", Renderer([&]
                                                          { return text(patient->getID_patient()); }));
    Component Full_name = Wrap("Họ và tên:", Renderer([&]()
                                                      { return text(patient->getFullName()); }));
    Component Phone_number = Wrap("Số điện thoại:", Renderer([&]
                                                             { return text(patient->getPhone()); }));
    Component DOB = Wrap("Ngày sinh:", Renderer([&]()
                                                { return text(patient->getDayOfBirth().getDate()); }));
    Component CCCD = Wrap("CCCD:", Renderer([&]()
                                            { return text(patient->getCCCD()); }));
    string Gender = (patient->getGender() ? "Nữ" : "Nam");
    Component Patient_gender = Wrap("Giới tính:", Renderer([&]()
                                                           { return text(Gender); }));
    Component Address = Wrap("Địa chỉ:", Renderer([&]()
                                                  { return text(patient->getAddress()); }));
    Component a_ID = Wrap("Mã lịch khám:", Renderer([&]()
                                                    { return text((*selected_app).getID()); }));
    Component Symptom_text = Wrap("Triệu chứng:", Renderer([&]()
                                                           { return paragraph((*selected_app).getDescription()); }));
    string symptom, diagnosis, solution, msg_text = "";
    Element msg = text(msg_text) | color(Color::Green);
    Component msg_comp = Renderer([&]() {return msg;});
    Component info_layout = Container::Vertical({
        Patient_id,
        Full_name,
        Phone_number,
        DOB,
        CCCD,
        Patient_gender,
        Address,
        a_ID,
        Symptom_text,
    });
    Component input_layout = Container::Vertical({
        Renderer([&](){
            return vbox({
                text("Triệu chứng:"),
                // separator(),
            });
        }),
        Input(&symptom, "Triệu chứng") | size(HEIGHT, GREATER_THAN, 1),
        Renderer([&](){
            return vbox({
                separator(),
                text("Chẩn đoán:"),
            });
        }),
        Input(&diagnosis, "Chẩn đoán") | size(HEIGHT, GREATER_THAN, 1),
        Renderer([&](){
            return vbox({
                separator(),
                text("Hướng điều trị:"),
            });
        }),
        Input(&solution, "Hướng điều trị") | size(HEIGHT, GREATER_THAN, 1),
    });
    Component button_layout = Container::Horizontal({
        Button("Quay lại", [&]() { screen.ExitLoopClosure()(); }),
        Button("Lưu và ghi đè hướng dẫn", [&]() {
            Date date;
            date.setCurrentDate();
            string save_symptom, save_diagnosis, save_solution;
            save_symptom = delete_break_line(symptom);
            save_diagnosis = delete_break_line(diagnosis);
            save_solution = delete_break_line(solution);
            solution_hint[save_symptom] = save_solution;
            medicalRecords.addMedicalRecord(patient->getID_patient(), save_symptom, save_diagnosis, date.getDate());
            selected_app->setIsProcessed(true);
            // Appoinments.writeAppointmentsToFile();
            msg = text("Đã lưu thông tin khám bệnh thành công!") | color(Color::Green);
        }),
    });
    Component exam_layout = Container::Vertical({
        info_layout | border,
        input_layout | border,
        msg_comp,
        button_layout,
    
    }) | border | size(WIDTH, EQUAL, 80) ;
    Component hint_button = Container::Vertical({});
    for (const auto& it : solution_hint) {
        hint_button->Add(Button(it.first, [&](){diagnosis = it.first; solution = it.second; }, Btn_animated_opt1()));
    }
    Component hint_layout = Container::Vertical({
        Renderer([&](){return vbox({
            text("Gợi ý hướng điều trị:"),
            separator(),
        });}),
        hint_button | vscroll_indicator | frame,
    }) | border | size(WIDTH, EQUAL, 80);
    Component main_layout = Container::Horizontal({
        exam_layout,
        hint_layout | align_right,
        });
    screen.Loop(main_layout);
}
void Chọn_lich_kham_UI(listPatient &patients)
{
    auto screen = ScreenInteractive::Fullscreen();
    listAppoinment appointments;
    Date today;
    today.setCurrentDate();
    string current_date = today.getDate();
    vector<Appoinment*> today_appointments = appointments.getAppointmentsByDateRange(current_date, current_date);
    Appoinment *selected_appoinment = nullptr;
    Patient *selected_patient = nullptr;
    vector<Patient*> filtered_patients;
    Component appointment_list = Container::Vertical({});
    for(auto &app : today_appointments)
    {   
        if(app->getStatus() && !app->getIsProcessed())
        {   
            filtered_patients = patients.searchPatient(SearchField::ID, app->getPatientID());
            string fullname = filtered_patients[0]->getFullName();
            string Patient_id = filtered_patients[0]->getID_patient();
            appointment_list->Add(Button(("  " + app->getID() + "   " + (app->getDate().getDate()) + "    " + GioKham(app->getTime()) + "       " + Patient_id + string(8- Patient_id.size(), ' ') + fullname), 
            [&](){
                selected_appoinment = app;
                selected_patient = filtered_patients[0];
                Kham_benh_UI(selected_patient, selected_appoinment, appointments);
        }, Btn_animated_opt1()));
        }
    }
    Element header_text = text("Danh sách lịch khám") | bold | center;
    Element tb_text = text(" Mã lịch khám    Ngày hẹn        Giờ hẹn    Mã bệnh nhân  Tên bệnh nhân") | bold;
    //| vscroll_indicator | frame |
    Component exit_btn = Button("Quay lại", [&]
                                { screen.ExitLoopClosure()(); }, btn_style1());
    Component app_list_layout = Container::Vertical({
        Container::Vertical({
            Renderer([&](){
            return vbox({
                header_text | hcenter,
                separator(),
                tb_text,
                separator(),
            });
        }),
        appointment_list | vscroll_indicator | frame,
        }) | size(HEIGHT, GREATER_THAN, 3) | border | hcenter,
        exit_btn | hcenter,
    }) |size(WIDTH, GREATER_THAN, 80)| hcenter;
    screen.Loop(app_list_layout);
}
void TK_Tuoi_GT(listPatient &patients)
{
    ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    Date today;
    today.setCurrentDate();
    Date _18_sai = today;
    Date _60_sai = today;
    _18_sai.setYear(today.getYear() - 18);
    _60_sai.setYear(today.getYear() - 60);
    if (isLeapYear(today.getYear()) && today.getMonth() == 2 && today.getDay() == 29)
    {
        if(!isLeapYear(_18_sai.getYear()))
        {
            _18_sai.setDay(28);
        }
        if(!isLeapYear(_60_sai.getYear()))
        {
            _60_sai.setDay(28);
        }
    }
    int count_18 = 0, count_18_m = 0, count_18_f = 0, count_60 = 0, count_60_m = 0, count_60_f = 0, count_60p = 0, count_60p_m = 0, count_60p_f = 0;
    int total = patients.size();

    for (int i = 0; i < total; i++)
    {   
        Patient *patient = patients.get(i);
        if(patient->getDayOfBirth() >= _18_sai)
        {
            count_18++;
            if(patients.get(i)->getGender() == 0)
            {
                count_18_m++;
            }
            else
            {
                count_18_f++;
            }
        }else
        if (patient->getDayOfBirth() <= _60_sai)
        {
            count_60p++;
            if(patients.get(i)->getGender() == 0)
            {
                count_60p_m++;
            }
            else
            {
                count_60p_f++;
            }
            
        }else
        {
            count_60++;
            if(patients.get(i)->getGender() == 0)
            {
                count_60_m++;
            }
            else
            {
                count_60_f++;
            }
            
        }
        
    }
    Component table = Renderer([&](){
        return vbox({
            hbox({
            text("Độ tuổi") | size(WIDTH, EQUAL, 17),
            separator(),
            text("Số lượng") | size(WIDTH, EQUAL, 8),
            separator(),
            text("Tỷ lệ") | size(WIDTH, EQUAL, 7) | hcenter,
            separator(),
            text("Giới tính") | size(WIDTH, EQUAL, 9),
            separator(),
            text("Số lượng") | size(WIDTH, EQUAL, 15),
            separator(),
            text("Tỷ lệ/độ tuổi") | size(WIDTH, EQUAL, 13),
            separator(),
            text("Tỷ lệ/tổng số") | size(WIDTH, EQUAL, 13),
            }),
            separator(),
            hbox({
                text("Dưới 18 tuổi") | size(WIDTH, EQUAL, 17) | vcenter,
                separator(),
                text(to_string(count_18)) | size(WIDTH, EQUAL, 8) | vcenter | hcenter,
                separator(),
                text(format("{:.2f}",(double) ((total != 0) ? (100* count_18 / total) : 0)) + "%") | size(WIDTH, EQUAL, 7) | vcenter | hcenter,
                vbox({
                    hbox({
                        separator(),
                        text("Nam") | size(WIDTH, EQUAL, 9),
                        separator(),
                        text(to_string(count_18_m)) | size(WIDTH, EQUAL, 15) | center,
                        separator(),
                        text(format("{:.2f}", (double) ((count_18 != 0) ? (100.0 * count_18_m / count_18) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        separator(),
                        text(format("{:.2f}", (double) ((total != 0) ? (100.0 * count_18_m / total) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        }),
                    separator(),
                    hbox({
                        separator(),
                        text("Nữ") | size(WIDTH, EQUAL, 9),
                        separator(),
                        text(to_string(count_18_f)) | size(WIDTH, EQUAL, 15) | center,
                        separator(),
                        text(format("{:.2f}",(double) ((count_18 != 0) ? (100.0 * count_18_f / count_18) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        separator(),
                        text(format("{:.2f}", (double) ((total != 0) ? (100.0 * count_18_f / total) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        }),
                    })
            }),
            separator(),
            hbox({
                text("Từ 18 đến 60 tuổi") | size(WIDTH, EQUAL, 17) | vcenter,
                separator(),
                text(to_string(count_60)) | size(WIDTH, EQUAL, 8) | vcenter | hcenter,
                separator(),
                text(format("{:.2f}", (double) ((total != 0) ? (100.0 * count_60 / total) : 0)) + "%") | size(WIDTH, EQUAL, 7) | vcenter | hcenter,
                vbox({
                    hbox({
                        separator(),
                        text("Nam") | size(WIDTH, EQUAL, 9),
                        separator(),
                        text(to_string(count_60_m)) | size(WIDTH, EQUAL, 15),
                        separator(),
                        text(format("{:.2f}",(double) ((count_60 != 0) ? (100.0 * count_60_m / count_60) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        separator(),
                        text(format("{:.2f}",(double) ((total != 0) ? (100.0 * count_60_m / total) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        }),
                        separator(),
                    hbox({
                        separator(),
                        text("Nữ") | size(WIDTH, EQUAL, 9),
                        separator(),
                        text(to_string(count_60_f)) | size(WIDTH, EQUAL, 15),
                        separator(),
                        text(format("{:.2f}", (double) ((count_60 != 0) ? (100.0 * count_60_f / count_60) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        separator(),
                        text(format("{:.2f}", (double) ((total != 0 ) ? (100.0 * count_60_f / total) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        }),
                    })
                }),
            separator(),
            hbox({
                text("Trên 60 tuổi") | size(WIDTH, EQUAL, 17) | vcenter,
                separator(),
                text(to_string(count_60p)) | size(WIDTH, EQUAL, 8) | vcenter | hcenter,
                separator(),
                text(format("{:.2f}", (double) ((total != 0 ) ? (100.0 * count_60p / total) : 0)) + "%") | size(WIDTH, EQUAL, 7) | vcenter | hcenter,
                vbox({
                    hbox({
                        separator(),
                        text("Nam") | size(WIDTH, EQUAL, 9),
                        separator(),
                        text(to_string(count_60p_m)) | size(WIDTH, EQUAL, 15),
                        separator(),
                        text(format("{:.2f}", (double) ((count_60p != 0) ? (100.0 * count_60p_m / count_60p) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        separator(),
                        text(format("{:.2f}", (double) ((total != 0 ) ? (100.0 * count_60p_m / total) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        }),
                        separator(),
                    hbox({
                        separator(),
                        text("Nữ") | size(WIDTH, EQUAL, 9),
                        separator(),
                        text(to_string(count_60p_f)) | size(WIDTH, EQUAL, 15),
                        separator(),
                        text(format("{:.2f}", (double) ((count_60p != 0) ? (100.0 * count_60p_f / count_60p) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        separator(),
                        text(format("{:.2f}", (double) ((total != 0 ) ? (100.0 * count_60p_f / total) : 0)) + "%") | size(WIDTH, EQUAL, 13),
                        }),
                    }),
            }),
    });
    }) | border | hcenter;
    Component layout = Container::Vertical({
        table,
        Button("Thoát", [&]() { screen.ExitLoopClosure()(); }) | hcenter,
    });
    screen.Loop(layout);
    
}
void Thong_ke_lich_kham()
{
    listAppoinment Appointments;
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    vector<Appoinment*> filteredAppoinments;
    int count[8][9];
    
    string start_date, end_date;
    start_date = "01/01/1900";
    Date startDate, endDate;
    endDate.setCurrentDate();
    end_date = endDate.getDate();
    auto count_process = [&]() -> void{
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 9; j++)
                count[i][j] = 0;
        }
        filteredAppoinments = Appointments.getAppointmentsByDateRange(start_date, end_date);
        for(auto &appoinment : filteredAppoinments)
        {
            count[appoinment->getTime()][appoinment->getDate().getWeekDay()]++;
        }
        for(int i = 0; i < 7; i++)
        {
            count[i][8]+= count[i][0] + count[i][1] + count[i][2] + count[i][3] + count[i][4] + count[i][5] + count[i][6];
            
        }
        for(int j = 0; j < 9; j++)
        {
            count[7][j]+= count[0][j] + count[1][j] + count[2][j] + count[3][j] + count[4][j] + count[5][j] + count[6][j];
        }
    };
    count_process();
    const int x_1 = 13;
    auto table_element = [&](string thu, int i) -> Element {
        return hbox({
                text(thu) | size(WIDTH, EQUAL, x_1) | size(HEIGHT, EQUAL, 2) | vcenter,
                separator(),
                vbox({
                    hbox({
                        text("Số lượng") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[i][0])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[i][1])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[i][2])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[i][3])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[i][4])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[i][5])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[i][6])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[i][7])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[i][8])) | size(WIDTH, EQUAL, x_1),
                        }),
                    separator(),
                    hbox({
                        text("Tỷ lệ") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[i][8] != 0) ? (100 * count[i][0] / count[i][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[i][8] != 0) ? (100 * count[i][1] / count[i][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[i][8] != 0) ? (100 * count[i][2] / count[i][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[i][8] != 0) ? (100 * count[i][3] / count[i][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[i][8] != 0) ? (100 * count[i][4] / count[i][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[i][8] != 0) ? (100 * count[i][5] / count[i][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[i][8] != 0) ? (100 * count[i][6] / count[i][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[i][8] != 0) ? (100 * count[i][7] / count[i][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[i][8] != 0) ? (100 * count[i][8] / count[7][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        // separator(),
                        }),
                    })
                });
    };
    // Element thu2 = table_element("Thứ 2", 1);
    Component table = Renderer([&](){
        return vbox({
            hbox({
                text("")|size(WIDTH, EQUAL, 27),
                separator(),
                text("07:30 - 08:30")|size(WIDTH, EQUAL, x_1),
                separator(),
                text("08:30 - 09:30")|size(WIDTH, EQUAL, x_1),
                separator(),
                text("09:30 - 10:30")|size(WIDTH, EQUAL, x_1),
                separator(),
                text("10:30 - 11:30")|size(WIDTH, EQUAL, x_1),
                separator(),
                text("13:30 - 14:30")|size(WIDTH, EQUAL, x_1),
                separator(),
                text("14:30 - 15:30")|size(WIDTH, EQUAL, x_1),
                separator(),
                text("15:30 - 16:30")|size(WIDTH, EQUAL, x_1),
                separator(),
                text("16:30 - 17:00")|size(WIDTH, EQUAL, x_1),
                separator(),
                text("Ngày/Tuần")|size(WIDTH, EQUAL, x_1),
            }),
            separator(),
            table_element("Thứ 2", 1),
            separator(),
            table_element("Thứ 3", 2),
            separator(),
            table_element("Thứ 4", 3),
            separator(),
            table_element("Thứ 5", 4),
            separator(),
            table_element("Thứ 6", 5),
            separator(),
            table_element("Thứ 7", 6),
            separator(),
            table_element("Chủ nhật", 0),
            separator(),
            hbox({
                text("") | size(WIDTH, EQUAL, x_1) | size(HEIGHT, EQUAL, 2) | vcenter,
                separator(),
                vbox({
                    hbox({
                        text("Tổng số") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[7][0])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[7][1])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[7][2])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[7][3])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[7][4])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[7][5])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[7][6])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[7][7])) | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(to_string(count[7][8])) | size(WIDTH, EQUAL, x_1),
                        }),
                    separator(),
                    hbox({
                        text("Tỷ lệ/tuần") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[7][8] != 0) ? (100 * count[7][0] / count[7][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[7][8] != 0) ? (100 * count[7][1] / count[7][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[7][8] != 0) ? (100 * count[7][2] / count[7][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[7][8] != 0) ? (100 * count[7][3] / count[7][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[7][8] != 0) ? (100 * count[7][4] / count[7][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[7][8] != 0) ? (100 * count[7][5] / count[7][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[7][8] != 0) ? (100 * count[7][6] / count[7][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[7][8] != 0) ? (100 * count[7][7] / count[7][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        separator(),
                        text(format("{:.2f}", ((double) ((count[7][8] != 0) ? (100 * count[7][8] / count[7][8]) : 0) )) + "%") | size(WIDTH, EQUAL, x_1),
                        // separator(),
                        }),
                    })
            })
        }) | border | size(WIDTH, EQUAL, (25 + x_1 * 10)) | size(HEIGHT, EQUAL, 33) | hcenter;
    });
    Component msg1 = Renderer([&]{return text(((ValidateDate(start_date) ? "" : "Ngày bắt đầu không hợp lệ!")));}) | color(Color::Red);
    Component msg2 = Renderer([&]{return text(((ValidateDate(end_date) ? "" : "Ngày kết thúc không hợp lệ!")));}) | color(Color::Red);
    Component input_start_date = Input(&start_date, "dd/mm/yyyy");
    Component input_end_date = Input(&end_date, "dd/mm/yyyy");
    Component layout = Container::Vertical({
        Container::Horizontal({
            Container::Vertical({
                Renderer([&]{return text("Ngày bắt đầu:");}),
                Input(&start_date, "dd/mm/yyyy"),
                msg1,
            }) | size(WIDTH, EQUAL, 40),
            Container::Vertical({
                Renderer([&]{return text("Ngày kết thúc:");}),
                Input(&end_date, "dd/mm/yyyy"),
                msg2,
            }) | size(WIDTH, EQUAL, 40),
            Renderer([&]{return separatorEmpty() | size(WIDTH, EQUAL, 20);}),
            Button(" Tìm kiếm ", [&]() { if(ValidateDate(start_date) && ValidateDate(end_date)) {count_process();} }) | align_right,
        }) | border |  size(WIDTH, EQUAL, (25 + x_1 * 10)) | hcenter,
        table,
        Button("Trở về", [&]() { screen.ExitLoopClosure()(); }) | hcenter,
    });
    screen.Loop(layout);
}
void Thong_ke_UI(listPatient &Patients)
{
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    Component ThongKe_ten_benh = Button("Thống kê theo tên bệnh", [&]()
                                             { TK_ten_benh(); });
    Component ThongKe_GT_DT= Button("Thống kê theo độ tuổi và giới tính", [&]()
                                              {  TK_Tuoi_GT(Patients);});
    
    Component ThongKe_ngay_gio_cao_diem = Button("Thống kê ngày cao điểm trong tuần", [&]()
                                               { Thong_ke_lich_kham(); });
    Component layout = Container::Vertical({
        Renderer([&](){return vbox({
            text("Thống kê"),
            separator(),
        });
    }),
        ThongKe_ten_benh,
        ThongKe_GT_DT,
        ThongKe_ngay_gio_cao_diem,
    }) | border | size(WIDTH, GREATER_THAN, 80);
    screen.Loop(layout);
}
void Admin_UI()
{
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    listPatient admin_ListPatient;
    // admin_ListPatient.readListPatientFromFile();
    Component QL_benhNhan = Button("Quản lý bệnh nhân", [&]()
                                   { QLBN_searchBN(admin_ListPatient); });
    Component QL_taikhoan = Button("Quản lý tài khoản", [&]()
                                   { QLTK(admin_ListPatient); });
    Component QL_benhAn = Button("Quản lý bệnh án", [&]()
                                 { QLBA_UI(admin_ListPatient); });
    Component Kham_benh = Button("Khám bệnh", [&]() {
        Chọn_lich_kham_UI(admin_ListPatient); });
    Component ThongKe = Button("Thống kê", [&]()
                               { Thong_ke_UI(admin_ListPatient); });
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