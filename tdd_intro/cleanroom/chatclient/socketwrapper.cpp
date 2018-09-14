#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <exception>
#include <vector>
#include <sstream>

#include "SocketWrapper.h"

namespace
{
    std::string GetExceptionString(const std::string& message, int errorCode)
    {
        return message + " " + std::to_string(errorCode) + "\n";
    }

    class WsaSubsystem
    {
    public:
        static void Init()
        {
            if (!m_self)
            {
                m_self.reset(new WsaSubsystem);
            }
        }

        ~WsaSubsystem()
        {
            ::WSACleanup(); // There is nothing to do with returned value
        }

    private:
        WsaSubsystem()
        {
            auto startupResult = ::WSAStartup(MAKEWORD(2,2), &m_wsaData);
            if (startupResult != 0)
            {
                throw std::runtime_error("WSAStartup failed: " + std::to_string(startupResult));
            }
        }

    private:
        WSADATA m_wsaData;
        static std::unique_ptr<WsaSubsystem> m_self;
    };

    std::unique_ptr<WsaSubsystem> WsaSubsystem::m_self;
}

SocketWrapper::SocketWrapper()
    : m_socket(INVALID_SOCKET)
{
    WsaSubsystem::Init();

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET)
    {
        throw std::runtime_error(GetExceptionString("Failed to create socket to listen on.", WSAGetLastError()));
    }
}

SocketWrapper::SocketWrapper(SOCKET & other)
    : m_socket(other)
{
    WsaSubsystem::Init();
}

SocketWrapper::~SocketWrapper()
{
    closesocket(m_socket);
}

void SocketWrapper::Bind(const std::string& addr, int16_t port)
{
    sockaddr_in addres;
    addres.sin_family = AF_INET;
    addres.sin_addr.s_addr = inet_addr(addr.data());
    addres.sin_port = htons(port);
    if (bind(m_socket, reinterpret_cast<sockaddr*>(&addres), sizeof(addres)) == SOCKET_ERROR)
    {
        throw std::runtime_error(GetExceptionString("Failed to bind socket to address.", WSAGetLastError()));
    }
}

void SocketWrapper::Listen()
{
    if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        throw std::runtime_error(GetExceptionString("Failed to listen on socket.", WSAGetLastError()));
    }
}

ISocketWrapperPtr SocketWrapper::Accept()
{
    SOCKET other = accept(m_socket, nullptr, nullptr);
    if (other == INVALID_SOCKET)
    {
        throw std::runtime_error(GetExceptionString("Failed to connect to client.", WSAGetLastError()));
    }
    return ISocketWrapperPtr(new SocketWrapper(other));
}

ISocketWrapperPtr SocketWrapper::Connect(const std::string& addr, int16_t port)
{
    sockaddr_in addres;
    addres.sin_family = AF_INET;
    addres.sin_addr.s_addr = inet_addr(addr.data());
    addres.sin_port = htons(port);
    SOCKET other = connect(m_socket, reinterpret_cast<sockaddr*>(&addres), sizeof(addres));
    if (other == INVALID_SOCKET)
    {
        throw std::runtime_error(GetExceptionString("Failed to connect to server.", WSAGetLastError()));
    }
    return ISocketWrapperPtr(new SocketWrapper(other));
}

void SocketWrapper::Read(std::string& buffer)
{
    std::vector<char> bufferTmp(1024); // 1KB
    int portionReceived = recv(m_socket, bufferTmp.data(), static_cast<int>(bufferTmp.size()), 0);
    if (SOCKET_ERROR == portionReceived)
    {
        throw std::runtime_error(GetExceptionString("Failed to read data.", WSAGetLastError()));
    }
    buffer.assign(bufferTmp.begin(), bufferTmp.begin() + portionReceived);
}

void SocketWrapper::Write(const std::string& buffer)
{
    for (int dataSent = 0; dataSent < buffer.size();)
    {
        dataSent += send(m_socket, buffer.data() + dataSent, static_cast<int>(buffer.size() - dataSent), 0);
        if (SOCKET_ERROR == dataSent)
        {
            throw std::runtime_error(GetExceptionString("Failed to send data.", WSAGetLastError()));
        }
    }
}
