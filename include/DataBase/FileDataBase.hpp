#ifndef FILE_DATA_BASE_H
#define FILE_DATA_BASE_H

#include <QDir>
#include <QString>
#include <QRegularExpression>
#include <fstream>
#include "../defines.hpp"
#include "../Exception/Exception.hpp"

class FileDataBase
{
public:
    static QString readAllFile(const QString &fileName)
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly))
        {
            return file.readAll();
        }
        throw FileOpenException(fileName);
    }

    static QString extractValueFromStrWithSelector(const QString &userData, const QString &selector)
    {
        QRegularExpression regex(QString("%1:\\s*\"([^\"]*)\"").arg(selector));
        QRegularExpressionMatch match = regex.match(userData);
        if (match.hasMatch())
        {
            return match.captured(1);
        }
        return QString();
    }

    static QString loadStyleFromFile(const QString &filePath, const QString &selector)
    {
        QFile file(filePath);
        if (!file.open(QFile::ReadOnly))
        {
            return QString();
        }

        QString styleSheet = file.readAll();
        QString pattern = QString("(%1\\s*\\{[^}]*\\})").arg(QRegularExpression::escape(selector));
        QRegularExpression regex(pattern);
        QRegularExpressionMatch match = regex.match(styleSheet);

        if (match.hasMatch())
        {
            return match.captured(1);
        }
        return QString();
    }
};

#endif