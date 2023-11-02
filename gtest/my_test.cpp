#include <gtest/gtest.h>
#include "socket.h"
#include "client.h"
#include "client_protocol.h"
#include "server_protocol.h"

TEST(MyTest, PassingTest)
{

    // Socket aceptador("8080");
    // Socket client_socket("127.0.0.1", "8080");
    // Socket peer = aceptador.accept();

    // ClientProtocol cp(std::ref(client_socket));
    // ServerProtocol sp(std::ref(peer));

    ASSERT_TRUE(true); // Esta aserción siempre será verdadera
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
