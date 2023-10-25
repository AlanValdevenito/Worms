#include "client.h"

Client::Client(Socket &&socket) : skt(std::move(socket)), protocolo(std::ref(skt)), was_closed(false) {}

Client::~Client() {}

void Client::start()
{
}
