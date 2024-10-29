#ifndef EDITOR
#define EDITOR

#include "Text.hpp"
class Editor : public Text
{
protected:
    Text currentText;

public:
    Editor(){};
    ~Editor(){};

    void createText();
    void editText();
    void saveText(const char* filename);
};
#endif