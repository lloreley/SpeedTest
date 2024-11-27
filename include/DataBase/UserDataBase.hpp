#ifndef USER_DATA_BASE_HPP
#define USER_DATA_BASE_HPP

#include "FileDataBase.hpp"

class UserDataBase : public FileDataBase
{
public:
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