#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <functional>
#include <filesystem>
#include <regex>
#define BASE_YEAR 1900
using namespace std;
namespace fs = std::filesystem;

inline string toLowerCase(const string &str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
inline int safe_stoi(const string &str) {
    try {
        return stoi(str);
    } catch (const invalid_argument& e) {
        cerr << "Lỗi: Chuỗi không hợp lệ để chuyển đổi thành số nguyên: " << e.what() << endl;
        return 0;
    }
}
inline bool valid_password(const string& password) {
    if (password.length() < 8) {
        return false;
    }
    if (!regex_search(password, regex("[a-zA-Z]"))) {
        return false;
    }
    if (!regex_search(password, regex("[0-9]"))) {
        return false;
    }
    if (!regex_search(password, regex("[!@#$%^&*()_+=-\\[\\]{};':\"\\\\|,.<>/?]"))) {
        return false;
    }
    return true;
    
}
#endif