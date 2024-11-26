#ifndef USER_HPP
#define USER_HPP

#include "ServerClient.hpp"
#include "../DataBase/FileDataBase.hpp"

class BaseUser : public ServerClient
{
    Q_OBJECT
public:
    BaseUser(QObject *parent = nullptr) : ServerClient(parent), userData("")
    {

        connect(this, ServerClient::messageReceived, this, processMessage);
    }

    virtual void processMessage(const QString &message) = 0;

    const QString getName()
    {
        return name;
    }
    const QString getEmail()
    {
        return email;
    }
    const QString getDateRegistration()
    {
        return dateRegistration;
    }
    const QString getUserData()
    {
        return userData;
    }
    void addTypingResult(const QString &newResult)
    {
        if (!userData.isEmpty())
        {
            userData += newResult + "\n";
            userData.remove('\r');
            sendToServer(QString("Save\n") + userData);
        }
    }

protected:
    QString userData;
    QString name;
    QString email;
    QString dateRegistration;

signals:
    void accountCreated();
    void accountNotCreated();
    void userNotFound();
    void passwordIncorrect();
    void loginSuccessful();
};

class UnauthorizedUser : public BaseUser
{
    Q_OBJECT
public:
    UnauthorizedUser(QObject *parent = nullptr) : BaseUser(parent)
    {
        name = "none";
        email = "none";
        dateRegistration = "none";
        userData = "Typing history";
    }

public slots:

    void processMessage(const QString &message) override
    {
        if (message.contains(CHECK_CONNECTION_MESSAGE))
        {
            sendToServer(CHECK_CONNECTION_MESSAGE);
        }
        if (message.contains(ACCESS_MESSAGE_TYPE))
        {
            if (message.contains(ACCESS_USER_NOT_FOUND))
            {
                emit userNotFound();
                return;
            }
            if (message.contains(ACCESS_PASSWORD_INCORRECT))
            {
                emit passwordIncorrect();
                return;
            }
            userData = message.mid(message.indexOf(NAME_SELECTOR));

            emit loginSuccessful();
        }
        if (message.contains(ACCOUNT_MESSAGE_TYPE))
        {
            if (message.contains(ACCOUNT_CREATED))
            {
                userData = message.mid(message.indexOf(NAME_SELECTOR));
                emit accountCreated();
            }
            else
                emit accountNotCreated();
        }
    }
};

class User : public BaseUser
{
    Q_OBJECT
public:
    User(QObject *parent = nullptr) : BaseUser(parent) {}

    void setUserData(const QString &userData)
    {
        this->userData = userData;
        name = FileDataBase::extractValueFromStrWithSelector(userData, NAME_SELECTOR);
        email = FileDataBase::extractValueFromStrWithSelector(userData, EMAIL_SELECTOR);
        dateRegistration = FileDataBase::extractValueFromStrWithSelector(userData, DATE_OF_REGISTRATION_SELECTOR);
    }

    void processMessage(const QString &message) override
    {
        if (message.contains(CHECK_CONNECTION_MESSAGE))
        {
            sendToServer(CHECK_CONNECTION_MESSAGE);
        }
    }

private:
};

#endif