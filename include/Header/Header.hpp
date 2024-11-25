#pragma once
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