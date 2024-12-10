#ifndef USER_HPP
#define USER_HPP

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QTimer>
#include "../defines.hpp"
#include "../DataBase/FileDataBase.hpp"

class ServerClient : public QObject
{
    Q_OBJECT

public:
    ServerClient(QObject *parent = nullptr) : QObject(parent), nextBlockSize{}, isConnected(true)
    {
        socket = new QTcpSocket;
        socket->connectToHost(SERVER_IP, SERVER_PORT);
        connect(socket, &QTcpSocket::readyRead, this, &ServerClient::read);
        connect(this, &ServerClient::messageReceived, this, &processMessage);
        keepAliveTimer = new QTimer(this);
        connect(keepAliveTimer, &QTimer::timeout, this, &checkConnection);
        keepAliveTimer->start(KEEP_ALIGN_TIME);
    }
    ServerClient(QTcpSocket *skt, QObject *parent = nullptr) : QObject(parent), nextBlockSize{}, isConnected(true)
    {
        QObject::disconnect(skt, nullptr, nullptr, nullptr);
        socket = skt;
        connect(socket, &QTcpSocket::readyRead, this, &ServerClient::read);
        connect(this, &ServerClient::messageReceived, this, &processMessage);
        keepAliveTimer = new QTimer(this);
        connect(keepAliveTimer, &QTimer::timeout, this, &checkConnection);
        keepAliveTimer->start(KEEP_ALIGN_TIME);
    }
    ~ServerClient()
    {
        if (!socket)
            delete socket;
        keepAliveTimer->stop();
        delete keepAliveTimer;
    }
    QTcpSocket *getSocket()
    {
        return socket;
    }
    void setSocket(QTcpSocket *socket)
    {
        this->socket = socket;
        if (!socket)
        {
            keepAliveTimer->stop();
        }
    }

public slots:
    void sendToServer(const QString &str)
    {
        if (socket && socket->state() == QAbstractSocket::ConnectedState)
        {
            Data.clear();
            QDataStream out(&Data, QIODevice::WriteOnly);
            out << quint16(str.size());
            out << str;
            socket->write(Data);
            socket->flush();
        }
        else
        {
            emit connectionLost();
        }
    }

protected slots:
    virtual void processMessage(const QString &message)
    {
        if (message.contains(CHECK_CONNECTION_MESSAGE))
        {
            isConnected = true;
            sendToServer(CHECK_CONNECTION_MESSAGE);
        }
        else if (message.contains(DISCONNECT_CONNECTION_MESSAGE))
        {
            emit disconnected();
        }
    }
private slots:

    void tryConnectToServer()
    {
        if (socket->state() == QAbstractSocket::UnconnectedState)
        {
            socket->connectToHost(SERVER_IP, SERVER_PORT);
        }
    }
    void checkConnection()
    {
        if (isConnected)
        {
            isConnected = false;
        }
        else
        {
            tryConnectToServer();
            emit connectionLost();
        }
    }
    void read()
    {
        QDataStream in(socket);
        in.setVersion(QDataStream::Qt_5_14);
        while (socket && socket->bytesAvailable() >= sizeof(quint16))
        {
            if (nextBlockSize == 0)
            {
                in >> nextBlockSize;
            }

            if (socket->bytesAvailable() >= nextBlockSize)
            {
                QString message;
                in >> message;
                nextBlockSize = 0;
                emit messageReceived(message);
            }
            else
                return;
        }
    }

protected:
    QTcpSocket *socket;
    QByteArray Data;
    quint16 nextBlockSize;
    QTimer *keepAliveTimer;
    bool isConnected;

signals:
    void messageReceived(QString message);
    void connectionLost();
    void disconnected();
};

class BaseUser : public ServerClient
{
    Q_OBJECT
public:
    BaseUser(QObject *parent = nullptr) : ServerClient(parent), userData(""), name(""), email(""), dateRegistration("") {}

    BaseUser(QTcpSocket *skt, QObject *parent = nullptr) : ServerClient(skt, parent), userData("") {}

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
        ServerClient::processMessage(message);
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
        else if (message.contains(ACCOUNT_MESSAGE_TYPE))
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

    User(QTcpSocket *skt, QObject *parent = nullptr) : BaseUser(skt, parent) {}

    void setUserData(const QString &userData)
    {
        this->userData = userData;
        name = FileDataBase::extractValueFromStrWithSelector(userData, NAME_SELECTOR);
        email = FileDataBase::extractValueFromStrWithSelector(userData, EMAIL_SELECTOR);
        dateRegistration = FileDataBase::extractValueFromStrWithSelector(userData, DATE_OF_REGISTRATION_SELECTOR);
    }
};

#endif
