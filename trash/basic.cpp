#include "../include/basic.hpp"

int getAmountWordsInFile(const char *fileName)
{
    int amount{};
    ifstream ifs(fileName);
    if (ifs.is_open())
    {
        while (!ifs.eof())
        {
            if (ifs.peek() == EOF)
                break;
            if (ifs.peek() != '\n')
            {
                ++amount;
            }
            ifs.ignore(numeric_limits<int>::max(), '\n');
        }
    }
    return amount;
}


