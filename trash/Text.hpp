#ifndef TEXT
#define TEXT
#include "String.hpp"
#include "Logger.hpp"

class Text
{
    friend std::ostream &operator<<(std::ostream &, Text &);

protected:
    String text;
    // vector<String> words;

public:
    Text();
    Text(const char *buffer);
    Text(const Text &buffer);
    ~Text();

    void loadFromFile(const char*filename);
    void inputFromKeyboard(std::istream istream);
    bool compare(const Text &other)  const noexcept;
};

#endif