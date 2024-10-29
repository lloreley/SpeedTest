#ifndef BASIC
#define BASIC

#include <iostream>
#include <limits>
#include <vector>

using std::ifstream;
using std::numeric_limits;
using std::vector;
using std::ifstream;
using std::ostream;


int getAmountWordsInFile(const char *fileName);

template<typename T>
ostream &operator<<(ostream &stream, vector<T> &words)
{
    //because compiler have a problems with detecting what is a member function
    //and what is a type name, when inside template.
    typename vector<T>::iterator it;  
    for (it = words.begin(); it != words.end(); ++it)
    {
        stream << *it << " ";
    }
    return stream;
}

template<typename T>
void fillVectorFromFile(vector<T> &vec, const char *fileName)
{
    ifstream ifs(fileName);
    T value;
    if (ifs.is_open())
    {
        while (!ifs.eof())
        {
            ifs >> value;
            if (value)
                vec.push_back(value);
        }
    }
}

#endif