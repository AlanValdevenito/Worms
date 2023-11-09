#ifndef SOCKET_MOCK_H
#define SOCKET_MOCK_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "socket.h"
#include "socket_interface.h"
#include "dto.h"
#include "constantes.h"

class SocketMock : public SocketInterface
{
private:
    std::vector<char> receivedData;
    unsigned int receivedSize;
    bool wasClosed;

public:
    SocketMock();
    ~SocketMock() override;

    int recvall(void *data, unsigned int sz, bool *was_closed) override;
    int sendall(const void *data, unsigned int sz, bool *was_closed) override;
    const std::vector<char> &getReceivedData() const;
    unsigned int getReceivedSize() const;
    bool wasConnectionClosed() const;

    int sendsome(const void *data, unsigned int sz, bool *was_closed);
    int recvsome(void *data, unsigned int sz, bool *was_closed);

    SocketInterface *accept() override;
    void shutdown(int how) override;
    int close() override;
};
#endif
