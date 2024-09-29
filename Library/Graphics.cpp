#include "./Graphics.h"

//* Lấy tọa độ x của con trỏ hiện tại 
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

//* Lấy tọa độ y của con trỏ hiện tại 
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

//* Lấy vị trí dòng hiện tại của con trỏ màn hình trong Console
int getCurrentCursorPositionY(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}

//* Dịch con trỏ hiện tại đến điểm có tọa độ (x, y) 
void gotoXY(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) }; // Chuyển kiểu dữ liệu từ int sang SHORT
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

//* Đặt màu cho chữ 
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

//* Làm ẩn trỏ chuột 
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

//* Trả về mã phím người dùng bấm 
int inputKey()
{
	if (_kbhit()) //true
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}
	return KEY_NONE;
}

//* Đặt màu cho chuỗi 
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

//* Hàm vẽ box mà không có nội dung
void boxNot(int x, int y, int w, int h, int t_color, int b_color){
	textcolor(b_color);
	for(int iy = y + 1; iy <= y + h - 1; iy++){
		for(int ix = x + 1; ix <= x + w - 1; ix++){
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	textcolor(1);
	SetColor(t_color);
	for (int ix = x; ix <= x + w; ix++){
        gotoXY(ix, y);
        cout << char(196);
        gotoXY(ix, y + h);
        cout << char(196);
    }

    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << char(179);
        gotoXY(x + w, iy);
        cout << char(179);
    }

    gotoXY(x, y); cout << char(218);
    gotoXY(x + w, y); cout << char (191);
    gotoXY(x, y + h); cout << char(192);
    gotoXY(x + w, y + h); cout << char (217);
}

void boxNot_(int x, int y, int w, int h, int t_color, int b_color){
	textcolor(b_color);
	for(int iy = y + 1; iy <= y + h - 1; iy++){
		for(int ix = x + 1; ix <= x + w - 1; ix++){
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	textcolor(1);
	SetColor(t_color);
	for (int ix = x; ix <= x + w; ix++){
        gotoXY(ix, y);
        cout << char(205);
        gotoXY(ix, y + h);
        cout << char(205);
    }

    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << char(186);
        gotoXY(x + w, iy);
        cout << char(186);
    }

    gotoXY(x, y); cout << char(201);
    gotoXY(x + w, y); cout << char (187);
    gotoXY(x, y + h); cout << char(200);
    gotoXY(x + w, y + h); cout << char (188);
}

//* Hàm vẽ box có nội dung
void box(int x, int y, int w, int h, int t_color, int b_color, int content_color, string content){
	textcolor(b_color);
	for(int iy = y + 1; iy <= y + h - 1; iy++){
		for(int ix = x + 1; ix <= x + w - 1; ix++){
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	SetColor(content_color);
	gotoXY(x + 1, y + 1);
	cout << content;
	textcolor(1);
	SetColor(t_color);
	for (int ix = x; ix <= x + w; ix++){
        gotoXY(ix, y);
        cout << char(196);
        gotoXY(ix, y + h);
        cout << char(196);
    }

    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << char(179);
        gotoXY(x + w, iy);
        cout << char(179);
    }

    gotoXY(x, y); cout << char(218);
    gotoXY(x + w, y); cout << char (191);
    gotoXY(x, y + h); cout << char(192);
    gotoXY(x + w, y + h); cout << char (217);
}

void box_(int x, int y, int w, int h, int t_color, int b_color, int content_color, string content){
	textcolor(b_color);
	for(int iy = y + 1; iy <= y + h - 1; iy++){
		for(int ix = x + 1; ix <= x + w - 1; ix++){
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	SetColor(content_color);
	gotoXY(x + 1, y + 1);
	cout << content;
	textcolor(1);
	SetColor(t_color);
	for (int ix = x; ix <= x + w; ix++){
        gotoXY(ix, y);
        cout << char(205);
        gotoXY(ix, y + h);
        cout << char(205);
    }

    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << char(186);
        gotoXY(x + w, iy);
        cout << char(186);
    }

    gotoXY(x, y); cout << char(201);
    gotoXY(x + w, y); cout << char (187);
    gotoXY(x, y + h); cout << char(200);
    gotoXY(x + w, y + h); cout << char (188);
}

//* Hàm di chuyển đối tượng và trả về vị trí mới khi phím Enter được nhấn
int move(int x, int y, int h, int &yp, int &kt, int soKhung){
	if(_kbhit()){
		int c = _getch();
		if(c == 224){
			kt = true;
			c = _getch();
			if(c == 72 && yp != y){
				yp -= 2;
			}else if(c == 72 && yp == y){
				yp = y + h * (2 - 1);
			}else if(c == 80 && yp != y + h * (soKhung - 1)){
				yp += 2;
			}else if(c == 80 && yp == y + h * (soKhung - 1)){
				yp = y;
			} 
		}else if(c == 13){
			kt = false;
			return yp;
		}
	}
	return yp;
}
