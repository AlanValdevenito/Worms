#ifndef DEAD_H
#define DEAD_H

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