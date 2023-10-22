#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <netinet/in.h>

#include "blockingqueue.h"
#include "dto.h"
#include "socket.h"

const uint8_t PLAYER_CNT_CODE = 6;
const uint8_t CHAT_MSG_CODE = 9;

class ServerProtocol
{
public:
    explicit ServerProtocol(Socket &skt);
    ~ServerProtocol();
    Dto *decode(bool &was_closed);
    void send(bool &was_closed, Dto *msj);

private:
    Socket &skt;
    void players_message(bool &was_closed, uint8_t number_of_players);
    void chat_message(bool &was_closed, const std::string &msj);
    uint8_t recv_comand(bool &was_closed);
    uint16_t recv_size_of_message(bool &was_closed);
    Dto *recv_message(bool &was_closed, uint16_t sz, uint8_t code);
};
#endif
