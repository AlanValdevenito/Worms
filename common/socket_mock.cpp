#include "socket_mock.h"

SocketMock::SocketMock() : receivedSize(0), wasClosed(false) {}

SocketMock::~SocketMock() {}

SocketInterface *SocketMock::accept() { return new SocketMock(); }
void SocketMock::shutdown(int how) {}
int SocketMock::close() { return 0; }
int SocketMock::sendsome(const void *data, unsigned int sz, bool *was_closed) { return 0; }
int SocketMock::recvsome(void *data, unsigned int sz, bool *was_closed) { return 0; }

int SocketMock::sendall(const void *data, unsigned int sz, bool *was_closed)
{

    // almaceno los bytes que llegan
    std::vector<char> newData(static_cast<const char *>(data), static_cast<const char *>(data) + sz);

    // concateno, al final, los datos entrantes con los existentes
    receivedData.insert(receivedData.end(), newData.begin(), newData.end());
    receivedSize += sz;

    *was_closed = wasClosed;
    return sz;
}

// Métodos para acceder a los datos recibidos
const std::vector<char> &SocketMock::getReceivedData() const
{
    return receivedData;
}

unsigned int SocketMock::getReceivedSize() const
{
    return receivedSize;
}

bool SocketMock::wasConnectionClosed() const
{
    return wasClosed;
}

int SocketMock::recvall(void *data, unsigned int sz, bool *was_closed)
{
    // Verifico si recibi datos previamente
    if (receivedData.empty())
    {
        *was_closed = true;
        return 0; // No hay datos para enviar
    }

    // Calculo la cantidad de datos a enviar (mínimo entre sz y los datos recibidos)
    int bytesToSend = std::min(static_cast<int>(sz), static_cast<int>(receivedData.size()));

    // Copio los datos desde receivedData a data
    std::memcpy(static_cast<void *>(data), receivedData.data(), bytesToSend);

    // Actualizo receivedData y receivedSize
    receivedData.erase(receivedData.begin(), receivedData.begin() + bytesToSend);
    receivedSize -= bytesToSend;

    return bytesToSend;
}
