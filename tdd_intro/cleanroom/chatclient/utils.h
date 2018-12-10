#include "socketwrapper.h"
#include "igui.h"

namespace utils
{
    bool TryToBind(ISocketWrapper& socket);
    ISocketWrapperPtr EstablishConnection(ISocketWrapper& socket, bool& isServer);
    void WriteToSocket(ISocketWrapper& socket, std::string data);
    void ReadFromSocket(ISocketWrapper& socket, std::string& data);
    std::string ClientHandshake(ISocketWrapper& socket, const std::string& nickname);
    std::string ServerHandshake(ISocketWrapper& socket, const std::string& nickname);
    void WriteFromGuiToSocket(IGui& gui, ISocketWrapper& socket);
    void WriteFromSocketToGui(IGui& gui, ISocketWrapper& socket, const std::string& name);
}
