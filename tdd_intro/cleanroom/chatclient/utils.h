#include "socketwrapper.h"

namespace utils
{
    bool TryToBind(ISocketWrapper& socket);
    ISocketWrapperPtr EstablishConnection(ISocketWrapper& socket);
    void WriteToSocket(ISocketWrapper& socket, std::string data);
    void ReadFromSocket(ISocketWrapper& socket, std::string& data);
    std::string ClientHandshake(ISocketWrapper& socket, const std::string& nickname);
    std::string ServerHandshake(ISocketWrapper& socket, const std::string& nickname);
}
