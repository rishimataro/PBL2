#include "./Graphics.h"

std::string hexToRgb(std::string hex) {
    int r, g, b;
    if((hex[0] == '#' && hex.length() == 7))
    {
        hex.erase(0, 1);
    }else if(hex.length() != 6)
    return "0;0;0";
    r = std::stoi(hex.substr(0, 2), nullptr, 16); // Giá trị đỏ
    g = std::stoi(hex.substr(2, 2), nullptr, 16); // Giá trị xanh lá
    b = std::stoi(hex.substr(4, 2), nullptr, 16); // Giá trị xanh dương
    return std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b);
}

std::string setTextColor(const std::string& hexColor) {
    return "\x1b[38;2;" + hexToRgb(hexColor) + "m";
}
std::string setTextColor(const int red, const int green, const int blue) {
    return "\x1b[38;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";
}
std::string setBackgroundColor(const std::string& hexColor) {
    return "\x1b[48;2;" + hexToRgb(hexColor) + "m";
}
std::string setBackgroundColor(const int red, const int green, const int blue) {
    return "\x1b[48;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";
}
std::string resetAll() {
    return "\x1b[0m";
}
std::string setBold() {
    return "\x1b[1m";
}
std::string setUnderline() {
    return "\x1b[4m";
}
std::string setItalic() {
    return "\x1b[3m";
}
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
void textcolor(int color)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, color);
}


std::vector<std::string> splitTextIntoLines(const std::string& text, int boxWidth) {
    std::vector<std::string> lines;
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
        std::string line = text.substr(startIndex, endIndex - startIndex);
        lines.push_back(line);

        // Bỏ qua dấu cách ở đầu dòng tiếp theo (nếu có)
        startIndex = endIndex;
        while (startIndex < textLength && text[startIndex] == ' ') {
            startIndex++;
        }
    }
    return lines;
}
//* Hàm vẽ box mà không có nội dung
void emptyBox2(int x, int y, int boxWidth, int boxHeight, string backgroundColor, string borderColor)
{	
    boxWidth--;
    boxHeight--;
	cout << setBackgroundColor(backgroundColor);
	for(int iy = y + 1; iy <= y + boxHeight - 1; iy++)
	{
		for(int ix = x + 1; ix <= x + boxWidth - 1; ix++){
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	cout << setTextColor(borderColor);
	for (int ix = x; ix <= x + boxWidth; ix++)
	{
        gotoXY(ix, y);
        cout << char(196);
        gotoXY(ix, y + boxHeight);
        cout << char(196);
    }	
    for (int iy = y; iy <= y + boxHeight; iy++) 
	{
        gotoXY(x, iy);
        cout << char(179);
        gotoXY(x + boxWidth, iy);
        cout << char(179);
    }
	gotoXY(x, y); cout << char(218);
    gotoXY(x + boxWidth, y); cout << char (191);
    gotoXY(x, y + boxHeight); cout << char(192);
    gotoXY(x + boxWidth, y + boxHeight); cout << char (217);

	cout << resetAll();
}
void emptyBox2_(int x, int y, int boxWidth, int boxHeight, string backgroundColor, string borderColor)
{	
	cout << setBackgroundColor(backgroundColor);
	for(int iy = y + 1; iy <= y + boxHeight - 1; iy++)
	{
		for(int ix = x + 1; ix <= x + boxWidth - 1; ix++){
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	cout << setTextColor(borderColor);
	for (int x = x; x <= x + boxWidth; x++)
	{
        gotoXY(x, y);
        cout << char(205);
        gotoXY(x, y + boxHeight);
        cout << char(205);
    }	
    for (int y = y; y <= y + boxHeight; y++) 
	{
        gotoXY(x, y);
        cout << char(186);
        gotoXY(x + boxWidth, y);
        cout << char(186);
    }
	gotoXY(x, y); cout << char(201);
    gotoXY(x + boxWidth, y); cout << char (187);
    gotoXY(x, y + boxHeight); cout << char(200);
    gotoXY(x + boxWidth, y + boxHeight); cout << char (188);

	cout << resetAll();
}
void emptyBox(int x, int y, int w, int h, int t_color, int b_color){
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
        cout << "─";
        gotoXY(ix, y + h);
        cout << "─";
    }

    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << "│";
        gotoXY(x + w, iy);
        cout << "│";
    }

    gotoXY(x, y); cout << "┌";
    gotoXY(x + w, y); cout << "┐";
    gotoXY(x, y + h); cout << "└";
    gotoXY(x + w, y + h); cout << "┘";
}

void emptyBox_(int x, int y, int w, int h, int t_color, int b_color){
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
        cout << "═";
        gotoXY(ix, y + h);
        cout << "═";
    }

    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << "║";
        gotoXY(x + w, iy);
        cout << "║";
    }

    gotoXY(x, y); cout << "╔";
    gotoXY(x + w, y); cout << "╗";
    gotoXY(x, y + h); cout << "╚";
    gotoXY(x + w, y + h); cout << "╝";
}

