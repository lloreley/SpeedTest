//============================INFO==============================//
//  This file contain actually written String class             //
//                                                              //
//  Types of CONSTRUCTORS:                                      //
//      default,                                                //
//      memory allocator,                                       //
//      copyconstructor from an object of this class,           //
//      copyconstructor from const char* massiv.                //
//==============================================================//
//  info about DESTRUCOTOR:                                     //
//      clears the memory allocated for the string              //
//==============================================================//
//  FUNCTION    void clear()                                    //
//      clears the memory allocated for the string and          //
//      assigns a null value to a string                        //
//==============================================================//
//  FUNCTION    int size()                                      //
//      returns the size of a string in bytes                   //
//==============================================================//
//  OVERLOADED functions/operators:                             //
//  FROM CLASS:                                                 //
//      String &operator=(const String &buffer);                //
//      String &operator=(const char *buffer);                  //
//      String &operator+=(const String &buffer);               //
//      String &operator+=(const char *buffer);                 //
//      bool operator==(const String &buffer);                  //
//      bool operator!=(const String &buffer);                  //
//      char &operator[](const int pos);                        //
//      operator bool();                                        //
//      operator char*()                                        //
//  NOT FROM CLASS:                                             //
//      ostream &operator<<(ostream &str,vector<String> &words) //
//      istream &operator>>(istream &stream, String &string);   //
//      ostream &operator<<(ostream &stream, const String &);   //
//      String operator+(String str1, String str2)              //
//==============================================================//
//  THE FOLLOWING FUNCTIONS ARE PRESENT:                        //
//      int strLength(const char *buffer);                      //
//      int strSize(const char *buffer);                        //
//      void strCopy(char *str1, const char *str2);             //
//==============================================================//

// TODO operator [](int) после создания своего класса exception
#ifndef STRING
#define STRING

#include <fstream>
#include <vector>
#include <sstream>

#define BUFF_SIZE 100

using std::ifstream;
using std::istream;
using std::ostream;
using std::vector;
using std::stringstream;

class String final
{
    friend ostream &operator<<(ostream &stream, const String &string);
    friend istream &operator>>(istream &stream, String &string);
    
private:
    char *string;
    int length;

public:
    String();
    String(size_t size);
    String(const char *);
    String(const String &);
    ~String();
    void clear() noexcept;
    int size() const noexcept;
    String &operator=(const String &buffer);
    String &operator=(const char *buffer);
    String &operator+=(const String &buffer);
    String &operator+=(const char *buffer);
    // String &operator+=(int num);
    bool operator==(const String &buffer) const;
    bool operator!=(const String &buffer) const;
    char &operator[](const int pos) const;
    operator bool() const noexcept;
    operator char *() const noexcept;
};
String operator+(String str1, String str2);
String intToString(int value);
int strLength(const char *buffer) noexcept;
int strSize(const char *buffer) noexcept;
void strCopy(char *str1, const char *str2);
#endif