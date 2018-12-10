#include "connector.h"
#include "socketwrapper.h"
#include "utils.h"

Connector::Connector(ISocketWrapper& socket, const std::string& nickname)
{

}

std::string Connector::GetCompanionNickname() const
{
    return "Alice";
}