//* Hàm vẽ box có nội dung
void printBox(int x, int y, int boxWidth, int boxHeight, string text, string backgroundColor, string borderColor, string textColor)
{	
	emptyBox2(x, y, boxWidth, boxHeight, backgroundColor, borderColor);
    cout << setBackgroundColor(backgroundColor);
    cout << setTextColor(textColor);
	int textLength = text.length();
	 // Ngắt văn bản thành các dòng phù hợp với boxWidth
    std::vector<std::string> lines = splitTextIntoLines(text, boxWidth - 2);
    int numLines = lines.size();
    // Tính toán khoảng trống trên và dưới để căn giữa theo chiều dọc
    int verticalPadding = (boxHeight - numLines) / 2;
    // int padd = (verticalPadding % 2 == 0)? 0 : 1;
    // In từng dòng văn bản, căn giữa theo chiều ngang
    gotoXY(x, y + verticalPadding);
    for (const std::string& line : lines) 
    {
        int padding = (boxWidth - line.length()) / 2;
        gotoXY(x + padding, whereY());
        std::cout << line << std::endl;
    }

    cout << resetAll();
    gotoXY(0, y + boxHeight + 1);
}


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
        cout << "─";
        gotoXY(ix, y + h);
        cout << "─";
    }

    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << "│";
        gotoXY(x + w, iy);
        cout << "│";
    }

    gotoXY(x, y); cout << "┌";
    gotoXY(x + w, y); cout << "┐";
    gotoXY(x, y + h); cout << "└";
    gotoXY(x + w, y + h); cout << "┘";
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
        cout << "═";
        gotoXY(ix, y + h);
        cout << "═";
    }

    for (int iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << "║";
        gotoXY(x + w, iy);
        cout << "║";
    }

    gotoXY(x, y); cout << "╔";
    gotoXY(x + w, y); cout << "╗";
    gotoXY(x, y + h); cout << "╚";
    gotoXY(x + w, y + h); cout << "╝";
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
std::string hexToRgb(std::string hex) {
    int r, g, b;
    if((hex[0] == '#' && hex.length() == 7))
    {
        hex.erase(0, 1);
    }else if(hex.length() != 6)
    return "0;0;0";
    r = std::stoi(hex.substr(0, 2), nullptr, 16); // Giá trị đỏ
    g = std::stoi(hex.substr(2, 2), nullptr, 16); // Giá trị xanh lá
    b = std::stoi(hex.substr(4, 2), nullptr, 16); // Giá trị xanh dương
    return std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b);
}

std::string setTextColor(const std::string& hexColor) {
    return "\x1b[38;2;" + hexToRgb(hexColor) + "m";
}
std::string setTextColor(const int red, const int green, const int blue) {
    return "\x1b[38;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";
}
std::string setBackgroundColor(const std::string& hexColor) {
    return "\x1b[48;2;" + hexToRgb(hexColor) + "m";
}
std::string setBackgroundColor(const int red, const int green, const int blue) {
    return "\x1b[48;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";
}
std::string resetAll() {
    return "\x1b[0m";
}
std::string setBold() {
    return "\x1b[1m";
}
std::string setUnderline() {
    return "\x1b[4m";
}
std::string setItalic() {
    return "\x1b[3m";
}

void SetConsoleSize(int width, int height) {
    // Lấy handle của cửa sổ console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Cấu hình kích thước của buffer và cửa sổ
    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}
void SetConsoleSizeAndDisableResize(int width, int height) {
    // Lấy handle của cửa sổ console
    HWND console = GetConsoleWindow();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Cấu hình kích thước của buffer và cửa sổ
    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // Tắt chế độ thay đổi kích thước
    LONG style = GetWindowLong(console, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX);  // Loại bỏ khả năng thay đổi kích thước và nút phóng to
    SetWindowLong(console, GWL_STYLE, style);
}

button::button(string text, string bgColor, string textColor, string borderColor, int x, int y, int width, int height)
    :text(text), bgColor(bgColor), textColor(textColor), borderColor(borderColor), x(x), y(y), width(width), height(height) 
{
    
}

void button::set(string text, string bgColor, string textColor, string borderColor, int x, int y, int width, int height)
{
    this->text = text;
    this->bgColor = bgColor;
    this->textColor = textColor;
    this->borderColor = borderColor;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}
void button::draw()
{
    printBox(this->x, this->y, this->width, this->height, this->text, this->bgColor, this->borderColor, this->textColor);
}
void button::changeColor(string newColor)
{
    this->bgColor = newColor;
    // draw();
}

void button::changeText(string newText)
{
    this->text = newText;
    // draw();
}
void button::changeBorderColor(string newColor)
{
    this->borderColor = newColor;
    // draw();
}

void button::move(int dx, int dy)
{
    this->x += dx;
    this->y += dy;
    // draw();
}

bool button::isClicked(int x, int y)
{
    return (x >= this->x && x <= this->x + this->width && y >= this->y && y <= this->y + this->height);
}

void button::setPosition(int x, int y)
 {
    this->x = x;
    this->y = y;
    // draw();
}

void button::reSize(int newWidth, int newHeight)
{
    this->width = newWidth;
    this->height = newHeight;
    // draw();
}
button::~button()
{

}