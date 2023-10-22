#include "dto.h"

Dto::Dto() {}

Dto::Dto(const std::string &message) : msg(message) {}

Dto::~Dto() {}

std::string Dto::message() { return msg; }

uint8_t Dto::code() { return 0; }

bool Dto::is_alive() { return false; }

uint8_t Dto::playersCount() { return 0; }

/*--------------------------------------------------------------------------------------------*/
/*-------------------------------CHAT_MESSAGE-------------------------------------------------*/
/*--------------------------------------------------------------------------------------------*/

ChatMessage::ChatMessage(const std::string &message, uint8_t cmd) : Dto(message)
{
    if (cmd == CLIENT_CHAT_CODE)
        dto_code = CODE_CHAT_MESSAGE;
    else
        throw std::invalid_argument(
            "Se intentó inicializar un mensaje de chat con un código inválido");
}
ChatMessage::ChatMessage(const std::string &message) : Dto(message), dto_code(CODE_CHAT_MESSAGE) {}

ChatMessage::~ChatMessage() {}

uint8_t ChatMessage::code() { return dto_code; }

bool ChatMessage::is_alive() { return true; }

/*--------------------------------------------------------------------------------------------*/
/*-------------------------------PLAYERS_MESSAGE----------------------------------------------*/
/*--------------------------------------------------------------------------------------------*/

PlayersMessage::PlayersMessage(uint8_t a_number) : players(a_number), msg(VACIO) {}

PlayersMessage::~PlayersMessage() {}

uint8_t PlayersMessage::code() { return dto_code; }

uint8_t PlayersMessage::playersCount() { return players; }

bool PlayersMessage::is_alive() { return true; }

std::string createDefaultMessage(uint8_t users_count)
{
    std::string msg(JUGADORES_N);
    msg += std::to_string(users_count);
    msg += COMPLETAR_MESAJE;
    return msg;
}

std::string PlayersMessage::message()
{
    msg = createDefaultMessage(players);
    return msg;
}

/*--------------------------------------------------------------------------------------------*/
/*-------------------------------DEAD_MESSAGE-------------------------------------------------*/
/*--------------------------------------------------------------------------------------------*/

DeadDto::DeadDto() : Dto(FIN) {}

DeadDto::~DeadDto() {}

bool DeadDto::is_alive() { return false; }
