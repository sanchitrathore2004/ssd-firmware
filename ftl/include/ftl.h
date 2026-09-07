#pragma once

#include "nand_flash.h"
#include "wear_leveling.h"
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <cstddef>

using namespace std;

struct PhysicalAddress
{
    size_t block;
    size_t page;

    PhysicalAddress(size_t block=0, size_t page=0)
    {
        this->block = block;
        this->page = page;
    }
};

class FTL
{
private:
    NandFlash &nand;
    WearLeveling wear_leveling;
    unordered_map<uint64_t, PhysicalAddress> mapping;
    size_t next_block;
    size_t next_page;

    PhysicalAddress allocatePage();

public:
    FTL(NandFlash &nand);

    bool write(uint64_t lba, const vector<uint8_t> &data);
    vector<uint8_t> read(uint64_t lba);

    const unordered_map<uint64_t, PhysicalAddress> &getMapping() const;

    bool updateMapping(uint64_t lba, PhysicalAddress address);

    NandFlash &getNand();

    PhysicalAddress allocateForGC(size_t excluded_block);

    bool relocate(uint64_t lba,
                  const vector<uint8_t> &data,
                  PhysicalAddress &new_address,
                  size_t excluded_block);
};