#pragma once
#include <memory>
#include <string>
#include <cstdint>

class ISocketWrapper;
using ISocketWrapperPtr = std::shared_ptr<ISocketWrapper>;

/*
 *  Wrapper around the standard SOCKET object.
 *
 * All methods throw exceptions when errors occur.
 *
 * To create a listener (SERVER), use Bind -> Listen -> Accept
 * To create a CLIENT, use Connect
 * See SocketWrapperTest for example of its usage.
*/

class ISocketWrapper
{
public:
    // Binds this socket to specified address and port.
    virtual void Bind(const std::string& addr, int16_t port) = 0;
    // Sets the socket to listening state. In this state the socket is waiting for incoming connections.
    virtual void Listen()= 0;
    // Accepts the incoming connection and creates new socket for it.
    // Note, that the original socket stays in the same state as before Accept is called.
    // The returned socket is actually the right thing you need to send or receive data within the established connection.
    virtual ISocketWrapperPtr Accept() = 0;
    // Connects the socket to the binded port on specified address.
    virtual ISocketWrapperPtr Connect(const std::string& addr, int16_t port)= 0;
    // Reads all available data from the stream of established connection.
    virtual void Read(std::string& buffer)= 0;
    // Writes data to the stream of established connection.
    // Note, that this function succeeds when write operation is done:
    // it doesn't check whether the data was successfully received on the other side.
    virtual void Write(const std::string& buffer)= 0;
};
