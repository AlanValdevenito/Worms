#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <string>
#include <vector>

#include "dto.h"

class DeadDto : public Dto
{
public:
    DeadDto();
    ~DeadDto();
    bool is_alive() override;
};
#endif