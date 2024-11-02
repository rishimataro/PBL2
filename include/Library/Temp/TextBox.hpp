#include "Graphics.h"
#include <cctype>
#include <locale>
#include <codecvt>
#include <map>
#include <io.h>
#include <fcntl.h>
#include <optional>
std::string WStringToUTF8(const std::wstring& wide_string);
std::wstring UTF8ToWString(const std::string& utf8_string);
void print_wstring(const std::wstring& wstr);
// Hàm kiểm tra ký tự hợp lệ
bool isValidCharacter(char32_t ch);

void setCursorPosition(string& str, int x, int y);
void setCursorPosition(wstring& str, int x, int y);
string convertTelexToVietnamese(const string& input);
void setupUtf16Console();
std::optional<wchar_t> getUnicodeCharIfPressed();
class textBox{
    private:
    int x, y, width;
    std::string content; // Giữ nguyên std::string
    std::string label; // Giữ nguyên std::string
    std::string labelColor;
    std::string textColor, backgroundColor, borderColor;
    int lengthLimit;
    bool spaceAccepted;

public:
    textBox(int x, int y, int width, std::string label = "", std::string labelColor = "FFFFFF", std::string backgroundColor = "000000", std::string borderColor = "FFFFFF");
    void show() const;
    void showLabel() const;
    void showContent() const;
    void TextColor(const std::string& newTextColor);
    void BackgroundColor(const std::string& newBackgroundColor);
    void BorderColor(const std::string& newBorderColor);
    bool isClicked(int x, int y);
    bool isClickedInside(int x, int y);
    void input();
    // void setCursorPosition();
    int currentCharacter() const;
    void setSpaceAccepted(bool newSpaceAccepted);

    std::string getContent() const;
    bool isValidCharacter(char key) const;
    bool isUtf8Character(char key) const;
    ~textBox();
};
