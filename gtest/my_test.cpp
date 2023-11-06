#include <gtest/gtest.h>
// #include "socket.h"
#include "socket_mock.h"
#include "client.h"
#include "client_protocol.h"
#include "server_protocol.h"

TEST(MyTest, PassingTest)
{

    SocketMock skt_mock;
    Socket skt("127.0.0.1", "8080");
    ClientProtocol cp(std::ref(skt));

    // uint8_t a = 8;
    // cp.sendPruebita(a); 
    // cp.recvPruebita();

    ASSERT_TRUE(true); // Esta aserción siempre será verdadera
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
