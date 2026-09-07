#pragma once

#include "nand_flash.h"
#include <cstddef>
#include <cstdint>

class Metrics {
private:
    NandFlash& nand;

public:
    Metrics(NandFlash& nand);

    size_t getProgrammedPages() const;
    size_t getValidPages() const;
    uint64_t getTotalEraseCount() const;
};