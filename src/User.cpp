#include "../include/User.h"
ServerClient::ServerClient(QObject *parent) : QObject(parent), nextBlockSize{}, isConnected(true)
{
    socket = new QTcpSocket;
    socket->connectToHost(SERVER_IP, SERVER_PORT);
    connect(socket, &QTcpSocket::readyRead, this, &ServerClient::read);
    connect(this, &ServerClient::messageReceived, this, &processMessage);
    keepAliveTimer = new QTimer(this);
    connect(keepAliveTimer, &QTimer::timeout, this, &checkConnection);
    keepAliveTimer->start(KEEP_ALIGN_TIME);
}
ServerClient::ServerClient(QTcpSocket *skt, QObject *parent) : QObject(parent), nextBlockSize{}, isConnected(true)
{
    QObject::disconnect(skt, nullptr, nullptr, nullptr);
    socket = skt;
    connect(socket, &QTcpSocket::readyRead, this, &ServerClient::read);
    connect(this, &ServerClient::messageReceived, this, &processMessage);
    keepAliveTimer = new QTimer(this);
    connect(keepAliveTimer, &QTimer::timeout, this, &checkConnection);
    keepAliveTimer->start(KEEP_ALIGN_TIME);
}
ServerClient::~ServerClient()
{
    if (!socket)
        delete socket;
    keepAliveTimer->stop();
    delete keepAliveTimer;
}
QTcpSocket *ServerClient::getSocket()
{
    return socket;
}
void ServerClient::setSocket(QTcpSocket *socket)
{
    this->socket = socket;
    if (!socket)
    {
        keepAliveTimer->stop();
    }
}
void ServerClient::sendToServer(const QString &str)
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
void ServerClient::processMessage(const QString &message)
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
void ServerClient::tryConnectToServer()
{
    if (socket->state() == QAbstractSocket::UnconnectedState)
    {
        socket->connectToHost(SERVER_IP, SERVER_PORT);
    }
}
void ServerClient::checkConnection()
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
void ServerClient::read()
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

BaseUser::BaseUser(QObject *parent) : ServerClient(parent), userData(""), name(""), email(""), dateRegistration("") {}
BaseUser::BaseUser(QTcpSocket *skt, QObject *parent) : ServerClient(skt, parent), userData("") {}
const QString BaseUser::getName()
{
    return name;
}
const QString BaseUser::getEmail()
{
    return email;
}
const QString BaseUser::getDateRegistration()
{
    return dateRegistration;
}
const QString BaseUser::getUserData()
{
    return userData;
}
void BaseUser::addTypingResult(const QString &newResult)
{
    if (!userData.isEmpty())
    {
        userData += newResult + "\n";
        userData.remove('\r');
        sendToServer(QString("Save\n") + userData);
    }
}

UnauthorizedUser::UnauthorizedUser(QObject *parent) : BaseUser(parent)
{
    name = "none";
    email = "none";
    dateRegistration = "none";
    userData = "Typing history";
}
void UnauthorizedUser::processMessage(const QString &message)
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

User::User(QObject *parent) : BaseUser(parent) {}
User::User(QTcpSocket *skt, QObject *parent) : BaseUser(skt, parent) {}
void User::setUserData(const QString &userData)
{
    this->userData = userData;
    name = FileDataBase::extractValueFromStrWithSelector(userData, NAME_SELECTOR);
    email = FileDataBase::extractValueFromStrWithSelector(userData, EMAIL_SELECTOR);
    dateRegistration = FileDataBase::extractValueFromStrWithSelector(userData, DATE_OF_REGISTRATION_SELECTOR);
}
