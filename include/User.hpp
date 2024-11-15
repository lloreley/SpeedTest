#ifndef USER
#define USER

#include "ServerClient.hpp"

class BaseUser : public ServerClient
{
public:
    BaseUser(QObject *parent = nullptr) : ServerClient(parent), userData("")
    {

        connect(this, ServerClient::messageReceived, this, processMessage);

    }

    virtual void processMessage(const QString &message) = 0;

private:
    QString userData;
};

// class UnauthorizedUser : public BaseUser
// {

// public:
//     UnauthorizedUser(QObject *parent = nullptr) : BaseUser(parent) {}

//     void processMessage(const QString &message) override
//     {

//     }

// protected:
// };

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
        qDebug() << "Received message:" << message;

        if (message.startsWith(CHECK_CONNECTION_MESSAGE))
        {
            sendToServer(CHECK_CONNECTION_MESSAGE);
        }
        if(message.startsWith(ACCESS_MESSAGE_TYPE))
        {
            
        }
        if(message.startsWith(ACCOUNT_CREATED_MESSAGE_TYPE))
        {

        }
        
    }

private:
};

#endif