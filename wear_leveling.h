#pragma once
#include "nand_flash.h"
#include <cstddef>

class WearLeveling {
private:
    NandFlash& nand;
public:
    WearLeveling(NandFlash& nand);
    size_t getLeastWornBlock() const;
};