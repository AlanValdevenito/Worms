#include "dead.h"

DeadDto::DeadDto() : Dto() {}

DeadDto::~DeadDto() {}

bool DeadDto::is_alive() { return false; }