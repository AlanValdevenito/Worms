#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <netinet/in.h>

#include "dto.h"
#include "socket.h"

const uint8_t CHAT_CODE = 5;
const uint8_t PLAYER_CNT_CODE = 6;
const uint8_t CHAT_MSG_CODE = 9;

const char ESPACIO = ' ';
const char CHAT_ESPACIO[] = "Chat ";

class ClientProtocol
{
public:
    explicit ClientProtocol(Socket &skt);
    ~ClientProtocol();
    Dto *receive(bool &was_closed);
    void sendChatMsj(std::string str, bool &was_closed);

private:
    Socket &skt;

    Dto *receiveChatMessage(bool &was_closed);
    Dto *receiveNumberOfPlayers(bool &was_closed);
};
#endif
