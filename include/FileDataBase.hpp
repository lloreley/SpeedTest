#ifndef FILE_DATA_BASE_H
#define FILE_DATA_BASE_H

#include <QDir>
#include <QString>
#include <QRegularExpression>
#include <fstream>

#define DATA_FOLDER_PATH "data"

#define NAME_SELECTOR "name"
#define PASSWORD_SELECTOR "password"
#define EMAIL_SELECTOR "email"
#define ID_SELECTOR "id"
#define USERS_COUNT_SELECETOR "users_count"

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
        // my exception bad open
        return QString("");
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
};

#endif