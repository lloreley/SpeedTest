#include "../include/Text.hpp"

Text::Text()
{
    Logger::getInstance()("Basic constructor for Text was worked");
}

Text::Text(const char *buffer) : text(buffer)
{
}

Text::Text(const Text &buffer) : text(buffer.text)
{
    Logger::getInstance()("Constructor for Text with const Text&");
}

Text::~Text()
{
    Logger::getInstance()("Destructor for Text was worked");
}

std::ostream &operator<<(std::ostream &stream, Text &Text)
{
    return stream << Text.text;
}

void Text::loadFromFile(const char *filename)
{
    std::ifstream ifs(filename);

    if (ifs.is_open())
    {
        while (!ifs.eof())
        {
            String buff;
            ifs >> buff;
            this->text += buff;
            this->text += String(" ");
        }
    }
    else throw "error";
}
void Text::inputFromKeyboard(std::istream istream)
{
    istream>>text;   
}
bool Text::compare(const Text &other) const noexcept
{
    return this->text == other.text;
}
