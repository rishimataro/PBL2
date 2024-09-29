#pragma once
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <iostream>
#include "windows.h" 
#define KEY_NONE	-1
using namespace std;

//* Hàm lấy tọa độ x của con trỏ hiện tại
int whereX();

//* Hàm lấy tọa độ y của con trỏ hiện tại
int whereY();

//* Hàm lấy vị trí dòng hiện tại của con trỏ màn hình trong Console
int getCurrentCursorPositionY();

//* Hàm dịch con trỏ hiện tại đến điểm có tọa độ (x, y)
void gotoXY(int x, int y);

//* Hàm đặt màu cho chữ
void SetColor(WORD color);

//* Hàm làm ẩn trỏ chuột
void ShowCur(bool CursorVisibility);

//* Hàm trả về mã phím người dùng bấm
int inputKey();

//* Hàm đặt màu cho chuỗi
void textcolor(int x);

//* Hàm vẽ box mà không có nội dung
void boxNot(int x, int y, int w, int h, int t_color, int b_color);  // 1 gạch
void boxNot_(int x, int y, int w, int h, int t_color, int b_color); // 2 gạch

//* Hàm vẽ box có nội dung
void box(int x, int y, int w, int h, int t_color, int b_color, int content_color, string content);  // 1 gạch
void box_(int x, int y, int w, int h, int t_color, int b_color, int content_color, string content); // 2 gạch

//* Hàm di chuyển đối tượng và trả về vị trí mới khi phím Enter được nhấn
int move(int x, int y, int h, int &yp, int &kt, int soKhung);
