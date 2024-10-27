#include "Graphics.h"

class textBox{
    private:
    int x, y, width, height;
    string content;
    string textColor, backgroundColor, borderColor;
    public:
    textBox(int x, int y, int width, int height, string content = "", string textColor = "FFFFFF", string backgroundColor = "000000", string borderColor = "FFFFFF");
    void print() const;
    void setContent(const string& newContent);
    void setTextColor(const string& newTextColor);
    void setBackgroundColor(const string& newBackgroundColor);
    void setBorderColor(const string& newBorderColor);
    ~textBox();
};