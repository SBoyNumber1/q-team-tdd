#include "connector.h"
#include "socketwrapper.h"
#include "utils.h"

Connector::Connector(ISocketWrapper& socket, const std::string& nickname)
{
    bool isServer;
    m_socket = utils::EstablishConnection(socket, isServer);

    if (!isServer)
    {
        m_nickname = utils::ClientHandshake(*m_socket, nickname);
    }
    else
    {
        m_nickname = utils::ServerHandshake(*m_socket, nickname);
    }

}

std::string Connector::GetCompanionNickname() const
{
    return m_nickname;
}
