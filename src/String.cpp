//  last change 10.11.2024


//  TODO:
//      char &String::operator[](const int pos) const

#include "../include/String.hpp"

String::String()
{
    string = nullptr;
    length = 0;
}

String::String(size_t size) : String()
{
    if (size > 0)
    {
        length = size - 1;
        string = new char[size];
    }
}

String::String(const char *buffer)
{
    length = strLength(buffer);
    if (buffer)
    {
        string = new char[strSize(buffer)];
    }
    else
        string = nullptr;
    strCopy(string, buffer);
}

String::String(const String &buffer)
{
    if (buffer)
    {
        string = new char[buffer.size()];
        strCopy(string, buffer.string);
    }
    else
    {
        string = nullptr;
    }
    length = buffer.length;
}

String::~String()
{
    if (string)
        delete[] string;
}

void String::clear() noexcept
{
    if (string)
    {
        delete[] string;
        string = nullptr;
        length = 0;
    }
}

ostream &operator<<(ostream &stream, const String &string)
{
    if (!string)
        return stream << "null";
    return stream << string.string;
}

istream &operator>>(istream &stream, String &string)
{
    char test[BUFF_SIZE];
    stream.getline(test, BUFF_SIZE);
    string = test;
    return stream;
}

int String::size() const noexcept
{
    if (length != 0)
        return length + 1;
    return length;
}

int strLength(const char *buffer) noexcept
{
    int length = 0;
    if (buffer)
    {
        for (; buffer[length] != '\0'; ++length);
    }
    return length;
}

int strSize(const char *buffer) noexcept
{
    if (strLength(buffer))
        return strLength(buffer) + 1;
    return 0;
}

void strCopy(char *str1, const char *str2)
{
    for (int i = 0; i < strSize(str2); ++i)
    {
        str1[i] = str2[i];
    }
}

String operator+(String str1, String str2)
{
    str1+=str2;
    return str1;
}

String &String::operator=(const String &buffer)
{
    if (this != &buffer)
    {
        this->clear();
        if (buffer)
        {
            length = buffer.length;
            if (length)
            {
                string = new char[length];
            }
            strCopy(string, buffer.string);
        }
    }
    return *this;
}

String &String::operator=(const char *buffer)
{
    this->clear();
    if (buffer)
    {
        length = strLength(buffer);
        if (length)
        {
            string = new char[length];
        }
        strCopy(string, buffer);
    }
    return *this;
}

String &String::operator+=(const String &buffer)
{
    if (this != &buffer)
    {
        String str(*this);
        this->clear();
        length = str.length + buffer.length;
        if (length)
        {
            string = new char[this->size()];
            strCopy(string, str.string);
            for (int i = str.length, j = 0; i < length; ++i, ++j)
            {
                string[i] = buffer.string[j];
            }
            string[length] = '\0';
        }
    }
    return *this;
}

String &String::operator+=(const char *buffer)
{
    String str(*this);
    this->clear();
    length = str.length + strLength(buffer);
    if (length)
    {

        string = new char[this->size()];
        strCopy(string, str.string);
        for (int i = str.length, j = 0; i < length; ++i, ++j)
        {
            string[i] = buffer[j];
        }
        string[length] = '\0';
    }
    return *this;
}

bool String::operator==(const String &buffer) const 
{
    if (this->size() + 1 != buffer.size() + 1)
    {
        return false;
    }
    for (int i = 0; i < this->size() + 1; ++i)
    {
        if (this->string[i] != buffer.string[i])
        {
            return false;
        }
    }
    return true;
}

bool String::operator!=(const String &buffer) const
{
    return !((*this) == buffer);
}

String::operator char*() const noexcept
{
    return this->string;
}

String::operator bool() const noexcept
{
    return string;
}

String intToString(int value)
{
    stringstream sstream;
    sstream << value;
    return String(sstream.str().c_str());
}

// operator int()

//TODO 
char &String::operator[](const int pos) const
{
    if (pos >= 0 && pos < this->length)
        return string[pos];
    // throw 
    exit(1);
}


