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

inline string toLowerCase(const string &str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}