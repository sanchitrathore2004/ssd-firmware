#pragma once
#include<vector>
#include<cstdint>
#include <cstddef>
#include"flash_page.h"

class NandFlash {
    private:
        size_t num_blocks;
        size_t pages_per_block;
        size_t page_size;
        vector<vector<FlashPage>> blocks;
        vector<uint32_t> erase_count;
    public:
        NandFlash(size_t num_blocks, size_t pages_per_block, size_t page_size);

        bool program(size_t block, size_t page, const vector<uint8_t>& data);

        vector<uint8_t> read(size_t block, size_t page);

        bool erase(size_t block);

        size_t getPageSize();

        size_t getPagesPerBlock();

        bool invalidate(size_t block, size_t page);

        bool isValid(size_t block, size_t page);

        bool isProgrammed(size_t block, size_t page);

        size_t getNumBlocks();

        uint32_t getEraseCount(size_t block);
};