#ifndef USER_HPP
#define USER_HPP

#include "ServerClient.hpp"

class BaseUser : public ServerClient
{
    Q_OBJECT
public:
    BaseUser(QObject *parent = nullptr) : ServerClient(parent), userData("")
    {

        connect(this, ServerClient::messageReceived, this, processMessage);
    }

    virtual bool isAuthorizedUser() = 0;
    virtual void processMessage(const QString &message) = 0;

private:
    QString userData;

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
    UnauthorizedUser(QObject *parent = nullptr) : BaseUser(parent) {}

public slots:

    void processMessage(const QString &message) override
    {
        qDebug() << "Received message:" << message;

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
            emit loginSuccessful();
        }
        if (message.contains(ACCOUNT_MESSAGE_TYPE))
        {
            if (message.contains(ACCOUNT_CREATED))
            {
                emit accountCreated();
            }
            else
                emit accountNotCreated();
        }
    }

    bool isAuthorizedUser() override
    {
        return false;
    }
};

class User : public BaseUser
{
public:
    User(QObject *parent = nullptr) : BaseUser(parent)
    {
    }

    void checkCredentials()
    {
    }

    void processMessage(const QString &message) override
    {
    }

    bool isAuthorizedUser() override
    {
        return true;
    }

private:
};

#endif