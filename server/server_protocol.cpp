#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket& skt): skt(skt) {}

ServerProtocol::~ServerProtocol() {}


void ServerProtocol::players_message(bool& was_closed, uint8_t number_of_clients) {
    skt.sendall(&PLAYER_CNT_CODE, sizeof(PLAYER_CNT_CODE), &was_closed);

    if (was_closed)
        return;

    skt.sendall(&number_of_clients, sizeof(number_of_clients), &was_closed);

    if (was_closed)
        return;
}


void ServerProtocol::chat_message(bool& was_closed, const std::string& msj) {
    uint16_t tam = htons(msj.size());

    skt.sendall(&CHAT_MSG_CODE, sizeof(CHAT_MSG_CODE), &was_closed);

    if (was_closed)
        return;

    skt.sendall(&tam, sizeof(tam), &was_closed);

    if (was_closed)
        return;

    skt.sendall(msj.c_str(), msj.size(), &was_closed);

    if (was_closed)
        return;
}

void ServerProtocol::send(bool& was_closed, Dto* msj) {

    if (was_closed)
        return;

    if (msj->code() == CHAT_MSG_CODE)
        chat_message(was_closed, msj->message());
    else if (msj->code() == PLAYER_CNT_CODE)
        players_message(was_closed, msj->playersCount());
    else
        return;
}

uint8_t ServerProtocol::recv_comand(bool& was_closed) {
    uint8_t comando;

    skt.recvall(&comando, sizeof(comando), &was_closed);

    if (was_closed)
        return 0;

    return comando;
}

uint16_t ServerProtocol::recv_size_of_message(bool& was_closed) {
    if (was_closed)
        return 0;

    uint16_t sz;
    skt.recvall(&sz, sizeof(sz), &was_closed);

    if (was_closed)
        return 0;

    uint16_t sz_2 = ntohs(sz);
    return sz_2;
}

Dto* ServerProtocol::recv_message(bool& was_closed, uint16_t sz, uint8_t code) {

    if (was_closed || sz == 0)
        return new DeadDto();

    std::vector<char> msj(sz);
    skt.recvall(msj.data(), msj.size(), &was_closed);

    if (was_closed)
        return new DeadDto();

    std::string mensaje(msj.begin(), msj.end());

    return new ChatMessage(mensaje, code);
}


Dto* ServerProtocol::decode(bool& was_closed) {
    if (was_closed)
        return new DeadDto();

    uint8_t comando = recv_comand(was_closed);
    uint16_t sz = recv_size_of_message(was_closed);
    Dto* dto = recv_message(was_closed, sz, comando);

    return dto;
}
