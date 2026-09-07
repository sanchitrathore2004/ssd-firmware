#include "garbage_collector.h"

GarbageCollector::GarbageCollector(FTL& ftl)
    : ftl(ftl) {
}

bool GarbageCollector::collect() {
    NandFlash& nand = ftl.getNand();

    size_t victim_block = nand.getNumBlocks();
    size_t max_invalid = 0;

    for (size_t block = 0; block < nand.getNumBlocks(); block++) {
        size_t invalid_pages = 0;

        for (size_t page = 0; page < nand.getPagesPerBlock(); page++) {
            if (nand.isProgrammed(block, page) &&
                !nand.isValid(block, page)) {
                invalid_pages++;
            }
        }

        if (invalid_pages > max_invalid) {
            max_invalid = invalid_pages;
            victim_block = block;
        }
    }

    if (victim_block == nand.getNumBlocks() || max_invalid == 0) {
        return false;
    }

    const auto& mapping = ftl.getMapping();

    for (const auto& entry : mapping) {
        uint64_t lba = entry.first;
        PhysicalAddress address = entry.second;

        if (address.block != victim_block) {
            continue;
        }

        vector<uint8_t> data = nand.read(address.block, address.page);
        PhysicalAddress new_address(address.block, address.page);

        if (!ftl.relocate(lba, data, new_address, victim_block)) {
            return false;
        }
    }

    if (!nand.erase(victim_block)) {
        return false;
    }

    return true;
}