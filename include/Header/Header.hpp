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
// #include <Library/Graphics.hpp>
// #include <Library/Mouse.hpp>
#define BASE_YEAR 1900
using namespace std;

#define WHITE "FFFFFF"
#define RED "FF4C4C"
#define GREEN "15B392"
#define BLUE "08C2FF"
#define YELLOW "FCCD2A"
#define BLACK "000000"
#define PINK "FFCCEA"
#define GREY "686D76"
#define ORANGE "FF8225"
#define PURPLE "615EFC"
#define DATA_PATH_MACRO(x) DATA_PATH "/" x
// int safe_stoi(const std::string &str) {
//     try {
//         return std::stoi(str);
//     } catch (const std::invalid_argument& e) {
//         std::cerr << "Lỗi: Chuỗi không hợp lệ để chuyển đổi thành số nguyên: " << e.what() << std::endl;
//         return 0; // Giá trị mặc định hoặc xử lý lỗi
//     }
// }