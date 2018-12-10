#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string>

class ISocketWrapper;

class Connector
{
public:
    Connector(ISocketWrapper& socket, const std::string& nickname);
    std::string GetCompanionNickname() const;
};

#endif // CONNECTOR_H
