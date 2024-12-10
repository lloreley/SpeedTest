#ifndef FILE_DATA_BASE_H
#define FILE_DATA_BASE_H

#include <QDir>
#include <QString>
#include <QRegularExpression>
#include <fstream>
#include "defines.h"

class FileDataBase
{
public:
    static QString readAllFile(const QString &fileName);
    static QString extractValueFromStrWithSelector(const QString &userData, const QString &selector);
    static QString loadStyleFromFile(const QString &filePath, const QString &selector);
};

#endif