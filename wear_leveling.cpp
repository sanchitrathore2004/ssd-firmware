#include "wear_leveling.h"

WearLeveling::WearLeveling(NandFlash& nand)
    : nand(nand) {
}

size_t WearLeveling::getLeastWornBlock() const {
    size_t best_block = 0;
    uint32_t min_erase_count = nand.getEraseCount(0);
    for (size_t block = 1; block < nand.getNumBlocks(); block++) {
        uint32_t current_count = nand.getEraseCount(block);
        if (current_count < min_erase_count) {
            min_erase_count = current_count;
            best_block = block;
        }
    }

    return best_block;
}
