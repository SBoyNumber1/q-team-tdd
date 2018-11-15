#include <gtest/gtest.h>

using namespace testing;
/*
Implement chat application, that communicates via TCP sockets.
 There is list of requirenments to this application:
 * It receives user nickname through commandline arguments on start
 * It runs only for two clients
 * On start it checks if port 4444 is bound
    * if it is - connects to other client
    * if not - binds a port and waits for inbound connection
        * message "No one is here..." is displayed in UI
 * After establishing connection - handshake is performed:
    * client writes message with it's nickname and ':HELLO!' string to socket ("client:HELLO!")
    * server responses with it's nickname and ':HELLO!' magic ("server:HELLO!")
        * if server receives malformated message - it drops connection with this client
        * if client receives malformated message - it drops connection and exits
            * Error message is shown
    * Listening socket must be closed
        (i) More than one client is not allowed to connect

 * It must send messages via created connection, until it is dropped
    * Application outputs "me: " prefix for user input
    * User inputs message through console interface and presses ENTER
    * Text message is sent to socket
 * It must receive messages via created connection, until it is dropped
    * Message received through socket
    * Line with message and '@friend_name: ' prefix is displayed ("metizik: Hello!")
 * END of message is determined by '\0' byte
 * When connection is dropped by one of users
    * "You are alone now" message is displayed to user
    * Application exits

  (i) Client starts dialog

 OPTIONAL requirement:
    * If user enters '!exit!' message, application must close connection and exit
    * If user runs app with 'me' nickname - error with text "Username me is reserved and can not be used" is displayed and application exits
*/

#include "mocks.h"
using namespace ::testing;

bool TryToBind(ISocketWrapper& socket)
{
    try
    {
         socket.Bind("", 0);
    }
    catch (const std::exception& ex)
    {
        return false;
    }

    return true;
}

void EstablishConnection(ISocketWrapper& socket)
{
    if (TryToBind(socket))
    {
        socket.Listen();
        socket.Accept();
    }
    else
    {
        socket.Connect("", 0);
    }
}

TEST(Chat, StartAsServer)
{
    StrictMock<SocketWrapperMock> socketMock;
    EXPECT_CALL(socketMock, Bind(_, _));
    ASSERT_TRUE(TryToBind(socketMock));
}

TEST(Chat, StartAsClient)
{
    StrictMock<SocketWrapperMock> socketMock;
    EXPECT_CALL(socketMock, Bind(_, _)).WillOnce(Throw(std::runtime_error("")));
    ASSERT_FALSE(TryToBind(socketMock));
}

TEST(Chat, StartConnection)
{
    StrictMock<SocketWrapperMock> socketMock;
    EXPECT_CALL(socketMock, Bind(_, _)).WillOnce(Throw(std::runtime_error("")));
    EXPECT_CALL(socketMock, Connect(_, _)).WillOnce(Return(ISocketWrapperPtr()));
    EstablishConnection(socketMock);
}

TEST(Chat, AcceptAfterListen)
{
    StrictMock<SocketWrapperMock> listener;
    StrictMock<SocketWrapperMock> client;
    EXPECT_CALL(listener, Bind(_, _)); // TODO: Order matters !!!
    EXPECT_CALL(listener, Listen());
    EXPECT_CALL(client, Bind(_, _)).WillOnce(Throw(std::runtime_error("")));
    EXPECT_CALL(client, Connect(_, _)).WillOnce(Return(ISocketWrapperPtr()));
    EXPECT_CALL(listener, Accept()).WillOnce(Return(ISocketWrapperPtr()));

    EstablishConnection(listener);
    EstablishConnection(client);
}

TEST(Chat, ServerReturnsClientSocket)
{
    StrictMock<SocketWrapperMock> listener;
    ASSERT_NE(nullptr, EstablishConnection(listener));
}


