// Tests for the real SocketWrapper implementation for Windows.
#include <gtest/gtest.h>
#include "socketwrapper.h"

TEST(SocketWrapperTest, EstablishConnection)
{
    SocketWrapper listener;
    SocketWrapper client;

    // Name "localhost" doesn't work! Use the next address to establish connection within the local computer.
    const char* address = "127.0.0.1";
    const int port = 4444;

    listener.Bind(address, port);
    listener.Listen();
    client.Connect(address, port);
    auto server = listener.Accept();

    const char* testPhrase = "bla-bla-bla";

    server->Write(testPhrase);
    std::string str;
    client.Read(str);

    EXPECT_STREQ(testPhrase, str.c_str());
}
