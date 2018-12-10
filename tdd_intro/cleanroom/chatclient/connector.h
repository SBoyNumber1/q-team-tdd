#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string>
#include <socketwrapper.h>

class ISocketWrapper;

class Connector
{
public:
    Connector(ISocketWrapper& socket, const std::string& nickname);
    std::string GetCompanionNickname() const;
private:
    ISocketWrapperPtr m_socket;
    std::string m_nickname;
};

#endif // CONNECTOR_H
