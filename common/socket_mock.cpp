#include "socket_mock.h"

SocketMock::SocketMock() : Socket("127.0.0.1", "8080"), receivedSize(0), wasClosed(false) {}
// SocketMock::SocketMock() : receivedData(nullptr), receivedSize(0), wasClosed(false) {}

SocketMock::~SocketMock() {}

// int SocketMock::recvall(void *data, unsigned int sz, bool *was_closed)
int SocketMock::sendall(const void *data, unsigned int sz, bool *was_closed)
{
    // almaceno los bytes que llegan
    // std::vector<char> newData(static_cast<char *>(data), static_cast<char *>(data) + sz);
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

// int SocketMock::sendall(const void *data, unsigned int sz, bool *was_closed)
int SocketMock::recvall(void *data, unsigned int sz, bool *was_closed)
{
    *was_closed = false;
    // Verifica si se han recibido datos previamente en recvall
    if (receivedData.empty())
    {
        return 0; // No hay datos para enviar
    }

    // Calculo la cantidad de datos a enviar (mínimo entre sz y los datos recibidos)
    int bytesToSend = std::min(static_cast<int>(sz), static_cast<int>(receivedData.size()));

    // Copia los datos desde receivedData a data
    // std::memcpy(const_cast<void *>(data), receivedData.data(), bytesToSend);
    std::memcpy(static_cast<void *>(data), receivedData.data(), bytesToSend);

    // Actualiza receivedData y receivedSize
    receivedData.erase(receivedData.begin(), receivedData.begin() + bytesToSend);
    receivedSize -= bytesToSend;

    // Verifica si quedan datos por enviar
    if (receivedData.empty())
    {
        // Se han enviado todos los datos almacenados
        *was_closed = true;
    }

    return bytesToSend;
}
