#include"nand_flash.h"
#include<mutex>

NandFlash::NandFlash(size_t num_blocks, size_t pages_per_block, size_t page_size) {
    this->num_blocks = num_blocks;
    this->page_size = page_size;
    this->pages_per_block = pages_per_block;

    erase_count.resize(num_blocks, 0);
    blocks.resize(num_blocks);

    for(size_t i=0;i<num_blocks;i++){
        blocks[i].reserve(pages_per_block);
        for(size_t j=0;j<pages_per_block;j++){
            blocks[i].emplace_back(page_size);
        }
    }
}

bool NandFlash::program(size_t block, size_t page, const vector<uint8_t>& data) {
    if(block >= num_blocks || page >= pages_per_block) {
        return false;
    }

    if(data.size() != page_size) {
        return false;
    }

    {
        lock_guard<mutex> lock(mtx);
        if(blocks[block][page].programmed == true) {
            return false;
        }
        blocks[block][page].data = data;
        blocks[block][page].programmed = true;
        blocks[block][page].valid = true;
    }

    return true;
}

vector<uint8_t> NandFlash::read(size_t block, size_t page) {
    if(block >= num_blocks || page >= pages_per_block) {
        return {};
    }

    {
        lock_guard<mutex> lock(mtx);
        return blocks[block][page].data;
    }
}

bool NandFlash::erase(size_t block) {
    if(block >= num_blocks) {
        return false;
    }

    {
        lock_guard<mutex> lock(mtx);
        for(size_t page = 0; page < pages_per_block; page++) {
            blocks[block][page].data.assign(page_size, 0);
            blocks[block][page].programmed = false;
            blocks[block][page].valid = false;
        }

        erase_count[block]++;
    }

    return true;
}

size_t NandFlash::getPageSize() {
    return page_size;
}

size_t NandFlash::getPagesPerBlock() {
    return pages_per_block;
}

bool NandFlash::invalidate(size_t block, size_t page) {
    if(block >= num_blocks || page >= pages_per_block) {
        return false;
    }

    {
        lock_guard<mutex> lock(mtx);
        blocks[block][page].valid = false;
    }

    return true;
}

bool NandFlash::isValid(size_t block, size_t page) {
    if(block >= num_blocks || page >= pages_per_block) {
        return false;
    }

    {
        lock_guard<mutex> lock(mtx);
        return blocks[block][page].valid;
    }
}

bool NandFlash::isProgrammed(size_t block, size_t page) {
    if(block >= num_blocks || page >= pages_per_block) {
        return false;
    }

    {
        lock_guard<mutex> lock(mtx);
        return blocks[block][page].programmed;
    }
}

size_t NandFlash::getNumBlocks() {
    return num_blocks;
}

uint32_t NandFlash::getEraseCount(size_t block) {
    if(block >= num_blocks) return UINT32_MAX;
    {
        lock_guard<mutex> lock(mtx);
        return erase_count[block];
    }
}