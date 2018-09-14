#pragma once
#include "isocketwrapper.h"
#include <Windows.h>

class SocketWrapper : public ISocketWrapper
{
public:
    SocketWrapper();
    explicit SocketWrapper(SOCKET& other);
    ~SocketWrapper();
    void Bind(const std::string& addr, int16_t port);
    void Listen();
    ISocketWrapperPtr Accept();
    ISocketWrapperPtr Connect(const std::string& addr, int16_t port);
    void Read(std::string& buffer);
    void Write(const std::string& buffer);

private:
    SOCKET m_socket;
};
